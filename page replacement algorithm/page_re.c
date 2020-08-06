#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

void fifo(char a[],int b)
{
	int n,i,j,co,co1=0,co2=0,pf=0;
	n=strlen(a);
	char al[b][n],al1[b];
	for(i=0;i<b;i++) for(j=0;j<n;j++) al[i][j]='\0';
	for(i=0;i<b;i++) al1[i]=' ';
	printf("Page_ref->memory->PF\n\n");
	for(i=0;i<n;i++)
	{
		co=0;
		for(j=0;j<b;j++)
		{
			if(al1[j]==a[i]) break;
			else co++;
		}
		if(co==b)
		{
			if(co1<b)
			{
				al1[co1]=a[i];
				co1++;
			}
			else
			{
				al1[co2]=a[i];
				co2=(++co2)%b;
			}
			pf++;
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->%d\n",pf);
		}
		else
		{
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->-\n");
		}
	}
	printf("\nALLOCATION\n\n");
	for(i=0;i<b;i++)
	{
		for(j=0;j<n;j++) printf("%c ",al[i][j]);
		printf("\n");
	}
	printf("\npage fault:%d\n",pf);		
	return;
}

void lru(char a[],int b)
{
	int n,i,j,co,co1=0,co2=0,pf=0;
	n=strlen(a);
	char al[b][n],al1[b];
	for(i=0;i<b;i++) for(j=0;j<n;j++) al[i][j]='\0';
	for(i=0;i<b;i++) al1[i]=' ';
	printf("Page_ref->memory->PF\n\n");
	for(i=0;i<n;i++)
	{
		co=0;
		for(j=0;j<b;j++)
		{
			if(al1[j]==a[i]) break;
			else co++;
		}
		if(co==b)
		{
			if(co1<b)
			{
				al1[co1]=a[i];
				co1++;
			}
			else
			{
				al1[co2]=a[i];
				co2=(++co2)%b;
			}
			pf++;
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->%d\n",pf);
		}
		else
		{
			printf("%c->",a[i]);
			if(co1>=b) if(al1[co2]==a[i]) co2=(++co2)%b;
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->-\n");
		}
	}
	printf("\nALLOCATION\n\n");
	for(i=0;i<b;i++)
	{
		for(j=0;j<n;j++) printf("%c ",al[i][j]);
		printf("\n");
	}
	printf("\npage fault:%d\n",pf);		
	return;
}

void optimal(char a[],int b)
{
	int n,i,j,k,co,co1=0,co2[b],pf=0,co3;
	n=strlen(a);
	char al[b][n],al1[b];
	for(i=0;i<b;i++) for(j=0;j<n;j++) al[i][j]='\0';
	for(i=0;i<b;i++) al1[i]=' ';
	printf("Page_ref->memory->PF\n\n");
	for(i=0;i<n;i++)
	{
		co=0;
		for(j=0;j<b;j++)
		{
			if(al1[j]==a[i]) break;
			else co++;
		}
		if(co==b)
		{
			if(co1<b)
			{
				al1[co1]=a[i];
				co1++;
			}
			else
			{
				for(j=0;j<b;j++)
				{
					co3=0;
					for(k=i+1;k<n;k++)
					{
						if(al1[j]==a[k]) break;
						else co3++;
					}
					co2[j]=co3;
				}
				k=0;
				for(j=1;j<b;j++) if(co2[k]<co2[j]) k=j;
				al1[k]=a[i];
			}
			pf++;
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->%d\n",pf);
		}
		else
		{
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->-\n");
		}
	}
	printf("\nALLOCATION\n\n");
	for(i=0;i<b;i++)
	{
		for(j=0;j<n;j++) printf("%c ",al[i][j]);
		printf("\n");
	}
	printf("\npage fault:%d\n",pf);
	return;
}

void lfu(char a[],int b)
{
	typedef struct
	{
		char p;
		int c;
	}re;
	re re1[b];
	int n,i,j,co,k,co1=0,co2[b],pf=0;
	n=strlen(a);
	char al[b][n],al1[b],al2;
	for(i=0;i<b;i++)
	{
		re1[i].c=0;
		for(j=0;j<n;j++) al[i][j]='\0';
	}
	for(i=0;i<b;i++) al1[i]=' ';
	printf("Page_ref->memory->PF\n\n");
	for(i=0;i<n;i++)
	{
		co=0;
		for(j=0;j<b;j++)
		{
			if(al1[j]==a[i]) break;
			else co++;
		}
		if(co==b)
		{
			if(co1<b)
			{
				re1[co1].p=a[i];
				re1[co1].c++;
				al1[co1]=a[i];
				co1++;
			}
			else
			{
				k=0;
				for(j=1;j<b;j++) if(re1[j].c<re1[k].c) k=j;
				al2=re1[k].p;
				for(j=0;j<b;j++)
				{
					if(al1[j]==al2) al1[j]=a[i];
					if(re1[j].p==al2)
					{
						re1[j].p=a[i];
						re1[j].c=1;
					}
				}
				for(j=0;j<b;j++) if(re1[j].p!=al2) re1[j].c=0;		
			}
			pf++;
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->%d\n",pf);
		}
		else
		{
			printf("%c->",a[i]);
			for(j=0;j<b;j++)
			{
				if(a[i]==re1[j].p) re1[j].c++; 
				al[j][i]=al1[j];
				printf("%c ",al1[j]);
			}
			printf("->-\n");
		}
	}
	printf("\nALLOCATION\n\n");
	for(i=0;i<b;i++)
	{
		for(j=0;j<n;j++) printf("%c ",al[i][j]);
		printf("\n");
	}
	printf("\npage fault:%d\n",pf);		
	return;
}

void main()
{
	int n,i,n1;
	char pro[MAX];
	do
	{
		printf("\n\n1-FIFO\n2-LRU\n3-OPTIMAL\n4-LFU\n5-EXIT\n");
		scanf("%d",&n);
		if(n<5)
		{
			printf("enter no of frames:");
			scanf("%d",&n1);
			printf("enter page reference:");
			scanf("%s",pro);
		}
		if(n==1) fifo(pro,n1);
		else if(n==2) lru(pro,n1);
		else if(n==3) optimal(pro,n1);
		else if(n==4) lfu(pro,n1);
		else if(n>5) printf("enter correct option");
	}while(n!=5);
}
