#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "1.cpp"
#define SEMKEY  0x1234
#define SHMKEY1 0x4321
#define SHMKEY2 0x4312
using namespace std;
int main()
{
    int semid =createSemaphore(SEMKEY,2);//S1 S2
    int shmid1=createSharedMemory(SHMKEY1,10);//x
    char *X   =(char *)attachSharedMemory(shmid1);
    int shmid2=createSharedMemory(SHMKEY2,10);//y
    char *Y   =(char *)attachSharedMemory(shmid2);
    int *values=(int *)malloc(sizeof(int *)*2);
    *values=0;*(values+1)=0;
    initSemaphore(semid,values);
    int x=0,y=0,i;
    while(1)
        {
	   printf("P2 X=%d Y=%d\n",x,y); 
	 //P(1)
	   P(semid,0);
	 //read(X)
	 i=0;
/*          while(*X!='\0')
                {
                   x=x*10+(*X+'0');X++;i++;
                }
	  X-=i;
	  y=x+1;
*/          //write(Y)	
    	  i=0;
	printf("P2 X=%d Y=%d\n",x,y);	
/*           while(y>=0)
                {
                  *Y=y%10-'0';y/=10;Y++;i++;
                }
          *Y='\0';
          Y-=i;     
*/         //V(2)
          V(semid,1);
        }
}

