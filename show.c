
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "./lib/e_malloc.h"


#ifndef FILE 
#   define FILE "/var/note.priv"
#endif 

void fail(char *msg_error)
{
    char buff_msg[100];
    
    strcpy(buff_msg, "[ERROR]\t");
    strncat(buff_msg, msg_error, 90);
    perror(buff_msg);

    exit(1);
}

int found_user(unsigned int fd, unsigned int id_user)
{
    unsigned int buff_id;
    unsigned char bytes;
    int lenght;
    
    lenght = 0;

    while(buff_id != id_user)
    {
        if(read(fd, &buff_id, 4) == -1 )
            return -1;


        bytes = 'a';
        
        while(bytes != '\0')
        {
            if(read(fd, &bytes, 1) != 1)
                return -1;

            lenght++;
        }
    }

    #ifdef DEBUG
        printf("\t [DEBUG] Founded %d bytes for user %d ID\n", lenght, id_user);
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

    if(note_lenght == -1)
        return -1;

    read(fd, buff_note, note_lenght);

    buff_note[note_lenght] = '\0';

    
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

    id_user = getuid();

    founded_note = 1;

    puts("===============[NOTE]===============");
    while(founded_note != -1){
        putchar('\n');
        founded_note = found_Note(fd, id_user, searching_buff);
    }
    puts("===============[END]================");

    if(close(fd) == -1)
        fail("failed to close file");

    free(searching_buff);

    return 0;
}