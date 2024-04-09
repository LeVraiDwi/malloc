#include "ft_malloc.h"
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/resource.h>
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

void *threadAlloc(void *arg) {
    unsigned int sizeToAlloc = 4;
    char **tab = arg;
    *tab = (char *)ft_malloc(sizeof(char) * sizeToAlloc);
    show_alloc_mem();
    return arg;
}

void *threadRealloc(void *arg) {
    unsigned int newSize = sizeof(char) * 1500;
    char **tab = arg;
    *tab = ft_realloc(*tab, newSize);
    show_alloc_mem();
    return NULL;
}

void *threadFree(void *arg) {
    void **ptr = arg;
    ft_free(*ptr);
    return NULL;
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
    printf("================Test Str Basic 1 ======================\n");
    {
        unsigned int sizeStr = 4;
        char *str = ft_malloc(sizeof(char) * sizeStr);
        for (unsigned int i = 0; i < sizeStr; i++) {
            str[i] = 's';
        }
        str[sizeStr - 1] = 0;
        show_alloc_mem();
        show_alloc_mem_hex();
        printf("%s\n", str);
        ft_free(str);
        show_alloc_mem();
        show_alloc_mem_hex();

        char *strs = malloc(sizeof(char) * sizeStr);
        for (unsigned int i = 0; i < sizeStr; i++) {
            strs[i] = 's';
        }
        strs[sizeStr - 1] = 0;

        printf("%s\n", strs);
        free(strs);
    }
    printf("================End Test Str Basic 1 ======================\n");
    printf("================Test realloc miss free 1 ======================\n");
    {        
        char * stttr = ft_malloc(sizeof(char) * 4);
        stttr = ft_realloc(stttr, 1509);
        show_alloc_mem();
        ft_free(stttr);
        show_alloc_mem();
    }
    printf("================End Test Str Basic 1 ======================\n");

    printf("================Test multi thread 1 ======================\n");
    {
        unsigned int nbThread = 15;
        char  *tab[nbThread];
        void **val = NULL;
        int threadId;
        pthread_t *id = ft_malloc(sizeof(pthread_t) * nbThread);
        for (unsigned int i = 0; i < nbThread; i++) {
            threadId = pthread_create(&id[i], NULL, &threadAlloc , &tab[i]);
        }
        for (unsigned int i = 0; i < nbThread; i++) {
            pthread_join(id[i], val);
        }
        show_alloc_mem_hex();
        for (unsigned int i = 0; i < nbThread; i++) {
            printf("realloc with: %p\n", (void *)tab[i]);
            threadId = pthread_create(&id[i], NULL, &threadRealloc , &tab[i]);
        }
        for (unsigned int i = 0; i < nbThread; i++) {
            pthread_join(id[i], val);
        }
        show_alloc_mem();
        for (unsigned int i = 0; i < nbThread; i++) {
            threadId = pthread_create(&id[i], NULL, &threadFree , &tab[i]);
        }
        for (unsigned int i = 0; i < nbThread; i++) {
            pthread_join(id[i], val);
        }
        ft_free(id);
        printf("=======================final tab==========================\n");
        show_alloc_mem();
    }
    printf("================End Test multi thread 1 ======================\n");
    printf("================Test realloc integreties 2 ======================\n");
    {
        int sizeOfStr = 15;
        char *str = ft_malloc(sizeof(char) * sizeOfStr);

        for (int i = 0; i < sizeOfStr; i ++) {
            str[i] = 's';
        }
        printf("string 1: %s\n", str);
        show_alloc_mem_hex();
        str = ft_realloc(str, sizeof(char) * 150);
        printf("string 2: %s\n", str);
        show_alloc_mem_hex();
        str = ft_realloc(str, sizeof(char) * 6);
        printf("string 3: %s\n", str);
        show_alloc_mem_hex();
        str = ft_realloc(str, sizeof(char) * 10);
        printf("string 3: %s\n", str);
        show_alloc_mem_hex();
        str = ft_realloc(str, sizeof(char) * 9);
        printf("string 3: %s\n", str);
        show_alloc_mem_hex();
        ft_free(str);
    }
    printf("================End Test realloc integreties 2 ======================\n");
    printf("================Test To Big For Mem ======================\n");
    {
        void *ptr = ft_malloc(99999999999999999);
        if (!ptr)
        {
            printf("failed to attribued %p\n", ptr);
        }
        else
            printf("succed to attribued %p\n", ptr);

    }
    printf("================End Test realloc integreties 2 ======================\n");
    printf("================Test null size ======================\n");
    {
        void *ptr = ft_malloc(0);
        if (!ptr)
        {
            printf("failed to attribued %p\n", ptr);
        }
        else
            printf("succed to attribued %p\n", ptr);
        ptr = ft_malloc(23515);
        show_alloc_mem();
        ptr = ft_realloc(ptr, 0);
        if (!ptr)
        {
            printf("failed to attribued %p\n", ptr);
        }
        else
            printf("succed to attribued %p\n", ptr);
        show_alloc_mem();
    }
    printf("================End Test null size ======================\n");
    printf("================Test null free ======================\n");
    {
        ft_free(0);
    }
    printf("================End Test null free ======================\n");
    printf("================Test tiny allocation ======================\n");
    {
        printf("taille d' un int : %li\n", sizeof(int));
        void *ptr = ft_malloc(256 - 72); // est la taille du header du block
        show_alloc_mem();
        ft_free(ptr);
    }
    printf("================End Test tiny allocation ======================\n");
    printf("================Test Small allocation ======================\n");
    {
        void *ptr = ft_malloc(2048 - 72); // est la taille du header du block
        show_alloc_mem();
        ft_free(ptr);
    }
    printf("================End Test Small allocation ======================\n");
    printf("================Test Large allocation ======================\n");
    {
        void *ptr = ft_malloc(20000000); // est la taille du header du block
        show_alloc_mem();
        ft_free(ptr);
    }
    printf("================End Test Large allocation ======================\n");
    printf("================Etat Final ======================\n");
    show_alloc_mem();
    show_alloc_mem_hex();
    printf("================End Etat Final ======================\n");

    return 0;
}