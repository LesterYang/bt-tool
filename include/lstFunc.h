/*
 * lstFunc.h
 *
 *  Created on: Oct 26, 2012
 *      Author: root
 */

#ifndef LSTFUNC_H_
#define LSTFUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <inttypes.h>
#include <sys/errno.h>
#include <asm-generic/errno-base.h>

typedef int lst_bool;

#ifndef FALSE
#define FALSE ((lst_bool) 0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#define LST_MAX_ALLOC_SIZE (1024*1024*64)  //64MB

#ifdef __GNUC__
#define LST_LIKELY(x) (__builtin_expect(!!(x),1))
#define LST_UNLIKELY(x) (__builtin_expect(!!(x),0))
#define LST_PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
#define LST_LIKELY(x) (x)
#define LST_UNLIKELY(x) (x)
#define LST_PRETTY_FUNCTION ""
#endif

#define lst_nop() do {} while (FALSE)

#ifdef LST_ASSERT
#define lst_assert(expr)                                              		\
    do {                                                                	\
        if (LST_UNLIKELY(!(expr))) {                                     	\
        	printf("Expr '%s' failed at %s:%u, function '%s'. Aborting\n",	\
						#expr , __FILE__, __LINE__, LST_PRETTY_FUNCTION);	\
            abort();                                                    	\
        }                                                              		\
    } while (0)
#else
#define lst_assert(expr) lst_nop()
#endif

#ifdef __GNUC__
#define LST_MAX(a,b)                            \
    __extension__ ({                            \
            typeof(a) _a = (a);                 \
            typeof(b) _b = (b);                 \
            _a > _b ? _a : _b;                  \
        })
#define LST_MIN(a,b)                            \
    __extension__ ({                            \
            typeof(a) _a = (a);                 \
            typeof(b) _b = (b);                 \
            _a < _b ? _a : _b;                  \
        })
#else
#define LST_MAX(a, b) 			((a) > (b) ? (a) : (b))
#define LST_MIN(a, b) 			((a) < (b) ? (a) : (b))
#endif

#define LST_ABS(a) 				((a) < 0 ? -(a) : (a))

#define LST_BIT_SET(var, bits)	((var) |= (bits))
#define LST_BIT_CLR(var, bits)	((var) &= ~(bits))
#define LST_BIT_AND(var, bits)	((var) &= (bits))
#define LST_BIT_VAL(var, bits)	((var) & (bits))
#define LST_GET_BITS(var, bits)	((var) & ((1ULL << bits)-1)

#define LST_ELEMENTSOF(x) (sizeof(x)/sizeof((x)[0]))


// allocate and free
void* lst_malloc(size_t size);
void* lst_calloc(size_t size);
void  lst_free(void *p);
char* lst_strdup(const char *s);

// sting copy
char *lst_strlcpy(char *b, const char *s, size_t l);

// read and write
ssize_t lst_read(int fd, void *buf, size_t count, int *type);
ssize_t lst_write(int fd, const void *buf, size_t count, int *type);
ssize_t lst_loop_read(int fd, void *data, size_t size, int *type);
ssize_t lst_loop_write(int fd, const void*data, size_t size, int *type);

// file
int lst_close(int fd);

static inline const char *lst_strnull(const char *x)
{
    return x ? x : "(null)";
}

// atomic
typedef struct lst_atomic {
    volatile int value;
} lst_atomic_t;
typedef struct lst_atomic_ptr {
    volatile unsigned long value;
} lst_atomic_ptr_t;

#define LST_ATOMIC_INIT(i)	{ (i) }
#define LST_ATOMIC_PTR_INIT(v) { .value = (long) (v) }

#ifdef __LST_ARM_v6

static inline void lst_memory_barrier(void) {
    asm volatile ("mcr  p15, 0, r0, c7, c10, 5  @ dmb");
}


static inline int lst_atomic_read(const lst_atomic_t *a) {
    lst_memory_barrier();
    return a->value;
}

static inline void lst_atomic_set(lst_atomic_t *a, int i) {
    a->value = i;
    lst_memory_barrier();
}

/* Returns the previously set value */
static inline int lst_atomic_add( int i, lst_atomic_t *a) {
    unsigned long not_exclusive;
    int new_val, old_val;

    lst_memory_barrier();
    do {
        asm volatile ("ldrex    %0, [%3]\n"
                      "add      %2, %0, %4\n"
                      "strex    %1, %2, [%3]\n"
                      : "=&r" (old_val), "=&r" (not_exclusive), "=&r" (new_val)
                      : "r" (&a->value), "Ir" (i)
                      : "cc");
    } while(not_exclusive);
    lst_memory_barrier();

    return old_val;
}

/* Returns the previously set value */
static inline int lst_atomic_sub( int i, lst_atomic_t *a) {
    unsigned long not_exclusive;
    int new_val, old_val;

    lst_memory_barrier();
    do {
        asm volatile ("ldrex    %0, [%3]\n"
                      "sub      %2, %0, %4\n"
                      "strex    %1, %2, [%3]\n"
                      : "=&r" (old_val), "=&r" (not_exclusive), "=&r" (new_val)
                      : "r" (&a->value), "Ir" (i)
                      : "cc");
    } while(not_exclusive);
    lst_memory_barrier();

    return old_val;
}

static inline int lst_atomic_inc(lst_atomic_t *a) {
    return lst_atomic_add(1, a);
}

static inline int lst_atomic_dec(lst_atomic_t *a) {
    return lst_atomic_sub(1, a);
}

static inline void* lst_atomic_ptr_load(const lst_atomic_ptr_t *a) {
    lst_memory_barrier();
    return (void*) a->value;
}

static inline void lst_atomic_ptr_store(lst_atomic_ptr_t *a, void *p) {
    a->value = (unsigned long) p;
    lst_memory_barrier();
}

#elif defined(__LST_x86)

#ifdef CONFIG_SMP
#define LOCK_PREFIX_HERE \
                 ".section .smp_locks,\"a\"\n"   \
                 ".balign 4\n"                   \
                 ".long 671f - .\n" /* offset */ \
                 ".previous\n"                   \
                 "671:"
#define LOCK_PREFIX LOCK_PREFIX_HERE "\n\tlock; "
#else
#define LOCK_PREFIX_HERE ""
#define LOCK_PREFIX ""
#endif

static inline int lst_atomic_read(const lst_atomic_t *v)
{
	return (*(volatile int *)&(v)->value);
}

static inline void lst_atomic_set(lst_atomic_t *v, int i)
{
	v->value = i;
}

static inline void lst_atomic_add(int i, lst_atomic_t *v)
{
	asm volatile(LOCK_PREFIX "addl %1,%0"
		     : "+m" (v->value)
		     : "ir" (i));
}
static inline void lst_atomic_sub(int i, lst_atomic_t *v)
{
	asm volatile(LOCK_PREFIX "subl %1,%0"
		     : "+m" (v->value)
		     : "ir" (i));
}
static inline void lst_atomic_inc(lst_atomic_t *v)
{
	asm volatile(LOCK_PREFIX "incl %0"
		     : "+m" (v->value));
}
static inline void lst_atomic_dec(lst_atomic_t *v)
{
	asm volatile(LOCK_PREFIX "decl %0"
		     : "+m" (v->value));
}
#else

#define lst_atomic_read(v)	(*(volatile int *)&(v)->value)
#define lst_atomic_set(v,i)	(((v)->value) = (i))
#define lst_atomic_add(i,v)	(((v)->value) = (((v)->value)+(i)))
#define lst_atomic_sub(i,v)	(((v)->value) = (((v)->value)-(i)))
#define lst_atomic_inc(v)	(((v)->value) = (((v)->value)+(1)))
#define lst_atomic_dec(v)	(((v)->value) = (((v)->value)-(1)))

#endif


// thread
typedef void (*lst_thread_func_t) (void *userdata);
typedef struct lst_thread {
    pthread_t id;
    lst_thread_func_t thread_func;
    void *userdata;
    lst_bool joined;
    lst_atomic_t running;
}lst_thread;

lst_thread* lst_thread_new(lst_thread_func_t thread_func, void *userdata);
void lst_thread_free(lst_thread *t);
int lst_thread_join(lst_thread *t);



#endif /* LSTFUNC_H_ */
