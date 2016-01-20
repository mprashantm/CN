#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#define BUF_LEN 1024
char buffer[BUF_LEN];
int mutex=1;
int available=0;
int ffd;//fifo file descriptor
void readInput()
{
  	char tmp[100];
	 while(1)
	 {
 	 scanf("%s",tmp);//read from input
  	 int i;
 	 while(available==1);//if buffer is full
  	 if(mutex==0)while(mutex!=1);//if writer is writting
  	 mutex=0;
         for(i=0;i<strlen(tmp);i++)
   	 {
     		buffer[i]=tmp[i];
  	 }
	  buffer[i]='\0';
	  mutex=1;//written in buffer
          available=1;//data is available 
	}
}
void writeBuffer()
{ 
	while(1)
	{
	  while(available!=1);//if data in buffer is not available
 	  if(mutex==0)while(mutex!=1);//if readInput thread is running
   	  mutex=0;
 	  write(ffd,buffer,strlen(buffer));
	  mutex=1;
   	  available=0;	
	}
}
int main(int argc,char *argv[])
{
   if(argc<2)
	{	
		printf("enter fifo name");	
		exit(1);
	}
	mkfifo(argv[1],0666);
	ffd=open(argv[1],O_RDWR);
	pthread_t p1,p2;
	if(pthread_create(&p1,NULL,(void *)(&readInput),NULL)!=0||pthread_create(&p2,NULL,(void *)(&writeBuffer),NULL)!=0)
          { 
		printf("pthread creation error");
		exit(1);
  	  }
        pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	return 0;
    while(1)
	{
		
	} 
}
