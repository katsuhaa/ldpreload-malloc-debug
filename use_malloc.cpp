#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

//
extern "C" {
static int *pdebug_malloc_size = NULL;
}

int get_debug_malloc_size()
{
    if (pdebug_malloc_size == NULL) {
        pdebug_malloc_size = (int*)dlsym(RTLD_DEFAULT, "debug_malloc_size");
    }
    if (pdebug_malloc_size) {
        return *pdebug_malloc_size;
    }
    return 0;
}
//

int main(void)
{
    void *vp = malloc(1024);
    
    printf("all size %d\n", get_debug_malloc_size());
    
    void *vp2 = malloc(1024);
    printf("all size %d\n", get_debug_malloc_size());

    free(vp);
    printf("all size %d\n", get_debug_malloc_size());
    free(vp2);
    printf("all size %d\n", get_debug_malloc_size());
    
    return 0;
}

