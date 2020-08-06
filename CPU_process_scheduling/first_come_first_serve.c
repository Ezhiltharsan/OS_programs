#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	char pro_id[20];
	int ar,bu;
}pro;

void main()
{
	int n,i,wt=0,tat,j,d;
	printf("enter no of process:");
	scanf("%d",&n);
	pro pro1[n];
	for(i=0;i<n;i++)
	{
		printf("process-%d\n",(i+1));
		printf("enter process id:");
		scanf("\n%s",pro1[i].pro_id);
		printf("enter arrival time:");
		scanf("\n%d",&pro1[i].ar);
		printf("enter burst time:");
		scanf("\n%d",&pro1[i].bu);
	}
	printf("\nTabular output\n\n");
	printf("PROCESS TIME\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURAROUND TIME\n");
	for(i=0;i<n;i++)
	{
		tat=pro1[i].bu+wt;
		printf("%s\t\t",pro1[i].pro_id);
		printf("%d\t\t",pro1[i].ar);
		printf("%d\t\t",pro1[i].bu);
		printf("%d\t\t",wt);
		printf("%d",tat);
		if(i<n) wt=(pro1[i].bu-pro1[i+1].ar)+pro1[i].ar;
		printf("\n");
	}
	printf("\nGantt chart\n\n|");
	if(pro1[0].ar!=0) for(i=0;i<pro1[0].ar;i++) printf("   |");
	for(i=0;i<n;i++)
	{
		printf("%s",pro1[i].pro_id);
		for(j=0;j<(pro1[i].bu-1);j++) printf("   ");
		printf("|");
	}
	printf("\n");
	if(pro1[0].ar!=0)
	{
		printf("0");
		for(i=0;i<pro1[0].ar;i++) printf("  ");
	}
	d=pro1[0].ar;
	for(i=0;i<n;i++)
	{
		printf("%d",d);
		for(j=0;j<(pro1[i].bu);j++) printf("  ");
		d=d+pro1[i].bu;
	}
	printf("%d",d);
}
