
#include <unistd.h>
#include <stdio.h>

#include "./lib/e_malloc.h"


#ifndef FILE 
#   define FILE "./tmp.txt"
#endif 

void fail(char *msg_error)
{
    char buff_msg[100];
    
    strcpy(buff_msg, "[ERROR]\t");
    strncar(buff_msg, msg_error, 90);

    perror(buff_msg);
}

void found_user(unsigned int fd, unsigned id_user)
{
    unsigned int buff_id;
    int lenght;
    unsigned char bytes;

    lenght = 0;

    while(buff_id != id_user)
    {
        if(read(fd, buff_id, 4) == -1 )
            return -1;

        //séprateur de ligne 1 bytes
        if(read(fd, bytes, 1) == -1)
            return -1;

        while(bytes != '\n')
        {
            if(read(fd, bytes, 1) != -1)
                return -1;
            
            lenght++;
        }
    }

    lseek(fd, lenght * -1 , SEEKCUR);


    return lenght;
    
}

int found_Note(unsigned int fd, unsigned int id_user)
{
    char buff_note[200];
    int note_lenght;

    if(note_lenght == -1)
        return -1;

    read(fd, buff_note, note_lenght);

    buff_note[note_lenght] = '\0';
    

    //TODO =>
    //vérifier la search
    //return 
    
}

int main(int argv, char **argc)
{
    char *searching_buff;
    int fd;
    int founded_note;
    unsgined int id_user;

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
        fail("failed to open file")

    founded_note = 1;
    while(founded_note){
        founded_note = found_Note(fd, id_user, searching_buff);
    }

    if(close(fd) == -1)
        fail("failed to close file");

    free(searching_buff)

    return 0;
}