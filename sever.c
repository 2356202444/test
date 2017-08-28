
#include"1.h"


/*****************************************************

项目名称：智能农场大棚管理系统  （服务器端）

*************************************************/
#define PATR 12345
sem_t sem;
void jieshou(DPL *p)
{
			
					
					
	printf("温度    ：%d\t  温度反馈    ：%d\t  温度描述    ：%s\n",p->tem,p->s,p->wd);
	printf("光照    ：%d\t  光照反馈    ：%d\t  光照描述    ：%s\n",p->guangzhao,p->a,p->gz);
	printf("湿度    ：%d\t  湿度反馈    ：%d\t  湿度描述    ：%s\n",p->shidu,p->b,p->sd);
	printf("co2含量 ：%d\t  CO2含量反馈 ：%d\t  CO2描述     ：%s\n",p->co2,p->c,p->et);
	printf("土壤肥力：%d\t  土壤肥力反馈：%d\t  土壤肥力描述 ：%s\n",p->N,p->d,p->yf);
					
}
                    
char buf[100]={0};
int socke;
DPL *p3;
DPL *p4;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void  mysql6(DPL *p)
{
   	p3->tem=p->tem;
	p3->guangzhao=p->guangzhao;
	p3->shidu=p->shidu;
	p3->co2=p->co2;
	p3->N=p->N;
	p3->s=p->s;
	p3->a=p->a;
	p3->b=p->b;
	p3->c=p->c;
	p3->d=p->d;
	strcpy(p3->wd,p->wd);
	strcpy(p3->gz,p->gz);
	strcpy(p3->sd,p->sd);
	strcpy(p3->et,p->et);
	strcpy(p3->yf,p->yf);	
	jieshou(p3);
}
void mysql4(void *arg)
{
	int sock = *((int*)arg);
	DPL *p;
	int x = 0;
	p=(DPL*)malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init(&mysql);
	int ret = 0;
	char sql[500]={0};
	if((mysql_real_connect(&mysql,"localhost","root","123","student",0,NULL,0))==NULL)
	{
		printf("connect error\n");
		exit(-1);
	}
	sprintf(sql,"select * from stu");
	ret = mysql_real_query(&mysql,sql,strlen(sql));
	if(ret < 0)
	{
		printf("query error:%s\n",mysql_error(&mysql));
	
		exit(-1);
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	int i;
	for(i = 0;row != NULL;i++)
	{
	p->tem=atoi(row[0]);
	p->guangzhao=atoi(row[1]);
	p->shidu=atoi(row[2]);
	p->co2=atoi(row[3]);
	p->N=atoi(row[4]);
	p->s=atoi(row[5]);
	p->a=atoi(row[6]);
	p->b=atoi(row[7]);
	p->c=atoi(row[8]);
	p->d=atoi(row[9]);
	strcpy(p->wd,row[10]);
	strcpy(p->gz,row[11]);
	strcpy(p->sd,row[12]);
	strcpy(p->et,row[13]);
	strcpy(p->yf,row[14]);
	ret = write(sock,p,sizeof(DPL));
		if(ret < 0)	
		{
			perror("read");
			exit(-1);
		}
	memset(p,0,sizeof(DPL));
	row = mysql_fetch_row(res);
	}
	mysql_close(&mysql);
}

void mysql1(void *c)
{
	DPL *p=(DPL*)c;
	MYSQL mysql;
	mysql_init(&mysql);
	int ret = 0;
	char sql[500]={0};
	if((mysql_real_connect(&mysql,"localhost","root","123","student",0,NULL,0))==NULL)
	{
		printf("connect error\n");
		exit(-1);
	}
	sprintf(sql,"insert into stu values(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s','%s','%s','%s','%s')",p->tem,p->guangzhao,p->shidu,p->co2,p->N,p->s,p->a,p->b,p->c,p->d,p->wd,p->gz,p->sd,p->et,p->yf);
	ret = mysql_real_query(&mysql,sql,strlen(sql));
	if(ret != 0)
	{
		printf("query error\n");
		exit(-1);
	}
	mysql_close(&mysql);
	
}
int mysql3(char *p1,char *p2)
{
	DPL *p;
	p=(DPL*)malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init(&mysql);
	int ret = 0;
	char sql[500]={0};
	if((mysql_real_connect(&mysql,"localhost","root","123","student",0,NULL,0))==NULL)
	{
		printf("connect error\n");
		exit(-1);
	}
	sprintf(sql,"select * from stu1");
	ret = mysql_real_query(&mysql,sql,strlen(sql));
	if(ret < 0)
	{
		printf("query error:%s\n",mysql_error(&mysql));
	
		exit(-1);
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	int i;
	for(i = 0;row != NULL;i++)
	{
		if(strcmp(p1,row[0])==0&&strcmp(p2,row[1])==0)
		{
			return 0;
			break;
		}	
	
	memset(p,0,sizeof(DPL));
	row = mysql_fetch_row(res);
	}
	if(row == NULL)
	return 1;
	mysql_close(&mysql);
}


int mysql5(char *p,char *p1)
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init(&mysql);
	int ret = 0;
	char sql[500]={0};
	if((mysql_real_connect(&mysql,"localhost","root","123","student",0,NULL,0))==NULL)
	{
		printf("connect error\n");
		exit(-1);
	}
	sprintf(sql,"insert into stu1 values('%s','%s')",p,p1);
	ret=mysql_real_query(&mysql,sql,strlen(sql));
	if(ret < 0)
	{
		printf("query error:%s\n",mysql_error(&mysql));
	
		return 1;
	}
	else
	return 0;
	mysql_close(&mysql);
}

void mysql2(void *arg)
{
	int sock = *((int*)arg);
	DPL *p;
	int x = 0;
	p=(DPL*)malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init(&mysql);
	int ret = 0;
	char sql[500]={0};
	if((mysql_real_connect(&mysql,"localhost","root","123","student",0,NULL,0))==NULL)
	{
		printf("connect error\n");
		exit(-1);
	}
	sprintf(sql,"select * from stu");
	ret = mysql_real_query(&mysql,sql,strlen(sql));
	if(ret < 0)
	{
		printf("query error:%s\n",mysql_error(&mysql));
	
		exit(-1);
	}
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	int i;
	for(i = 0;row != NULL;i++)
	{
	p->tem=atoi(row[0]);
	p->guangzhao=atoi(row[1]);
	p->shidu=atoi(row[2]);
	p->co2=atoi(row[3]);
	p->N=atoi(row[4]);
	p->s=atoi(row[5]);
	p->a=atoi(row[6]);
	p->b=atoi(row[7]);
	p->c=atoi(row[8]);
	p->d=atoi(row[9]);
	strcpy(p->wd,row[10]);
	strcpy(p->gz,row[11]);
	strcpy(p->sd,row[12]);
	strcpy(p->et,row[13]);
	strcpy(p->yf,row[14]);
	ret = write(sock,p,sizeof(DPL));
		if(ret < 0)	
		{
			perror("read");
			exit(-1);
		}
	memset(p,0,sizeof(DPL));
	row = mysql_fetch_row(res);
	}
	memset(p,0,sizeof(DPL));
	ret = write(sock,p,sizeof(DPL));
		if(ret < 0)	
		{
			perror("read");
			exit(-1);
		}
	
	mysql_close(&mysql);
}
void *fun(void *arg)
{

	int sock=*((int*)arg);
	int ret = 0;
	while(1)
	{
		ret = read(sock,p4,sizeof(DPL));
		if(ret < 0)	
		{
			perror("read");
			exit(-1);
		}
		if(p4->tem == 0)break;
		mysql1(p4);
	}
	
}




void fun2()
{
	int ret = 0;
	
			printf("buf is %s\n",buf);
			ret = write(socke,buf,sizeof(buf));
			if(ret < 0)	
			{
				perror("write");
				exit(-1);
			}
			memset(buf,0,sizeof(buf));
	
		
	
}

void *fun1(void *arg)
{
	DPL *p;
	char sql[100]={0};
	char ch1[10]={0};
	char ch2[10]={0};
	int i = 0,j = 0;
	int x = 0;
	p=(DPL*)malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	int sock = *((int *)arg);
	int ret = 0;
	while(1)
	{
			memset(sql,0,sizeof(sql));
			ret = read(sock,sql,sizeof(sql));
			if(ret < 0)	
			{
				perror("read");
				exit(-1);
			}
		while(1)
		{
			j=0;
			memset(ch1,0,sizeof(ch1));
			memset(ch2,0,sizeof(ch2));
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='1')
			{	
				for(i=3;sql[i]!=',';i++)
				{
					ch1[j]=sql[i];
					j++;
				}
				printf("%s\n",ch1);
				j=0;
				for(i=i+1;sql[i]!='#';i++)
				{
					ch2[j]=sql[i];
					j++;
				}
				printf("%s\n",ch2);
				x=mysql3(ch1,ch2);
				if(x==0)
				{
					ret =write(sock,"密码正确",sizeof("密码正确"));
					if(ret < 0)	
					{
						perror("write");
						exit(-1);
					}
				break;
				}
				else
				{
				ret =write(sock,"密码或用户名错误",sizeof("密码或用户名错误"));
					if(ret < 0)	
					{
						perror("write");
						exit(-1);
					}
					memset(sql,0,sizeof(sql));
					ret = read(sock,sql,sizeof(sql));
					if(ret < 0)	
					{
						perror("read");
						exit(-1);
					}
				}
			}
			else 
			break;
		}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='2'&&sql[3]=='2')
			{
				mysql2(&sock);
			}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='3'&&sql[3]=='1')
			{
				memset(buf,0,sizeof(buf));	
				strcpy(buf,"11");
				fun2();
                            //    jieshou(p1);
				ret = write(sock,p4,sizeof(DPL));
				if(ret < 0)	
				{
					perror("write");
					exit(-1);
				}
           		memset(p4,0,sizeof(DPL));
				
			}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='3'&&sql[3]=='2')
			{
				
					
				strcpy(buf,"12");
				fun2();
				ret = write(sock,p4,sizeof(DPL));
				if(ret < 0)	
				{
					perror("write");
					exit(-1);
				}
                memset(p4,0,sizeof(DPL));
			}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='3'&&sql[3]=='3')
			{
				
					
				strcpy(buf,"13");
				fun2();
				ret = write(sock,p4,sizeof(DPL));
				if(ret < 0)	
				{
					perror("write");
					exit(-1);
				}
                memset(p4,0,sizeof(DPL));
			}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='3'&&sql[3]=='4')
			{
					
				strcpy(buf,"14");
				fun2();
				ret = write(sock,p4,sizeof(DPL));
				if(ret < 0)	
				{
					perror("write");
					exit(-1);
				}
                memset(p4,0,sizeof(DPL));
			}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='3'&&sql[3]=='5')
			{
				
					
				strcpy(buf,"15");
				fun2();
				ret = write(sock,p4,sizeof(DPL));
				if(ret < 0)	
				{
					perror("write");
					exit(-1);
				}
                memset(p4,0,sizeof(DPL));
			}
		while(1)
		{
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='2'&&sql[3]=='1')
			{
				j=0;
			
				for(i=4;sql[i]!=',';i++)
				{
					ch1[j]=sql[i];
					j++;
				}
				printf("%s\n",ch1);
				j=0;
				for(i=i+1;sql[i]!='#';i++)
				{
					ch2[j]=sql[i];
					j++;
				}
				x=mysql5(ch1,ch2);
				if(x==0)
				{
					ret = write(sock,"设置成功",sizeof("设置成功"));
					if(ret < 0)	
					{
						perror("write");
						exit(-1);
					}
				break;
				}
				else
				{
					ret =write(sock,"设置失败",sizeof("设置失败"));
					if(ret < 0)	
					{
		 				perror("write");
						exit(-1);
					}
				}
				memset(sql,0,sizeof(sql));
				ret = read(sock,sql,sizeof(sql));
				if(ret < 0)	
				{
					perror("read");
					exit(-1);
				}
			}
			else
			break;	
		}
			if(sql[0]=='$'&&sql[1]=='$'&&sql[2]=='2'&&sql[3]=='3')
			{
				mysql2(&sock);
			}
	
	}	
}

