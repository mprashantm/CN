#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "1.c"
#define SEMKEY  0x1234
#define SHMKEY1 11
#define SHMKEY2 12
int main()
{
    int semid =createSemaphore(ftok(".",1),2);//S1 S2
    int shmid1=createSharedMemory(ftok(".",2),10);//x
    char *X   =(char *)attachSharedMemory(shmid1);
    int shmid2=createSharedMemory(ftok(".",3),10);//y
    char *Y   =(char *)attachSharedMemory(shmid2);
    int *values=(int *)malloc(sizeof(int *)*2);
    *values=0;*(values+1)=0;
    initSemaphore(semid,values);
//    shmid1=16547892;
//    shmid2=16580668;
    int x=0,y=0,i;
    while(1)
        {
	   printf("P1 X=%d Y=%d\n",x,y); 
	 //P(1)
	   P(semid,0);
	 //read(X)
	 i=0;
          while(*X!='\0')
                {
                   x=x*10+(*X+'0');X++;i++;
                }
	  X-=i;
	  y=x+1;
          //write(Y)	
    	  i=0;
	printf("P1 X=%d Y=%d\n",x,y);	
           while(y>=0)
                {
                  *Y=y%10-'0';y/=10;Y++;i++;
                }
          *Y='\0';
          Y-=i;     
         //V(2)
          V(semid,1);
        }
}

