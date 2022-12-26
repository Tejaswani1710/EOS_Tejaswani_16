/*****************************************************************************************************
This is p1 process where we are opening "/usr/include/stdio.h" reading the data and send it to p2.
******************************************************************************************************/

/*****************************************************************************************************
 Header files which we are including
******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

/*****************************************************************************************************/

#define BUFF_SIZE 10000
char buff[BUFF_SIZE];
struct mq_attr desd_mq_attr;

/*****************************************************************************************************
 Main fuction
******************************************************************************************************/
int main()
{
    /*decalaration of variables*/
    int mq_send_er, mq_close_er;
    char *buff;
    int fd_open = 0;
    int fd_read = 0;
    mqd_t desd_mq_desc; 
    
    /****************************/
    
    /*these are the members of structure which are define in mq_open*/

    desd_mq_attr.mq_flags = 0;
    desd_mq_attr.mq_maxmsg = 5;     /*max. msg on queue*/
    desd_mq_attr.mq_msgsize = 10000;   /*msg size in byte*/ 
    desd_mq_attr.mq_curmsgs = 0;    /*msg'es currently in queue*/

    /*****************************************************************/

     /*opening the file */
    fd_open = open("/usr/include/stdio.h",O_RDONLY);
     if(-1 == fd_open)
     {
        perror("Error in open :(\n");
        exit(EXIT_FAILURE);

     }

    /*creating a queue*/
    desd_mq_desc = mq_open("/tejuqueue",O_CREAT|O_RDWR, S_IRUSR|S_IWUSR, &desd_mq_attr);
    if(-1 == desd_mq_desc)
     {
        perror("Error in mq_open :(\n");
        exit(EXIT_FAILURE);

     }
    else
     {
        printf("Reading...");
        /*reading the data of files*/
        fd_read = read(fd_open,buff,strlen(buff));  
        if(-1 == fd_read)
         {
            perror("Error in reading :(\n");
            exit(EXIT_FAILURE);
         }
     }

    /*sending the data*/
    mq_send_er = mq_send(desd_mq_desc,buff,strlen(buff),0);
    if(-1 == mq_send_er)
     {
        perror("Error in mq_send :(\n");
        exit(EXIT_FAILURE);
     }
    else
        printf("Data send successfully :)\n");

    /*closing the message queue descriptor*/    
    mq_close_er = mq_close(desd_mq_desc);
    if(-1 == mq_close_er)
     {
        perror("Error in mq_close :(\n");
        exit(EXIT_FAILURE);
     }
    return 0;
}

/*****************************************************************************************************/