#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "malloc.h"

// #define M (1024 * 1024)
// void    print(char *s)
// {
//     write(1, s, strlen(s));
// }

void *threadAlloc(void *arg) {
    unsigned int sizeToAlloc = 4;
    char **tab = arg;
    *tab = (char *)malloc(sizeof(char) * sizeToAlloc);
    return arg;
}

void *threadRealloc(void *arg) {
    unsigned int newSize = sizeof(char) * 1500;
    char **tab = arg;
    *tab = realloc(*tab, newSize);
    return NULL;
}

void *threadFree(void *arg) {
    void **ptr = arg;
    free(*ptr);
    return NULL;
}

// int     main(void)
// {
//     int   i;
//     char  *addr;

//     i = 0;
//     while (i < 1024) 
//     {
//         addr = (char*)malloc(1024);
//         if (addr == NULL)
//         {
//             print("Failed to allocate memory\n");
//             return (1);
//         }
//         addr[0] = 42;
//         free(addr); 
//         i++;
//     }
//     show_alloc_mem();
//     return (0);
// }

// int     main()
// {
//     char *addr1;
//     char *addr2;
//     //char *addr3;

//     addr1 = (char*)malloc(16*M);
//     if (addr1 == NULL)
//     {
//         print("Failed to allocate memory\n");
//         return 1;
//     }
//     strcpy(addr1, "Hello world!\n");
//     print(addr1);
//     addr2 = (char*)malloc(16*M);
//     show_alloc_mem();
//     if (addr2 == NULL)
//     {
//         print("Failed to allocate memory\n");
//         return 1;
//     }
//     //addr3 = (char*)realloc(addr1, 128*M);
//     // if (addr3 == NULL)
//     // {
//     //     print("Failed to reallocate memory\n");
//     //     return 1;
//     // }
//     //addr3[127*M] = 42;
//     show_alloc_mem();
//     //print(addr3);
//     free(realloc(addr1, 128*M));
//     show_alloc_mem();
//     free(addr2);
//     show_alloc_mem();
//     return (0);
// }


// int     main(void)
// {
//     int   i;
//     char  *addr;

//     i = 0;
//     while (i < 1024) 
//     {
//         addr = (char*)malloc(1024);
//         if (addr == NULL)
//         {
//             print("Failed to allocate memory\n");
//             return (1);
//         }
//         addr[0] = 42;
//         free(addr); 
//         i++; 
//     }
//     return (0);
// }

void    print(char *s)
{
    write(1, s, strlen(s));
}

int     main(void)
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        if (addr == NULL)
        {
            print("Failed to allocate memory\n");
            return (1);
        }
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
}


// int main() {
//      unsigned int nbThread = 4;
//      char  *tab[nbThread];
//      void **val = NULL;
//      int threadId;
//     pthread_t *id = malloc(sizeof(pthread_t) * nbThread);

//     for (unsigned int i = 0; i < nbThread; i++) {
//         threadId = pthread_create(&id[i], NULL, &threadAlloc , &tab[i]);
//     }
//     for (unsigned int i = 0; i < nbThread; i++) {
//         pthread_join(id[i], val);
//     }
//     show_alloc_mem();
//     for (unsigned int i = 0; i < nbThread; i++) {
//         threadId = pthread_create(&id[i], NULL, &threadRealloc , &tab[i]);
//     }
//     for (unsigned int i = 0; i < nbThread; i++) {
//         pthread_join(id[i], val);
//     }
//     show_alloc_mem();
//     for (unsigned int i = 0; i < nbThread; i++) {
//         threadId = pthread_create(&id[i], NULL, &threadFree , &tab[i]);
//     }
//     for (unsigned int i = 0; i < nbThread; i++) {
//         pthread_join(id[i], val);
//     }
//     free(id);

//     write(1, "table end\n", strlen("table end\n"));
//     show_alloc_mem();
//     show_alloc_mem_hex();
//     return 0;
// }