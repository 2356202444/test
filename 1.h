#ifndef _1_H
#define _1_H


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<semaphore.h>
#include<signal.h>
#include<time.h>
#include<mysql/mysql.h>

typedef struct dapeng
{
	int tem;//温度
	int guangzhao;//光照
	int shidu;//湿度
	int co2;//CO2浓度
	int N;//土壤中养分含量
	int s;//温度反馈
	int a;//光照反馈
	int b;//湿度反馈
	int c;//CO2浓度反馈
	int d;//养分反馈
	char wd[30];
	char gz[30];
	char sd[30];
	char et[30];
	char yf[30];
}DPL;

#define PART 12345
#endif
