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
	char *a;
	int id;
	id=shmget(111,50,IPC_CREAT | 00666);
	a=shmat(id,NULL,0);
	a[0]='#';
	scanf(" %s",a);
	shmdt(a);
}
