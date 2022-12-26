/*****************************************************************************************************
This is p2 process here we are getting data from p1 and calculating the no. of occurance of char 's'.
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

#define BUFF_SIZE 128
char buff[BUFF_SIZE];
struct mq_attr desd_mq_attr;

/*****************************************************************************************************
 Main fuction
******************************************************************************************************/
int main()
{
    /*declaration of variables*/
    mqd_t desd_mq_desc; 
    int mq_recvd_er, mq_close_er;

    /**************************/
    
    /*these are the members of structure which are define in mq_open*/
    desd_mq_attr.mq_flags = 0;
    desd_mq_attr.mq_maxmsg = 5;    /*max. msg on queue*/
    desd_mq_attr.mq_msgsize = 10000;  /*msg size in byte*/ 
    desd_mq_attr.mq_curmsgs = 0;  /*msg'es currently in queue*/

    /****************************************************************/
    
    /*creating/opening a queue*/
    desd_mq_desc = mq_open("/tejuqueue",O_CREAT|O_RDWR, S_IRUSR|S_IWUSR, &desd_mq_attr);
    if(-1 == desd_mq_desc)
     {
        perror("Error in mq_open :(\n");
        exit(EXIT_FAILURE);
     }

    /*receiving the data from p1*/
    mq_recvd_er = mq_receive(desd_mq_desc,buff,strlen(buff),0);
    if(-1 == mq_recvd_er)
     {
        perror("Error in mq_receive :(\n");
        exit(EXIT_FAILURE);
     }
    else
        printf("Data received successfully :)\n");
        if()

    /*closing the queue*/    
    mq_close_er = mq_close(desd_mq_desc);
    if(-1 == mq_close_er)
     {
        perror("Error in mq_close :(\n");
        exit(EXIT_FAILURE);
     }

    return 0;
}