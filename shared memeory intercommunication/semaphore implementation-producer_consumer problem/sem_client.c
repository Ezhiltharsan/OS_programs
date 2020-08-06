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

extern int errno;

#define SIZE 10
#define SHMPERM 0666

int segid;
int empty_id;
int full_id;
int mutex_id;
char * buff;
sem_t *empty;
sem_t *full;
sem_t *mutex;

void consume()
{
	int i=1;
	do
	{
		sem_wait(full);
		sem_wait(mutex);
		if(buff[0]!=' ') printf("\nconsumed item-%d:%d\n",i,buff[0]);
		else return;
		sem_post(mutex);
		sem_post(empty);
		i++;
		sleep(1);				
	}while(1);
}


void main()
{
	segid = shmget(100,SIZE,0);
	empty_id=shmget(101,sizeof(sem_t),0);
	full_id=shmget(102,sizeof(sem_t),0);
	mutex_id=shmget(103,sizeof(sem_t),0);
	buff = shmat( segid,0, 0 );
	empty = shmat(empty_id,0,0);
	full = shmat(full_id,0,0);
	mutex = shmat(mutex_id,0,0);
	printf("\n CLIENT \n");
	consume();
	printf("\n CONSUMER FINISHED \n");
	shmdt(buff);
	shmdt(empty);
	shmdt(full);
	shmdt(mutex);
	shmctl(segid, IPC_RMID, NULL);
	semctl( empty_id, 0, IPC_RMID, NULL);
	semctl( full_id, 0, IPC_RMID, NULL);
	semctl( mutex_id, 0, IPC_RMID, NULL);
	sem_destroy(empty);
	sem_destroy(full);
	sem_destroy(mutex);
}
