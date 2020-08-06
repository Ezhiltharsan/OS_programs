#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	char pro_id[20];
	int ar,bu,pr;
}pro;

void main()
{
	int n,i,j,k,l,t,t1=0,st,wt,d,tat;
	float avg=0,ta=0;
	printf("enter no of process:");
	scanf("%d",&n);
	pro pro1[n],pro2[n],min;
	for(i=0;i<n;i++)
	{
		printf("process-%d\n",(i+1));
		printf("enter process id:");
		scanf("%s",pro1[i].pro_id);
		printf("enter arrival time:");
		scanf("%d",&pro1[i].ar);
		printf("enter burst time:");
		scanf("%d",&pro1[i].bu);
		printf("enter priority:");
		scanf("%d",&pro1[i].pr);
	}
	min=pro1[0];
	for(i=0;i<n;i++)
	{
		k=0;
		for(j=0;j<n;j++)
		{
			if(i==0)
			{
				if((j+1)<n)
				{
					if(min.ar==pro1[j+1].ar)
					{
						if(min.pr>pro1[j+1].pr) min=pro1[j+1];
					}
					else
					{
						pro2[i]=min;
						break;
					}
				}
			}
			else if(t1>=pro1[j].ar)
			{
				l=i-1;
				t=0;
				while(l>=0)
				{
					if(strcmp(pro2[l].pro_id,pro1[j].pro_id)!=0) t++;
					l--;
				}
				if(t==i)
				{	 
					if(k==0)
					{
						min=pro1[j];
						k++;
					}
					else
					{ 
						if(min.pr>pro1[j].pr) min=pro1[j];
					}
				}
			}
		}
		pro2[i]=min;
		t1=t1+min.bu;
	}
	printf("\nTabular output\n\n");
	printf("PROCESS TIME\tARRIVAL TIME\tBURST TIME\tPRORITY\tTURN_AROUND TIME\tWAITING TIME\n");
	st=pro2[0].ar;
	wt=0;
	for(i=0;i<n;i++)
	{
		tat=pro2[i].bu+wt;
		printf("%s\t\t",pro2[i].pro_id);
		printf("%d\t\t",pro2[i].ar);
		printf("%d\t\t",pro2[i].bu);
		printf("%d\t\t",pro2[i].pr);
		printf("%d\t\t",wt);
		printf("%d",tat);
		avg=avg+wt;
		ta=ta+tat;
		if(i<n)
		{
			if((pro2[i].bu+st)<pro2[i+1].ar)
			{
				wt=0;
				st=pro2[i+1].ar;
			}
			else
			{
				st=st+pro2[i].bu;
				wt=st-pro2[i+1].ar;
			}
		}
		printf("\n");
	}
	printf("average waiting time:%f\n",avg/n);
	printf("average turnaround time:%f\n",ta/n);
	printf("\nGantt chart\n\n|");
	if(pro2[0].ar!=0)
	{
		for(i=0;i<pro2[0].ar;i++) printf(" ");
		printf("|");
	}
	for(i=0;i<n;i++)
	{
		printf("%s",pro2[i].pro_id);
		for(j=0;j<(pro2[i].bu-1);j++) printf("   ");
		printf("|");
	}
	printf("\n");
	if(pro2[0].ar!=0)
	{
		printf("0");
		for(i=0;i<pro2[0].ar;i++) printf("  ");
	}
	d=pro2[0].ar;
	for(i=0;i<n;i++)
	{
		printf("%d",d);
		for(j=0;j<(pro2[i].bu);j++) printf("  ");
		if(pro2[i+1].ar>(pro2[i].bu+d)) d=pro2[i+1].ar;
		else d=d+pro2[i].bu;
	}
	printf("%d",d);
}			

