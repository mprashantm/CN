#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/stat.h>
//#include<sys/fifo.h>
void handle()
{
  
}
int main()
{
  mkfifo("1",0666);
  int ffd=open("1",O_RDWR);
  write(ffd,"hello",5);
   write(ffd,"how a",5);
    write(ffd,"r you",5);
   char a[6];
   read(ffd,a,5);
  read(ffd,a,5);
  printf("%s",a); 
}
