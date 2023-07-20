#include "ft_malloc.h"
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

volatile int running_threads = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printf_mutex = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *arg) {
    char *str = (char *)ft_malloc((sizeof(char) * 200));
    pthread_t *block = (pthread_t *)ft_malloc(sizeof(pthread_t));

    for (int i = 0; i <  199; i++)
        str[i] = 'b';
    str[199] = 0;
    pthread_mutex_lock(&printf_mutex);
    printf("=========Routine SHOW===========\n");
    show_alloc_mem_hex();
    pthread_mutex_unlock(&printf_mutex);
    str = ft_realloc(str, 600);
    ft_free(str);
    ft_free(block);
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    return arg;
}

void *routine_(void *arg) {
    int *tab[1034];

    for (int i = 0; i <  1034; i++)
        tab[i] = ft_malloc(sizeof(int));
    for (int i = 0; i <  1034; i++)
        *tab[i] = 2;
    pthread_mutex_lock(&printf_mutex);
    printf("=========Routine SHOW===========\n");
    show_alloc_mem_hex();
    pthread_mutex_unlock(&printf_mutex);
    for (int i = 0; i <  1034; i++)
        ft_free(tab[i]);
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    return arg;
}

void *routine__(void *arg) {
    pthread_t *block[23];

    for (int i = 0; i <  23; i++)
        block[i] = ft_malloc(sizeof(pthread_t));
    pthread_mutex_lock(&printf_mutex);
    printf("=========Routine SHOW===========\n");
    show_alloc_mem_hex();
    pthread_mutex_unlock(&printf_mutex);
    pthread_mutex_lock(&running_mutex);
    running_threads++;
    pthread_mutex_unlock(&running_mutex);
    pthread_create(block[2], NULL, routine, NULL);
    for (int i = 0; i <  23; i++)
        ft_free(block[i]);
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    return arg;
}

void *routine_malloc(void *arg) {
    char *str = (char *)malloc((sizeof(char) * 200));
    pthread_t *block = (pthread_t *)malloc(sizeof(pthread_t));

    arg = NULL;
    for (int i = 0; i <  199; i++)
        str[i] = 'b';
    str[199] = 0;
    str = realloc(str, 6);
    free(str);
    free(block);
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    return NULL;
}

int main() {
    int *i = (int *)ft_malloc(sizeof(int));
    int *k = (int *)ft_malloc(sizeof(int));
    char *c = (char *)ft_malloc(sizeof(char) * 18);
    char *c_ = (char *)malloc(sizeof(char) * 18);
    int *tab[10];

    int *tabInt = (int *)ft_malloc(sizeof(int) * 1024);

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
    tabInt[1024] = 11;
    tabInt[1000] = 2312;
    printf("%d\n%s%d\n%d\n", *i, c, tabInt[1000], tabInt[1024]);
    printf("=========FIRST SHOW===========\n");
    show_alloc_mem_hex();
    c = ft_realloc(c, sizeof(char) * 230);
    c = ft_realloc(c, sizeof(char) * 2);
    c = ft_realloc(c, sizeof(char) * 0);
    printf("=========SECOND SHOW===========\n");
    show_alloc_mem_hex();
    ft_free(i);
    for(int k = 0; k < 10; k++) {
        tab[k] = (int *)ft_malloc(sizeof(int));
    }
    printf("=========3rd SHOW===========\n");
    show_alloc_mem_hex();
    ft_free(k);
    ft_free(tabInt);
    free(c_);
    printf("=========4dr SHOW===========\n");
    show_alloc_mem_hex();
    char *f = (char*)ft_malloc(sizeof(char) * 223);
    f[2] = 'a';
    ft_free(f);
    for(int k = 0; k < 10; k++) {
        ft_free(tab[k]);
    }
    printf("=========END SHOW===========\n");
    show_alloc_mem();

    char *str = (char *)ft_malloc((sizeof(char) * 200));
    pthread_t *block = (pthread_t *)ft_malloc(sizeof(pthread_t));

    for (int i = 0; i <  199; i++)
        str[i] = 'b';
    str[199] = 0;
    printf("=========Routine SHOW===========\n");
    show_alloc_mem_hex();
    str = ft_realloc(str, 600);
    printf("=========Routine SHOW===========\n");
    ft_free(str);
    ft_free(block);
    printf("=========Routine SHOW===========\n");


    int *tab2[1034];

    for (int i = 0; i <  1034; i++)
        tab2[i] = ft_malloc(sizeof(int));
    printf("=========Routine SHOW===========\n");
    
    for (int i = 0; i <  1034; i++)
        *tab2[i] = 2;
    printf("=========Routine SHOW===========\n");
    show_alloc_mem_hex();
    for (int i = 0; i <  1034; i++)
        ft_free(tab2[i]);
    return 0;
}