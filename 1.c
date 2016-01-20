#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>
//using namespace std;
union semun {
 int val;
 struct semid_ds *buf;
 unsigned short int *array;
 };
int createSemaphore(int semkey,int no_of_semaphore)
{
    int semid;
    if((semid=semget(semkey,no_of_semaphore,IPC_CREAT|0666))<0)//for s1,s2
     {
       printf("error in creating semaphore\n");
        exit(1);
     }
    printf("semid = %d\n",semid);
    return semid;
}

int initSemaphore(int semid,int *array)
{
 union semun temp;
 temp.array=(unsigned short int*)array;
 return semctl(semid, 0, SETALL, temp);
}

int createSharedMemory(int shmkey,int bytes)
{
    int shmid;
     if(shmid=shmget(shmkey,bytes,IPC_CREAT|0700)<0)
     {
        printf("error in creating shared memory\n");
        exit(1);
     }
     printf("shmid =%d",shmid);
     return shmid;
}
void* attachSharedMemory(int shmid)
{
     void *address;
     if((address=shmat(shmid,NULL,0))==(void *)0)
     {
       printf("error in attaching shared memory\n");
        exit(1);
     }
     return address;
}
void destroySharedMemory(int shmkey)
{
  shmctl(shmkey,IPC_RMID,NULL);
}
void destroySemaphore(int semkey)
{
  semctl(semkey,0,IPC_RMID); 
}
void P(int id,int i)
{
  struct sembuf sb;
  sb.sem_num = i;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  semop(id, &sb, 1);
}
void V(int id, int i)
{
  struct sembuf sb;
  sb.sem_num = i;
  sb.sem_op = 1;
  sb.sem_flg = SEM_UNDO;
  semop(id, &sb, 1);
}
