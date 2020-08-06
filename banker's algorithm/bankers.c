#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	int n,i,n1,j;
	printf("enter no of process:");
	scanf("%d",&n);
	printf("enter no of resources:");
	scanf("%d",&n1);
	int al[n][n1],av[n1],max[n][n1],need[n][n1],sa[n],k=0,co,ch;
	for(i=0;i<n;i++) sa[i]=-1;
	printf("enter available instances of resources\n\n");
	for(i=0;i<n1;i++)
	{
		printf("resource-%d\n",i+1);
		scanf("%d",&av[i]);
	}
	printf("\nenter maximum need of process");
	for(i=0;i<n;i++)
	{
		printf("\n\nprocess-%d\n",i+1);
		for(j=0;j<n1;j++)
		{
			printf("\nresource-%d:",j+1);
			scanf("%d",&max[i][j]);
		}
	}
	printf("\nenter allocated instance of process");
	for(i=0;i<n;i++)
	{
		printf("\n\nprocess-%d\n",i+1);
		for(j=0;j<n1;j++)
		{
			printf("\nresource-%d:",j+1);
			scanf("%d",&al[i][j]);
		}
	}
	for(i=0;i<n;i++) for(j=0;j<n1;j++) need[i][j]=max[i][j]-al[i][j];
	do
	{
                ch=0;
                co=0;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n1;j++) if(av[j]>=need[i][j]) co++;
			if(co==n1)
			{
				for(j=0;j<n1;j++)
                                {
                                        need[i][j]=0;
					av[j]+=al[i][j];
                                        al[i][j]=0;
                                }
                                co=0;
                                for(j=0;j<n;j++) if(sa[j]!=i) co++;
				if(co==n)
                                {
                                        sa[k]=i;
                                        k++;
					ch++;
                                }
		        }
			co=0;
                }
        }while(ch>0);
        if(k!=n) printf("unsafe sequence");
        else
	{
		printf("safe sequence\n");
		for(i=0;i<n;i++) printf("%d\t",sa[i]);
	}
}

