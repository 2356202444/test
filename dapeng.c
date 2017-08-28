

#include"1.h"


/*************************************************************

智能农场大棚：大棚端（数据传输、处理、检测、控制面板）



*********************************************************/

int tem();
int shidu();
int guangzhao();
int CO2();
int N();
sem_t sem;
DPL *p2;
char qt[10]={0};
void *fun(void *arg)
{
	DPL *p=(DPL *)arg;
	printf("\n\n\n\n");
	printf("%d\n",p->tem);
}
int temp(int m,int *c,DPL *p)//温度
{
	if(*c==0&&m<25)
	{
	strcpy(p->wd,"打开暖气");
	printf("打开暖气\n");
	*c=1;
	return *c;}
	else if(*c==1&&m>40)
	{
	strcpy(p->wd,"关闭暖气并通风");
	printf("关闭暖气并通风\n");
	*c=0;
	return *c;
	}
	else if(*c == 0&&m>40)
	{
	strcpy(p->wd,"通风");
		printf("通风\n");
	return *c;
	}
	else 
	{
	strcpy(p->wd,"正常室温");
	printf("正常室温\n");
	*c=0;
	return *c;
	}
}


int gzh(int m,int *c, DPL *p)//光照
{
	if(*c==0&&m<200)
	{
	strcpy(p->gz,"打开灯光");
	printf("打开灯光\n");
	*c=1;
	return *c;}
	else if(*c==1&&m>400)
	{
	strcpy(p->gz,"关闭灯光打开遮阳伞");
	printf("关闭灯光打开遮阳伞\n");
	*c=0;
	return *c;
	}
	else if(*c == 0&&m>400)
	{
	strcpy(p->gz,"打开遮阳伞");
		printf("打开遮阳伞\n");
	return *c;
	}
	else 
	{
	strcpy(p->gz,"正常光照");
	printf("正常光照\n");
	*c=0;
	return *c;
	}
}

int shd(int m,int *c,DPL *p)
{
	if(*c==0&&m<50)
	{
	strcpy(p->sd,"打开水龙头");
	printf("打开水龙头\n");
	*c=1;
	return *c;}
	else if(*c==1&&m>80)
	{
	strcpy(p->sd,"关闭水龙头警报");
	printf("关闭水龙头警报\n");
	*c=0;
	return *c;
	}
	else if(*c == 0&&m>80)
	{
	strcpy(p->sd,"警报");
		printf("警报\n");
	return *c;
	}
	else 
	{
	strcpy(p->sd,"正常土壤湿度");
	printf("正常土壤湿度\n");
	*c=0;
	return *c;
	}
	
}

int t2(int m,int *c,DPL *p)
{
	if(*c==0&&m>4)
	{
	strcpy(p->et,"打开通风口降低co2");
	printf("打开通风口降低co2\n");
	*c=1;
	return *c;}
	else if(*c==1&&m<4)
	{
	strcpy(p->et,"关闭通风口1");
	printf("关闭通风口1\n");
	*c=0;
	return *c;
	}
	else if(*c == 0&&m<4)
	{
	strcpy(p->et,"正常CO2浓度");
		printf("正常CO2浓度\n");
	return *c;
	}

	
}

int yangfen(int m,int *c, DPL *p)
{
	if(*c==0&&m<10)
	{
	strcpy(p->yf,"混合肥料噴灌");
	printf("混合肥料噴灌\n");
	*c=1;
	return *c;
	}
	else if(*c==1&&m>15)
	{
	strcpy(p->yf,"关闭噴灌1");
	printf("关闭噴灌1\n");
	*c=0;
	return *c;
	}
	else if(*c == 0&&m>15&&m<20)
	{
	strcpy(p->yf,"正常养分浓度");
		printf("正常养分浓度\n");
	return *c;
	}
	
}