int main()
{
	sem_init(&sem,0,1);
	char buf[10]={0};
	struct sockaddr_in myaddr;
	struct sockaddr_in headdr;
	memset(&myaddr,0,sizeof(myaddr));
	memset(&headdr,0,sizeof(headdr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PART);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	p4=(DPL*)malloc(sizeof(DPL));
	int sock;
	pthread_t th,th1,th2;
	int socke1;
	int size = sizeof(headdr);
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("sock");
		exit(-1);
	}
	int ret = 0;
	ret = bind(sock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(ret < 0)
	{
		perror("bind");
		exit(-1);
	}
	ret = listen(sock,5);
	if(ret < 0)
	{
		perror("listen");
		exit(-1);
	}
	int x = 0;
	while(1)
	{
		socke=accept(sock,(struct sockaddr*)&headdr,&size);
		if(socke< 0)
		{
			perror("accept");
			exit(-1);
		}
		ret = read(socke,buf,sizeof(buf));
		if(ret < 0)
		{
			perror("read");
			exit(-1);
		}
		if(buf[0]=='$'&&buf[1]=='$'&&buf[2]=='1'&&buf[3]=='2'&&x==0)
		{
			printf("nihao\n");
			pthread_create(&th,NULL,fun,&socke);
			x=1;
		}	
		else
		{
			pthread_create(&th1,NULL,fun1,&socke);
			
		}
		memset(buf,0,sizeof(buf));
	}
	pthread_join(th,NULL);
	pthread_join(th1,NULL);
	
	
	
}
