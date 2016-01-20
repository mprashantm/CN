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
    int shmid1=createSharedMemory(key2,10);//x
    printf("shmid1 %d from main\n",shmid1);
    char *X   =(char *)attachSharedMemory(shmid1); 
//    int shmid2=createSharedMemory(key3,10);//y
  //  printf("shmid2 %d from main\n",shmid2);
    char *Y  ; //=//(char *)attachSharedMemory(shmid2);
    int *values=(int *)malloc(sizeof(int *)*2);
    *values=0;*(values+1)=0;
    initSemaphore(semid,values);
/*    V(semid,0);
    printf("hi");
    P(semid,0);
*/   
    int x=0,y=0,i;
    while(1)
	{
	 // write(x)
 	  i=0;
	  printf("P1 X=%d Y=%d\n",x,y);
          while(x>0)
		{
		  *X=x%10-'0';x/=10;X++;i++;
		}
	  printf("*\n");
	  *X='\0';
	  printf("*\n");
	  X-=i;//X Points to start of shared memory  	
	 //V(1)
          V(semid,0);
	 //P(2)
	  P(semid,1);
	 //Read Y
          i=0;
	  while(*Y!='\0')
		{
		   y=y*10+(*Y+'0');Y++;i++;
		}
	  Y-=i; 
	 //X=Y+1;
	  x=y+1;	
	   printf("P1 X=%d Y=%d\n",x,y);
	}
} 
