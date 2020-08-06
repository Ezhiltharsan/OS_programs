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
#include<fcntl.h>

void main()
{
	char *a,*b;
	int id,id1;
	id=shmget(111,500,0);
	id1=shmget(222,50,0);
	a=shmat(id,NULL,0);
	b=shmat(id1,NULL,0);
	do
	{
		while(b[0]=='1');
		printf("message received\n\n%s\n\n",a);
		if(a[0]=='0')
		{
			printf("conversation closed");
			shmdt(a);
			shmdt(b);
			shmctl(id, IPC_RMID,NULL);
			exit(0);
		}
		printf("enter message or 0 to exit\n\n");
		scanf("\n%[^\n]",a);
		b[0]='1';
	}while(a[0]!='0');
	shmdt(a);
	shmdt(b);
	printf("\nend\n");
}

