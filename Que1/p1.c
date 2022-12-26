#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    pid_t id;
    char buff[10000];
    int fd[2];
    int fd_open = 0;
    int fd_read = 0;

    pipe(fd);


    id = fork();
    if(id == 0)
     {                  //process p2
        close(fd[1]);
        read(fd[0],buff,10000);
       
        close(fd[0]);
     }
    else 
     {       
                   // process p1
        fd_open = open("/usr/include/stdio.h",O_RDONLY);
        if(-1 == fd_open)
         {
             perror("Error in open :(\n");
             exit(EXIT_FAILURE);

         }

         /*reading the data of files*/
        fd_read = read(fd_open,buff,strlen(buff));  
        if(-1 == fd_read)
         {
            perror("Error in reading :(\n");
            exit(EXIT_FAILURE);
         }  
        close(fd[0]);
       
        close(fd[1]); 
     }
}