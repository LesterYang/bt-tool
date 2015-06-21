/*
 * lstFunc.c
 *
 *  Created on: Oct 26, 2012
 *      Author: lester
 */

#include "lstFunc.h"

void* lst_malloc(size_t size)
{
    void *p;

    if (size > 0 && size < LST_MAX_ALLOC_SIZE){
    	if (!(p = malloc(size))){
    		printf("malloc error");
    		return NULL;
    	}
    }
    else{
    	printf("alloc size error");
    	return NULL;
    }
    return p;
}

void* lst_calloc(size_t size)
{
    void *p;

    if (size > 0 && size < LST_MAX_ALLOC_SIZE){
    	if (!(p =  calloc(1, size))){
    		printf("malloc error");
    		return NULL;
    	}
    }
    else{
    	printf("alloc size error");
    	return NULL;
    }
    return p;
}

void lst_free(void *p)
{
    if (!p)
        return;
    free(p);
}

char* lst_strdup(const char *s)
{
    if (!s)
        return NULL;
    else {
    	int l;
    	l=strlen(s)+1;
        char *r = (char*)lst_calloc(l);
        memcpy(r, s, l);
        return r;
    }
}

char *lst_strlcpy(char *b, const char *s, size_t l)
{
    size_t k;
    k = strlen(s);
    if (k > l-1)
        k = l-1;
    memcpy(b, s, k);
    b[k] = 0;
    return b;
}
ssize_t lst_read(int fd, void *buf, size_t count, int *type)
{
    for (;;) {
        ssize_t r;
        if ((r = read(fd, buf, count)) < 0)
            if (errno == EINTR)
                continue;
        return r;
    }
}

ssize_t lst_write(int fd, const void *buf, size_t count, int *type)
{
    if (!type || *type == 0) {
        ssize_t r;
        for (;;) {
            if ((r = send(fd, buf, count, MSG_NOSIGNAL)) < 0) {
                if (errno == EINTR)
                    continue;
                break;
            }
            return r;
        }
        if (errno != ENOTSOCK)
            return r;
        if (type)
            *type = 1;
    }
    for (;;) {
        ssize_t r;
        if ((r = write(fd, buf, count)) < 0)
            if (errno == EINTR)
                continue;
        return r;
    }
}

ssize_t lst_loop_read(int fd, void *data, size_t size, int *type)
{
    ssize_t ret = 0;
    int _type;

    if (!type) {
        _type = 0;
        type = &_type;
    }
    while (size > 0) {
        ssize_t r;
        if ((r = lst_read(fd, data, size, type)) < 0)
            return r;
        if (r == 0)
            break;
        ret += r;
        data = (uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}

ssize_t lst_loop_write(int fd, const void *data, size_t size, int *type)
{
    ssize_t ret = 0;
    int _type;

    if (!type) {
        _type = 0;
        type = &_type;
    }
    while (size > 0) {
        ssize_t r;
        if ((r = lst_write(fd, data, size, type)) < 0)
            return r;

        if (r == 0)
            break;
        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}

int lst_close(int fd)
{
    for (;;) {
        int r;
        if ((r = close(fd)) < 0)
            if (errno == EINTR)
                continue;
        return r;
    }
}


static void* internal_thread_func(void *userdata)
{
    lst_thread *t = (lst_thread *)userdata;
    t->id = pthread_self();
   lst_atomic_inc(&t->running);
    t->thread_func(t->userdata);
   lst_atomic_sub(2, &t->running);

    return NULL;
}

lst_thread* lst_thread_new(lst_thread_func_t thread_func, void *userdata)
{
	lst_thread *t;
	t=(lst_thread *)lst_malloc(sizeof(lst_thread));
	t->thread_func=thread_func;
	t->userdata=userdata;
	t->joined=FALSE;

	lst_atomic_set(&t->running,0);

	if (pthread_create(&t->id, NULL, internal_thread_func, t) < 0) {
        lst_free(t);
        return NULL;
    }
    lst_atomic_inc(&t->running);

	return t;
}

void lst_thread_free(lst_thread *t)
{
	lst_thread_join(t);
	lst_free(t);
}

int lst_thread_join(lst_thread *t)
{
	if (t->joined)
	        return -1;
	t->joined = TRUE;
	return pthread_join(t->id, NULL);
}
