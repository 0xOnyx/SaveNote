

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "./lib/e_malloc.h"

void usage(char *prog, char *file)
{
    printf("usage => \n\t $ %s <data to store in %s> ", prog, file);
    exit(0);
}

char *store_file = "/var/notes"

int main(int argc, char **argv )
{
    char *store_file;
    char *buff_string;

    buff_string = (char *)e_malloc(sizeof(char) * 100);

    strcpy(store_file, );

    if(argc < 2)
        usage(argv[0], store_file);
       
    strcpy(buff_string, argv[1]);
    
    open()

    return 0;
}