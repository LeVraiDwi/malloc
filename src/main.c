#include "ft_malloc.h"
#include <stdio.h>

int main() {
    int *i = (int *)ft_malloc(sizeof(int));

    *i = 2;
    printf("%d\n", *i);
    return 1;
}