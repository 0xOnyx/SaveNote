#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


void read_bytes(int fd, int size)
{

    unsigned char *bytes;
    int i;

    if(read(fd, &bytes, size ) == -1)
    {
        printf("[ERROR] TO READ");
    }
    

    i = 0;

    while(i < 1)
    {
        printf("%02x", bytes[i]);
        i++;
    }

}

int main()
{
    int fd;


    fd = open("./tmp.txt", O_RDONLY);
    if(fd == -1)
    {   
        printf("[ERROR] TO OPEN\n");
        exit(-1);
    }

    read_bytes(fd, 4);
    
    return 0;
}