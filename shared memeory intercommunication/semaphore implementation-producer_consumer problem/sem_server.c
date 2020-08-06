#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include<unistd.h>

#define SIZE 10
#define SHMPERM 0666

extern int errno;
int segid;
int empty_id;
int full_id;
int mutex_id;
char *buff;
sem_t *empty;
sem_t *full;
sem_t *mutex;

void produce(int n)
{
	int i,a,c=0;
	for(i=0;i<n;i++)
	{
		a=rand();
		sem_wait(empty);
		sem_wait(mutex);
		buff[0]=a;
		printf("\nproduced item-%d:%d\n\n",(i+1),buff[0]);
		sem_post(mutex);
		sem_post(full);
		sleep(1);
	 }
	sem_wait(empty);
	sem_wait(mutex);
	buff[0]=' ';
	sem_post(mutex);
	sem_post(full);
	return;
}


void main()
{
	int n;
	segid = shmget (100, SIZE, IPC_CREAT| SHMPERM );
	empty_id=shmget(101,sizeof(sem_t),IPC_CREAT|SHMPERM);
	full_id=shmget(102,sizeof(sem_t),IPC_CREAT|SHMPERM);
	mutex_id=shmget(103,sizeof(sem_t),IPC_CREAT|SHMPERM);
	buff = shmat( segid,0,0);
	empty = shmat(empty_id,0,0);
	full = shmat(full_id,0,0);
	mutex = shmat(mutex_id,0,0);
	sem_init(empty,1,SIZE);
	sem_init(full,1,0);
	sem_init(mutex,1,1);
	printf("enter n value:");
	scanf("%d",&n);
	printf("\n SERVER \n\n");
	produce(n);
	printf("\n SERVER FINISHED \n");
}
