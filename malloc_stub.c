#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>
#include <malloc.h>

int debug_malloc_size = 0; 

static void *(*malloc0)(size_t size) = NULL;
static void (*free0)(void* p) = NULL;

static void init_malloc0(void)
{
    malloc0 = dlsym(RTLD_NEXT, "malloc");
    free0 = dlsym(RTLD_NEXT, "free");
}

void *malloc(size_t size)
{
    void *retp;
    if (malloc0 == NULL) {
        init_malloc0();
    }

    retp = malloc0(size);
    if (retp) {
        debug_malloc_size += malloc_usable_size(retp);
    }
    return retp;
}

void free(void *p)
{
    if (malloc0 == NULL) {
        init_malloc0();
    }

    debug_malloc_size -= malloc_usable_size(p);
    return free0(p);
}


