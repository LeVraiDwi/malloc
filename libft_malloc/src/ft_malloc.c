#include "ft_malloc_include.h"

void    *ft_malloc(size_t size) {
    void    *p = NULL;
    int     pageSize;

    if (size) {
        pageSize = getpagesize();
        printf("%d %zu\n", pageSize, size);
        p = mmap(0, pageSize, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
        if (p == MAP_FAILED ) {
            printf("fail\n");
            return NULL;
        }
        ft_bzero(p, pageSize - 1);
    }
    return p;
}