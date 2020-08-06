#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char pro_id[20];
	int ar,bu,st,ft,wt,tat;
}pro;

void main()
{
	int i,n,k=0,t,j,m=0,u,v,l=1,co,w=0,d;
	float ta,avg;
	printf("enter no of process:");
	scanf("%d",&n);
	pro pro1[n],pro2[100],min;
	for(i=0;i<n;i++)
	{
		printf("process-%d\n",(i+1));
		printf("enter process id:");
		scanf("%s",pro1[i].pro_id);
		printf("enter arrival time:");
		scanf("%d",&pro1[i].ar);
		printf("enter burst time:");
		scanf("%d",&pro1[i].bu);
	}
	t=pro1[0].ar;
	for(i=0;i<(n-1);i++)
	{
		if(t==pro1[(i+1)].ar)
		{
			for(j=(i+1);j<n;j++)
			{
				if((pro1[j].ar==pro1[i].ar)&&(pro1[i].bu>pro1[j].bu))
				{
					min=pro1[j];
					pro1[j]=pro1[i];
					pro1[i]=min;
				}
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(t==pro1[i].ar)
		{
			pro2[k]=pro1[i];
			k++;
		}
		else break;
	}
	while(i<n)
	{
		for(j=m;j<k;j++)
		{
			if((pro1[i].ar<=(pro2[j].bu+w)) && (pro1[i].bu<=pro2[j].bu))
			{
				m=k-1;
				while(m>j)
				{
					pro2[(m+1)]=pro2[m];
					m--;
				}
				m=m+1;
				pro2[m]=pro1[i];
				strcpy(pro2[(k+1)].pro_id,pro2[(m-1)].pro_id);
				pro2[(k+1)].ar=pro2[(m-1)].ar;
				pro2[(k+1)].bu=pro2[(m-1)].bu-(pro2[m].ar-pro2[m-1].ar);
				k=k+2;
				for(u=m+1;u<(k-1);u++)
				{
					for(v=u+1;v<k;v++)
					{
						if(pro2[u].bu>pro2[v].bu)
						{
							min=pro2[u];
							pro2[u]=pro2[v];
							pro2[v]=min;
						}
					}
				}
				break;
			}
			else
			{
				pro2[k]=pro1[i];
				k=k+1;
				for(u=m+1;u<(k-1);u++)
				{
					for(v=u+1;v<k;v++)
					{
						if(pro2[u].ar==pro2[v].ar)
						{
							if((pro2[u].bu)>pro2[v].bu)
							{
								min=pro2[u];
								pro2[u]=pro2[v];
								pro2[v]=min;
							}
						}
						else
						{
							if((pro2[u].bu-l)>pro2[v].bu)
							{
								min=pro2[u];
								pro2[u]=pro2[v];
								pro2[v]=min;
							}
						}
					}
				}
				l++;
				break;
			}
			w=w+pro2[j].bu;
		}
		i++;
	}
	if((pro2[0].bu>pro2[1].bu)&&(pro2[0].bu>pro2[1].ar))
	{
		pro2[0].st=0;
		pro2[0].ft=pro2[1].ar;
	}
	else
	{
		pro2[0].st=0;
		pro2[0].ft=pro2[0].bu;
	}
	co=pro2[0].ft;	
	for(i=1;i<k;i++)
	{
			pro2[i].st=co;
			if((pro2[i-1].bu>pro2[i].bu)&&(pro2[i-1].bu>pro2[i].ar))
			{
				if((pro2[i].bu>pro2[i+1].ar)&&(pro2[i].bu>pro2[i+1].bu))
				{
					pro2[i].ft=pro2[i].bu-pro2[i+1].ar;
					co+=pro2[i].ft;
					co-=1;
				}
				else
				{
					co+=pro2[i].bu;
					pro2[i].ft=co;
				}
			}
			else
			{
				if((pro2[i].bu>pro2[i+1].ar)&&(pro2[i].bu>pro2[i+1].bu))
				{
					pro2[i].ft=pro2[i].bu-pro2[i+1].ar;
					co+=pro2[i].ft;
					co-=1;
				}
				else
				{
					co+=pro2[i].bu;
					pro2[i].ft=co;
				}
			}
	}
	for(i=0;i<k;i++)
	{
		co=0;
		u=-1;
		for(j=0;j<k;j++)
		{
			if(strcmp(pro2[i].pro_id,pro2[j].pro_id)!=0) co++;
			else for(l=j;l<i;l++) if(strcmp(pro2[i].pro_id,pro2[l].pro_id)==0) u=l;
		}
		if(co==k-1)
		{
			if(pro2[i].st==pro2[i].ar) pro2[i].wt=0;
			else pro2[i].wt=pro2[i].st-pro2[i].ar;
		}
		else
		{
			if(u==-1)
			{
				if(pro2[i].st==pro2[i].ar) pro2[i].wt=0;
				else pro2[i].wt=pro2[i].st-pro2[i].ar;
			}
			else
			{
				m=pro2[i].st-pro2[u].ft;
				pro2[i].wt=pro2[u].wt+m;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		co=0;
		for(j=(i+1);j<k;j++)
		{
			if(strcmp(pro2[i].pro_id,pro2[j].pro_id)!=0) co++;
			else break;
		}
		if(co==(k-(i+1)))
		{
			u=-1;
			for(l=0;l<(i-1);l++) if(strcmp(pro2[i].pro_id,pro2[l].pro_id)==0) u=l;
			if(u==-1) u=i;
			pro2[i].tat=pro2[i].ft-pro2[u].ar;
		}
		else pro2[j].tat=0;
	}
	printf("\nTabular output\n\n");
	printf("PROCESS TIME\tARRIVAL TIME\tBURST TIME\tTURN_AROUND TIME\tWAITING TIME\n");
	for(i=0;i<k;i++)
	{
		printf("%s\t\t",pro2[i].pro_id);
		printf("%d\t\t",pro2[i].ar);
		printf("%d\t\t",pro2[i].bu);
		printf("%d\t\t",pro2[i].wt);
		printf("%d",pro2[i].tat);
		printf("\n");
		avg=avg+pro2[i].wt;
		ta=ta+pro2[i].tat;
	}
	printf("average waiting time:%f\n",avg/n);
	printf("average turnaround time:%f\n",ta/n);
	printf("\nGantt chart\n\n|");
	if(pro2[0].ar!=0)
	{
		for(i=0;i<pro2[0].ar;i++) printf(" ");
		printf("|");
	}
	for(i=0;i<k;i++)
	{
		printf("%s",pro2[i].pro_id);
		for(j=0;j<(pro2[i].bu-1);j++) printf("  ");
		printf("|");
	}
	printf("\n");
	if(pro2[0].ar!=0)
	{
		printf("0");
		for(i=0;i<pro2[0].ar;i++) printf("  ");
	}
	for(i=0;i<k;i++)
	{
		printf("%d",pro2[i].st);
		for(j=0;j<(pro2[i].bu);j++) printf("  ");
	}
	printf("%d",pro2[i-1].ft);				
}


