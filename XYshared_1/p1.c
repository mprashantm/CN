#include <stdio.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include "1.c"
#define SEMKEY  0x1234
#define SHMKEY1 1
#define SHMKEY2 2
int main()
{
    int key1=ftok(".",1);
    int key2=ftok(".",2);
    int key3=ftok(".",3);
    printf("%d %d %d",key1,key2,key3);
    int semid =createSemaphore(key1,2);//S1 S2
    int shmid1=createSharedMemory(key2,4);//x
    printf("shmid1 %d from main\n",shmid1);
    int  *X   =(int *)attachSharedMemory(shmid1); 
    int shmid2=createSharedMemory(key3,4);//y
    printf("shmid2 %d from main\n",shmid2);
    int  *Y   =(int *)attachSharedMemory(shmid2);
    int *values=(int *)malloc(sizeof(int *)*2);
    *values=0;*(values+1)=0;
    initSemaphore(semid,values);
    *X=0;
    while(1)
	{
	 // write(x)
	  printf("P1 X=%d,Y=%d",*X,*Y);
	 //V(1)
          V(semid,0);
	 //P(2)
	  P(semid,1);
	 //Read Y
	 //X=Y+1;
	 *X=*Y+1;
	}
} 
