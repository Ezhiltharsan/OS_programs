#include <sys/ipc.h>
# define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>

void main()
{
	char *b;
	int id;
	id=shmget(111,50,0);
	b=shmat(id,NULL,0);
	while(b[0]=='#');
	printf("\n child %s\n",b);
	shmdt(b);
	shmctl(id, IPC_RMID,NULL);
}