void *fun1(void *arg)
{
	char buf[100]={0};
	char c='1',a='0';
	int sock = *((int*)arg);
	int ret = 0;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret = read(sock,buf,sizeof(buf));
		if(ret < 0)
		{
		 	perror("read");
			exit(-1);
		}
		printf("数据为：%s\n",buf);
		if(buf[0]=='1'&&buf[1]=='1'&&p2 != NULL)
		{

			if(p2->s==0)
			{

				strcpy(qt,"成功");
                printf("打开暖气成功:\n");
				
			}
			else
			{
		printf("数据为：%s\n",buf);
				strcpy(qt,"错误");
                printf("打开暖气失败:\n");
				
				
			}
		}
		if(buf[0]=='1'&&buf[1]=='2'&&p2 != NULL)
		{
			if(p2->a==0)
			{
				strcpy(qt,"成功");
                printf("打开棚顶成功:\n");
				
			}
			else
			{
				strcpy(qt,"错误");
                printf("打开棚顶失败:\n");
				
				
			}
		}
		if(buf[0]=='1'&&buf[1]=='3'&&p2 != NULL)
		{
			if(p2->b==0)
			{
				strcpy(qt,"成功");
                printf("加热成功:\n");
				
			}
			else
			{
				strcpy(qt,"错误");
                printf("加热失败:\n");
				
			}
		}
		if(buf[0]=='1'&&buf[1]=='4'&&p2 != NULL)
		{
			if(p2->c==0)
			{
				strcpy(qt,"成功");
                printf("通风成功:\n");
				
			}
			else
			{
				strcpy(qt,"错误");
                printf("通风失败:\n");
				
				
			}
		}	
		if(buf[0]=='1'&&buf[1]=='5'&&p2 != NULL)
		{
			if(p2->d==0)
			{	
				strcpy(qt,"成功");
                printf("施肥成功:\n");
				
			}
			else
			{
				strcpy(qt,"错误");
                printf("施肥失败，正在工作:\n");
				
			
			}
		}	
	}
}
#define PART  12345
int main()
{
	struct sockaddr_in headdr;
	memset(&headdr,0,sizeof(headdr));
	headdr.sin_family = AF_INET;
	headdr.sin_port = htons(PART);
	headdr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int sock ;
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock <0)
	{
		perror("soxket");
		exit(-1);
	}
	int ret = 0;
	ret = connect(sock,(struct sockaddr*)&headdr,sizeof(headdr));
	if(ret < 0)
	{
	 	perror("socket");
		exit(-1);
	}
	ret =write(sock,"$$12",sizeof("$$12"));
	if(ret < 0)
	{
	 	perror("write");
		exit(-1);
	}
	int a1 = 0,b1 = 0,c1 = 0,d1 = 0,e1 = 0;	
	DPL *p;
	p=malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	p2=malloc(sizeof(DPL));
	memset(p2,0,sizeof(DPL));
	pthread_t th,th1,th2;
	pthread_create(&th1,NULL,fun1,&sock);
	
//	pthread_create(&th2,NULL,fun2,p);
	while(1)
	{
	p->tem=tem();
	p->s=temp(p->tem,&c1,p);
	printf("%d\n",p->s);
	p-> guangzhao=guangzhao();
	p->shidu=shidu();
	p->co2=CO2();
	p->N=N();
	p->a=gzh(p->guangzhao,&a1,p);
	p->b=shd(p->shidu,&b1,p);
	p->c=t2(p->co2,&d1,p);
	p->d=yangfen(p->N,&e1,p);
	p2=p;
	printf("%s\n",p->wd);
	printf("%d\n",tem());
	printf("%d PF\n",shidu());
	printf("%d LX\n",guangzhao());
	printf("%d LX\n",N());
	printf("%d LX\n",CO2());
//	memset(p,0,sizeof(DPL));
	ret = write(sock,p,sizeof(DPL));
	if(ret < 0)
	{
		perror("write");
		exit(-1);
	}
	memset(p,0,sizeof(DPL));
	
	
	sleep(5);
	}
	pthread_join(th1,NULL);
}


int tem()
{
	int i;
srand((int) time(0));
	i = 10+(int) (40.0 *rand()/(RAND_MAX+1.0));
	return i;
}


int shidu()
{
	int i;
	srand((int) time(0));
	i = 30+(int) (60.0 *rand()/(RAND_MAX+1.0));
	return i;
}

int guangzhao()
{
	int i;
	srand((int) time(0));
	i = 0.0+(int) (500.0 *rand()/(RAND_MAX+1.0));
	return i;
}


int N()
{
	int i;
	srand((int) time(0));
	i = 1.0+(int) (20.0 *rand()/(RAND_MAX+1.0));
	return i;
	
}


int CO2()
{
	int i;
	srand((int) time(0));
	i = 1.0+(int) (10.0 *rand()/(RAND_MAX+1.0));
	return i;
	
}
