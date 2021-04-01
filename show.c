
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "./lib/e_malloc.h"


#ifndef FILE 
#   define FILE "./tmp.txt"
#endif 

void fail(char *msg_error)
{
    char buff_msg[100];
    
    strcpy(buff_msg, "[ERROR]\t");
    strncat(buff_msg, msg_error, 90);

    perror(buff_msg);
}

int found_user(unsigned int fd, unsigned id_user)
{
    unsigned int buff_id;
    int lenght;
    unsigned char bytes;

    lenght = 0;

    while(buff_id != id_user)
    {
        printf("OK3\n");

        if(read(fd, &buff_id, 4) == -1 )
            return -1;

        //séprateur de ligne 1 bytes
        if(read(fd, &bytes, 1) == -1)
            return -1;

        printf("OK4\n");
        printf("%d\n", buff_id);

        bytes = 0;

        while(bytes != '\n')
        {
            printf("OK5\n");
            if(read(fd, &bytes, 1) != -1)
                return -1;
            
            printf("OK6%c\n",bytes);
            lenght++;
        }
    }
    #ifdef DEBUG
        printf("\t [DEBUG] Founded %d bytes for user %d ID", lenght, id_user);
    #endif

    lseek(fd, lenght * -1 , SEEK_CUR);


    return lenght;
    
}

int search_note(char *buff_note, char *searching_buff)
{
    int i;
    int lenght_note;
    int lenght_searching;

    if(searching_buff[0] == 0)
        return 1;

    i = 0;
    lenght_note = strlen(buff_note);
    lenght_searching = strlen(searching_buff);

    while(i < lenght_note)
    {
        if(buff_note[i] == searching_buff[0])
        {
            int y;
            y = 0;
            while(buff_note[i] == searching_buff[y])
            {
                if(y == lenght_searching)
                    return 1;
                i++;
                y++;
            }
            i -= y;
        }
        i++;
    }
    return 0;
}

int found_Note(unsigned int fd, unsigned int id_user, char *searching_buff)
{
    char buff_note[200];
    int note_lenght;

    note_lenght = found_user(fd, id_user);
    printf("OK2\n");

    if(note_lenght == -1)
        return -1;

    read(fd, buff_note, note_lenght);

    buff_note[note_lenght] = '\0';

    printf("OK1%s\n", buff_note);
    
    if(search_note(buff_note, searching_buff))
    {
        puts(buff_note);
    }
    
    return 1;
    
}

int main(int argv, char **argc)
{
    char *searching_buff;
    int fd;
    int founded_note;
    unsigned int id_user;

    if(argv > 1)
    {
        searching_buff = (char *)e_malloc(sizeof(char) * 50);
        strcpy(searching_buff, argc[1]);
    }
    else{
        searching_buff = (char *)e_malloc(sizeof(char)* 1);
        *searching_buff  = '\0';
    }

    fd = open(FILE, O_RDONLY);
    if(fd == -1)
        fail("failed to open file");

    founded_note = 1;

    printf("===============[NOTE]===============");
    while(founded_note){
        printf("\n\n");
        founded_note = found_Note(fd, id_user, searching_buff);
        printf("%d\n", founded_note);
    }

    if(close(fd) == -1)
        fail("failed to close file");

    free(searching_buff);

    return 0;
}