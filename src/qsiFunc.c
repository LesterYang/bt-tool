/*
 * qsiFunc.c
 *
 *  Created on: Oct 26, 2012
 *      Author: lester
 */

#include "qsiFunc.h"

void* qsi_malloc(size_t size)
{
    void *p;

    if (size > 0 && size < QSI_MAX_ALLOC_SIZE){
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

void* qsi_calloc(size_t size)
{
    void *p;

    if (size > 0 && size < QSI_MAX_ALLOC_SIZE){
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

void qsi_free(void *p)
{
    if (!p)
        return;
    free(p);
}

char* qsi_strdup(const char *s)
{
    if (!s)
        return NULL;
    else {
    	int l;
    	l=strlen(s)+1;
        char *r = (char*)qsi_calloc(l);
        memcpy(r, s, l);
        return r;
    }
}

char *qsi_strlcpy(char *b, const char *s, size_t l)
{
    size_t k;
    k = strlen(s);
    if (k > l-1)
        k = l-1;
    memcpy(b, s, k);
    b[k] = 0;
    return b;
}
ssize_t qsi_read(int fd, void *buf, size_t count, int *type)
{
    for (;;) {
        ssize_t r;
        if ((r = read(fd, buf, count)) < 0)
            if (errno == EINTR)
                continue;
        return r;
    }
}

ssize_t qsi_write(int fd, const void *buf, size_t count, int *type)
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

ssize_t qsi_loop_read(int fd, void *data, size_t size, int *type)
{
    ssize_t ret = 0;
    int _type;

    if (!type) {
        _type = 0;
        type = &_type;
    }
    while (size > 0) {
        ssize_t r;
        if ((r = qsi_read(fd, data, size, type)) < 0)
            return r;
        if (r == 0)
            break;
        ret += r;
        data = (uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}

ssize_t qsi_loop_write(int fd, const void *data, size_t size, int *type)
{
    ssize_t ret = 0;
    int _type;

    if (!type) {
        _type = 0;
        type = &_type;
    }
    while (size > 0) {
        ssize_t r;
        if ((r = qsi_write(fd, data, size, type)) < 0)
            return r;

        if (r == 0)
            break;
        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}

int qsi_close(int fd)
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
    qsi_thread *t = (qsi_thread *)userdata;
    t->id = pthread_self();
   qsi_atomic_inc(&t->running);
    t->thread_func(t->userdata);
   qsi_atomic_sub(2, &t->running);

    return NULL;
}

qsi_thread* qsi_thread_new(qsi_thread_func_t thread_func, void *userdata)
{
	qsi_thread *t;
	t=(qsi_thread *)qsi_malloc(sizeof(qsi_thread));
	t->thread_func=thread_func;
	t->userdata=userdata;
	t->joined=FALSE;

	qsi_atomic_set(&t->running,0);

	if (pthread_create(&t->id, NULL, internal_thread_func, t) < 0) {
        qsi_free(t);
        return NULL;
    }
    qsi_atomic_inc(&t->running);

	return t;
}

void qsi_thread_free(qsi_thread *t)
{
	qsi_thread_join(t);
	qsi_free(t);
}

int qsi_thread_join(qsi_thread *t)
{
	if (t->joined)
	        return -1;
	t->joined = TRUE;
	return pthread_join(t->id, NULL);
}
