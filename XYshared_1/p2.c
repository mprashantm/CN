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
    int key1=ftok(".",1);
    int key2=ftok(".",2);
    int key3=ftok(".",3);
     printf("%d %d %d",key1,key2,key3);
    int semid =createSemaphore(key1,2);//S1 S2
    int shmid1=createSharedMemory(key2,10);//x
    int *X   =(int *)attachSharedMemory(shmid1);
    int shmid2=createSharedMemory(key3,10);//y
    int *Y   =(int *)attachSharedMemory(shmid2);
    int *values=(int *)malloc(sizeof(int *)*2);
    *values=0;*(values+1)=0;
    initSemaphore(semid,values);
    printf("%d %d",*X,*Y);
    while(1)
        {
	   printf("P1 X=%d Y=%d\n",*X,*Y); 
	 //P(1)
	   P(semid,0);
	 //read(X)
	  *Y=*X+1;
          //write(Y)    
         //V(2)
          V(semid,1);
        }
}

