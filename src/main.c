#include "ft_malloc.h"
#include <stdio.h>

int main() {
    int *i = (int *)ft_malloc(sizeof(int));
    int *k = (int *)ft_malloc(sizeof(int));
    char *c = (char *)ft_malloc(sizeof(char) * 18);
    char *c_ = (char *)malloc(sizeof(char) * 18);

    // int *tabInt = (int *)ft_malloc(sizeof(int) * 1024);

    c[0] = 's';
    c[1] = 'a';
    c[2] = 'l';
    c[3] = '\n';
    c[4] = '\0';
    for (int k = 0; k < 17; k++)
        c[k] = 'p';
    c[17] = 0;
    // c[234] = 'q';
    // c_[234] = 'q';
    *i = 2;
    *k = 2;
    // tabInt[1024] = 11;
    // tabInt[1000] = 2312;
    // printf("%d\n%s%d\n%d\n", *i, c, tabInt[1000], tabInt[1024]);
    printf("=========FIRST SHOW===========\n");
    show_alloc_mem_hex();
    // ft_realloc(c, sizeof(char) * 230);
    // ft_realloc(c, sizeof(char) * 2);
    // ft_realloc(c, sizeof(char) * 0);
    ft_free(c);
    printf("=========FIRST SHOW===========\n");
    show_alloc_mem_hex();
    ft_free(i);
    ft_free(k);
    // ft_free(tabInt);
    free(c_);
    printf("=========FIRST SHOW===========\n");
    show_alloc_mem_hex();
    char *f = (char*)ft_malloc(sizeof(char) * 223);
    f[2] = 'a';
    ft_free(f);
    printf("=========FIRST SHOW===========\n");
    show_alloc_mem();
    return 0;
}