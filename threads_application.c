#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int min,max,len;
float avg=0;

void *average(void *param)
{
	int i,*arr=(int *) param;
	for(i=0;i<len;i++) avg=avg+arr[i];
	avg=avg/len;
	pthread_exit(0);
}

void *minimum(void *param)
{
	int i,*arr=(int *) param;
	min=arr[0];
	for(i=1;i<len;i++) if(min>arr[i]) min=arr[i];
	pthread_exit(0);
}

void *maximum(void *param)
{
	int i,*arr=(int *) param;
	max=arr[0];
	for(i=1;i<len;i++) if(max<arr[i]) max=arr[i];
	pthread_exit(0);
}

void main(int argc, char *argv[])
{
	int i,*arr;
	pthread_t tid,tid1,tid2;
	pthread_attr_t attr,attr1,attr2;
	if(argc==1)
	{
		printf("not enough arguments\n");
		exit(0);
	}
	len=argc-1;
	arr=(int*)malloc(len*sizeof(int));
	for(i=1;i<argc;i++) arr[i-1]=atoi(argv[i]);
	pthread_attr_init(&attr);
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_create(&tid,&attr,average,(void*) arr);
	pthread_create(&tid1,&attr1,minimum,(void*) arr);
	pthread_create(&tid2,&attr2,maximum,(void*) arr);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("average:%f\n",avg);
	printf("minimum:%d\n",min);
	printf("maximum:%d\n",max);
}


