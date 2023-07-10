#include "ft_malloc.h"
#include <stdio.h>

int main() {
    int *i = (int *)ft_malloc(sizeof(int));
    char *c = (char *)ft_malloc(sizeof(char) * 8);
    char *c_ = (char *)malloc(sizeof(char) * 8);

    int *tabInt = (int *)ft_malloc(sizeof(int) * 1024);

    c[0] = 's';
    c[1] = 'a';
    c[2] = 'l';
    c[3] = '\n';
    c[4] = '\0';
    // c[234] = 'q';
    // c_[234] = 'q';
    *i = 2;
    tabInt[1024] = 11;
    tabInt[1000] = 2312;
    printf("%d\n%s%d\n%d\n", *i, c, tabInt[1000], tabInt[1024]);
    ft_realloc(c, sizeof(char) * 230);
    ft_realloc(c, sizeof(char) * 2);
    ft_realloc(c, sizeof(char) * 0);
    ft_free(i);
    ft_free(tabInt);
    free(c_);
    return 1;
}