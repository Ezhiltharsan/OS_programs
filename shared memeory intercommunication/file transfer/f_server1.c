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
	int id,f1,co,id1;
	id=shmget(111,500,0);
	id1=shmget(222,50,0);
	a=shmat(id,NULL,0);
	b=shmat(id1,NULL,0);
	while(b[0]=='1');
	f1=open(a,O_RDONLY);
	if(f1==-1)
	{
		b[0]='3';
		shmdt(a);
		shmdt(b);
		printf("file not exists");
		exit(0);
	}
        co=read(f1,a,500);
	b[0]='1';
	close(f1);
	shmdt(a);
	shmdt(b);
	printf("\nend\n");
}

