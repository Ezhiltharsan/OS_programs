#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 50


int* fframe(char phy[],int a)
{
	static int f[MAX];
	int i,j=0;
	for(i=0;i<a;i++) f[i]=-1;
	for(i=0;i<a;i++)
	{
		if(phy[i]=='h')
		{
			f[j]=i;
			j++;
		}
	}
	f[MAX-1]=j-1;
	return f;
}

void preq(char phy[],int a,int b,char na[])
{
	int n,*p,n1,i;
	char c[2],d;
	printf("enter process name:");
	scanf("%s",c);
	d=c[1];
	for(i=0;i<MAX;i++)
	{
		if(na[i]=='\0')
		{
			na[i]=d;
			break;
		}
	}
	printf("enter mem:");
	scanf("%d",&n);
	printf("\nprocess is divided into %d frames\n",n/b);
	printf("page table for process-%s\n\n",c);
	p=fframe(phy,a);
	n1=n%b;
	n1=(n/b)+n1;
	if(*(p+49)>=n1)
	{
		for(i=0;i<n1;i++)
		{
			printf("page-%d:frame-%d\n",(i+1),*(p+i));
			phy[*(p+i)]=d;
		}
	}
	else printf("frames not available");
	return;
}

void deall(char phy[],int a,char na[])
{
	int i;
	char b[2],c;
	printf("enter process to deallocated:");
	scanf("%s",b);
	c=b[1];
	for(i=0;i<a;i++) if(phy[i]==c) phy[i]='h';
	for(i=0;i<MAX;i++)
	{
		if(na[i]==c)
		{
			if(na[i+1]=='\0') na[i]='\0';
			else for(i=i;i<MAX;i++) na[i]=na[i+1];
			break;
		}
	}
	return;
}

void display(char phy[],int a,char na[])
{
	int i=0,j,k;
	while(na[i]!='\0')
	{
		k=0;
		printf("\npage table-P%c\n\n",na[i]);
		for(j=0;j<a;j++) if(phy[j]==na[i]) printf("page-%d:frame-%d\n",k++,j);
		i++;
	}
	return;
}

void main()
{
	srand(time(0));
	int ran,n,i,n1,a,*p;
	printf("\nPAGING TECHNIQUE\n");
	printf("\nPHYSICAL MEMORY\n\n");
	do
	{
		printf("enter phy mem size:");
		scanf("%d",&n);
		printf("enter page size:");
		scanf("%d",&n1);
		if(n%n1==0) printf("phy mem is divided into %d frames",n/n1);
		else printf("enter correct values");
	}while(n%n1);
	a=n/n1;
	char phy[a],na[MAX];
	for(i=0;i<MAX;i++) na[i]='\0';
	for(i=0;i<a;i++) phy[i]='h';
	for(i=0;i<((a/2)-2);i++)
	{
		ran=rand()%(a-1);
		phy[ran]='f';
	}
	p=fframe(phy,a);
	i=0;
	while(i!=-1)
	{
		if(*(p+i)==-1)
		{
			if(i==0)
			{
				printf("no free frames");
				i=-1;
			}
			else i=-1;
		}
		else
		{
			if(i==0) printf("\nfree frames\n");
			printf("%d  ",*(p+i));
			i++;
		}
	}
	do
	{	
		printf("\n\n1-Process request\n2-Deallocation\n3-Page Table display\n4-Free Frame display\n5-Exit\n\n");
		printf("enter option:");
		scanf("%d",&n);
		switch(n)
		{
			case 1: preq(phy,a,n1,na);
				break;
			case 2: deall(phy,a,na);
				break;
			case 3: display(phy,a,na);
				break;
			case 4: p=fframe(phy,a);
				i=0;
				while(i!=-1)
				{
					if(*(p+i)==-1)
					{
						if(i==0)
						{
							printf("no free frames");
							i=-1;
						}
						else i=-1;
					}
					else
					{
						if(i==0) printf("\nfree frames\n");
						printf("%d  ",*(p+i));
						i++;
					}
				}
				break;
			case 5: exit(0);
				break;
			default: printf("printf enter correct option");
		}
	}while(n!=5);
}
