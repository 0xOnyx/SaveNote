

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "./lib/e_malloc.h"

void usage(char *prog, char *file)
{
    printf("usage => \n\t $ %s <data to store in %s> \n", prog, file);
    exit(0);
}

//char *store_file = "/var/notes";
char *store_file = "./tmp.txt";


void write_user(unsigned int id_user, unsigned int fd)
{
    if(write(fd, &id_user , 4) == -1)
    {
        fprintf(stderr, "[ERROR]\t Error to write UID");
        exit(1);
    }
}

void write_content(char *content, unsigned fd)
{
    if(write(fd, &content, strlen(content)) == -1)
    {
        fprintf(stderr, "[ERROR]\t Error to write content");
        exit(1);
    }
}

void fail(char *msg_error)
{
     char buff_msg[100];

     strcpy(buff_msg, "[ERROR]\t");
     strncat(buff_msg, msg_error, 90);

     perror(buff_msg);
}


int main(int argc, char **argv )
{
    char *buff_string;
    unsigned int id_user;
    int fd;

    id_user = getuid();
    buff_string = (char *)e_malloc(sizeof(char) * 100);

    if(argc < 2)
        usage(argv[0], store_file);
       
    strcpy(buff_string, argv[1]);
    
    fd = open(store_file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);

    if(fd == -1)  
    {
        fprintf(stderr, "[ERROR]\t Error to open or create file");
        exit(1);
    }

    write_user(id_user, fd);
    write_content(buff_string, fd);
    
    if(close(fd) == -1 )
    {
        fprintf(stderr, "[ERROR]\t Error to close file");
        exit(1);
    }

    free(buff_string);

    return 0;
}