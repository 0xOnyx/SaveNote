#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


void read_bytes(int fd, int size)
{

    unsigned char *bytes;
    unsigned int uid;

    if(read(fd, &uid, size ) == -1)
    {
        printf("[ERROR] TO READ");
    }
    

    bytes = (unsigned char *)&uid;

    int i = 0;
    printf("VALUE => %d\n", uid);
    printf("value2 = %c\n", uid);
    while(i < size)
    {
        printf("%02x", bytes[i]);
        i++;
    }

    putchar('\n');

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

    read_bytes(fd,4);
    
    int i = -1;
    while(++i < 9)
        read_bytes(fd,1);
    

    return 0;
}