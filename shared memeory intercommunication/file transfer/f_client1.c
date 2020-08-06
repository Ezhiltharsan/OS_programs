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
	char *a,*b;
	int id,id1;
	id=shmget(111,500,IPC_CREAT | 00666);
	id1=shmget(222,50,IPC_CREAT | 00666);
	a=shmat(id,NULL,0);
	b=shmat(id1,NULL,0);
	b[0]='1';
	printf("\nenter file name:");
	scanf("%s",a);
	b[0]='0';
	while(b[0]=='0');
	if(b[0]=='3')
	{
		printf("server unable to send");
		shmdt(a);
		shmdt(b);
		shmctl(id, IPC_RMID,NULL);
		exit(0);
	}
	printf("%s",a);
	shmdt(a);
	shmdt(b);
	shmctl(id, IPC_RMID,NULL);
	shmctl(id1, IPC_RMID,NULL);
	printf("\nend\n");
}
