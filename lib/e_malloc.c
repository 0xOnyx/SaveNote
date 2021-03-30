
#include <stdlib.h>
#include <stdio.h>

void *e_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);

    if(ptr == NULL)
    {
        fprintf(stderr, "[ERROR]\t Error to malloc abort program");
        exit(1);
    }
    return ptr;
}