#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include "1.c"
int noOfclient;
int shmid,semid;
char Fifo[5][2][10]={{"11","12"},{"21","22"},{"31","32"},{"41","42"},{"51","52"}};
char *X;
void handler()
{
  mkfifo(Fifo[noOfClient][0],O_RDWR|NON_BLOCK);
  mkfifo(Fifo[noOFClient][1],O_RDWR|NON_BLOCK);
  int i;
 P()
  for(i=0;Fifo[noOfClient][0][i]!='\0';i++,X++)
    *X=Fifo[noOfCLient][0][i]; 
}
int main()
{
  shmid=shmget(ftok(".",1),10,IPC_CREAT|0666|IPC_EXCL);
  X=(char *)shmat(shmid,NULL,0);
  semid=semget(ftok(".",2),1,IPC_CREAT|0666|IPC_EXCL);
  semctl(semid,0,SETALL,0);
  signal(handler,SIGNUM);
  
}

