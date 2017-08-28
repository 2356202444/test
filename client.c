#include"1.h"

/**********************************************************
智能农场大棚系统（客户端）
功能：
super：超级用户实现对数据的查询、以及对管理员的任命、密码的修改
普通用户：对数据的查询，并无对大棚内部器械的操作功能。



********************************************************/

DPL *p1;
#define  PART 12345

void jieshou(DPL *p)
{
			
					
					
	printf("温度    ：%d\t  温度反馈    ：%d\t  温度描述    ：%s\n",p->tem,p->s,p->wd);
	printf("光照    ：%d\t  光照反馈    ：%d\t  光照描述    ：%s\n",p->guangzhao,p->a,p->gz);
	printf("湿度    ：%d\t  湿度反馈    ：%d\t  湿度描述    ：%s\n",p->shidu,p->b,p->sd);
	printf("co2含量 ：%d\t  CO2含量反馈 ：%d\t  CO2描述     ：%s\n",p->co2,p->c,p->et);
	printf("土壤肥力：%d\t  土壤肥力反馈：%d\t  土壤肥力描述 ：%s\n",p->N,p->d,p->yf);
					
}
void zhengque(void *arg)
{
		int sock=*((int*)arg);
		int x = 0,c =0;
		char m[10]={0};	
		char n[10]={0};
		int ret = 0;
		char sql[100]={0};	
		DPL *p;
		p=(DPL*)malloc(sizeof(DPL));
		memset(p,0,sizeof(DPL));
		while(1)
		{
			printf("\n\n");
    		printf("     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	     	printf("     ┃ ******************************************* ┃\n");
		    printf("     ┃ * ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ * ┃\n");
		    printf("     ┃ * ┃*************************************┃ * ┃\n");
		    printf("     ┃ * ┃**                                 **┃ * ┃\n");
		    printf("     ┃ * ┃**       欢迎使用智能大棚系统      **┃ * ┃\n");
  			printf("     ┃ * ┃****                             ****┃ * ┃\n");
  			printf("     ┃ * ┃****   1 注册（指定其他超级用户）****┃ * ┃\n");
   		 	printf("     ┃ * ┃****                             ****┃ * ┃\n");
   		 	printf("     ┃ * ┃****   2 查询                    ****┃ * ┃\n");
  		  	printf("     ┃ * ┃****                             ****┃ * ┃\n");
   		 	printf("     ┃ * ┃****   3 给定命令                ****┃ * ┃\n");
   		 	printf("     ┃ * ┃****         ver 1.1.1           ****┃ * ┃\n");
   		 	printf("     ┃ * ┃*************************************┃ * ┃\n");
    		printf("     ┃ * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ * ┃\n");
    		printf("     ┃ ******************************************* ┃\n");
    		printf("     ┗━━━━━━━━━━━━━━━━━━按其他键退出━━━━━━━━━━━━━━━┛\n");
			printf("请选择\n");
			scanf("%d",&x);
				if(x == 1)
				{
					printf("请输入用户名\n");
						if(ret < 0)
						{
							perror("read");
							exit(-1);
						}
					scanf("%s",m);	
					printf("请输入密码\n");
					scanf("%s",n);
					sprintf(sql,"$$21%s,%s##",m,n);
					ret = write(sock,sql,sizeof(sql));	
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
					printf("%s\n",sql);
					
				}
				else if(x == 2)
				{
					sprintf(sql,"$$22");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("write");
						exit(-1);
					}
					while(1)
					{
						ret = read(sock,p,sizeof(DPL));
						if(ret < 0)
						{
							perror("read");
							exit(-1);
						}
						if(p->tem == 0)
						break;
						printf("\n\n");
						jieshou(p);
						memset(p,0,sizeof(DPL));
						sleep(1);
					}
				}
				else if(x==3)
				{
					while(1)
					{
					printf("\n\n");
 		   		printf("     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	   		 	printf("     ┃ ******************************************* ┃\n");
			    printf("     ┃ * ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ * ┃\n");
			    printf("     ┃ * ┃*************************************┃ * ┃\n");
			    printf("     ┃ * ┃**                                 **┃ * ┃\n");
			    printf("     ┃ * ┃**       欢迎使用智能大棚系统      **┃ * ┃\n");
  				printf("     ┃ * ┃****                             ****┃ * ┃\n");
  				printf("     ┃ * ┃****   1 对温度调控              ****┃ * ┃\n");
   			 	printf("     ┃ * ┃****   2 对光照调控              ****┃ * ┃\n");
   			 	printf("     ┃ * ┃****   3 对湿度调控              ****┃ * ┃\n");
  			  	printf("     ┃ * ┃****   4 对co2调控               ****┃ * ┃\n");
   			 	printf("     ┃ * ┃****   5 对土壤养分调控          ****┃ * ┃\n");
   			 	printf("     ┃ * ┃****         ver 1.1.1           ****┃ * ┃\n");
   			 	printf("     ┃ * ┃*************************************┃ * ┃\n");
    			printf("     ┃ * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ * ┃\n");
    			printf("     ┃ ******************************************* ┃\n");
    			printf("     ┗━━━━━━━━━━━━━━━━━━按其他键退出━━━━━━━━━━━━━━━┛\n");
				printf("请选择\n\n");
				scanf("%d",&c);
				if(c==1)
					{
					memset(sql,0,sizeof(sql));
					sprintf(sql,"$$31");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("rwrite");
						exit(-1);
					}
					}
				else if(c==2)
					{
					memset(sql,0,sizeof(sql));
					sprintf(sql,"$$32");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("rwrite");
						exit(-1);
					}
					}
				else if(c==3)
					{
					memset(sql,0,sizeof(sql));
					sprintf(sql,"$$33");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("rwrite");
						exit(-1);
					}
					}
				else if(c==4)
					{
					memset(sql,0,sizeof(sql));
					sprintf(sql,"$$34");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("rwrite");
						exit(-1);
					}
					}
				else if(c==5)
					{
					memset(sql,0,sizeof(sql));
					sprintf(sql,"$$35");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("rwrite");
						exit(-1);
					}
					}
					else
					break;
					memset(sql,0,sizeof(sql));
					ret = read(sock,p1,sizeof(DPL));
					if(ret < 0)
	 				{
						perror("read");
						exit(-1);
					}
                   			 jieshou(p1);
					  
                   			 memset(p1,0,sizeof(DPL));
					}
				
				}
				else 
				break;
		}
}
void *fun(void *arg)
{
	DPL *p;
	p=(DPL*)malloc(sizeof(DPL));
	memset(p,0,sizeof(DPL));
	int  a = 0;
	int  x = 0; 
	char m[10] = {0};
	char n[10] = {0};
	char sql[100] = {0};
	int ret = 0;
	int sock = *((int*)arg);  
	printf("\n\n");
    printf("     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("     ┃ ******************************************* ┃\n");
    printf("     ┃ * ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ * ┃\n");
    printf("     ┃ * ┃*************************************┃ * ┃\n");
    printf("     ┃ * ┃**                                 **┃ * ┃\n");
    printf("     ┃ * ┃**       欢迎使用智能大棚系统      **┃ * ┃\n");
    printf("     ┃ * ┃****                             ****┃ * ┃\n");
    printf("     ┃ * ┃****                             ****┃ * ┃\n");
    printf("     ┃ * ┃****                             ****┃ * ┃\n");
    printf("     ┃ * ┃****                             ****┃ * ┃\n");
    printf("     ┃ * ┃****                             ****┃ * ┃\n");
    printf("     ┃ * ┃****         ver 1.1.1           ****┃ * ┃\n");
    printf("     ┃ * ┃*************************************┃ * ┃\n");
    printf("     ┃ * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ * ┃\n");
    printf("     ┃ ******************************************* ┃\n");
    printf("     ┗━━━━━━━━━━━━━━━━━━按任意键继续━━━━━━━━━━━━━━━┛\n");
	char c=getchar();
	printf("\n\n");
	while(1)
	{	printf("\n\n");
    	printf("     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    	printf("     ┃ ******************************************* ┃\n");
    	printf("     ┃ * ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ * ┃\n");
    	printf("     ┃ * ┃*************************************┃ * ┃\n");
    	printf("     ┃ * ┃**                                 **┃ * ┃\n");
    	printf("     ┃ * ┃**       欢迎使用智能大棚系统      **┃ * ┃\n");
    	printf("     ┃ * ┃****                             ****┃ * ┃\n");
    	printf("     ┃ * ┃****       1  超级用户登录       ****┃ * ┃\n");
    	printf("     ┃ * ┃****                             ****┃ * ┃\n");
    	printf("     ┃ * ┃****       2  游客登录           ****┃ * ┃\n");
    	printf("     ┃ * ┃****                             ****┃ * ┃\n");
    	printf("     ┃ * ┃****         ver 1.1.1           ****┃ * ┃\n");
    	printf("     ┃ * ┃*************************************┃ * ┃\n");
    	printf("     ┃ * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ * ┃\n");
    	printf("     ┃ ******************************************* ┃\n");
    	printf("     ┗━━━━━━━━━━━━━━━━━━按其他键继续━━━━━━━━━━━━━━━┛\n");
		printf("\n");
		printf("请选择进程\n");
		scanf("%d",&a);
			if(a == 1)
			{
					printf("请输入用户名\n");
					scanf("%s",m);	
					printf("请输入密码\n");
					scanf("%s",n);
					sprintf(sql,"$$1%s,%s##",m,n);
					ret = write(sock,sql,sizeof(sql));	
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
					if(strcmp(sql,"密码正确")==0)
					{
						printf("密码正确\n");
						zhengque(&sock);
					}
					else
					{
						printf("密码错误，请重新输入用户名和密码\n");
						memset(m,0,sizeof(m));
						memset(n,0,sizeof(n));
					}
			}
	
		else if(a == 2)
			{
					sprintf(sql,"$$23");
					ret = write(sock,sql,sizeof(sql));
					if(ret < 0)
					{
						perror("write");
						exit(-1);
					}
					while(1)
					{
						memset(sql,0,sizeof(0));
						ret = read(sock,p,sizeof(DPL));
						if(ret < 0)
						{
							perror("read");
							exit(-1);
						}
						if(p->tem==0)
						break;
						jieshou(p);
						memset(p,0,sizeof(DPL));
						sleep(1);
					}
			}
			else 
			break;
	}
}

int main()
{
	pthread_t thread;
	p1=(DPL*)malloc(sizeof(DPL));
	memset(p1,0,sizeof(DPL));
	struct sockaddr_in headdr;
	memset(&headdr,0,sizeof(headdr));
	headdr.sin_family = AF_INET;
	headdr.sin_port = htons(PART);
	headdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int sock ;
	sock = socket(AF_INET,SOCK_STREAM,0);
	if( sock < 0)
	{
		perror("sock");
		exit(-1);
	}
	int ret = 0;
	ret = connect(sock,(struct sockaddr*)&headdr,sizeof(headdr));
	if(ret < 0)
	{
		perror("connect");
		exit(-1);
	}
	ret = write(sock,"$$11",sizeof("$$11"));
	if(ret < 0)
	{
	 	perror("write");
		exit(-1);
	}
	pthread_create(&thread,NULL,fun,&sock);

	pthread_join(thread,NULL);
	return 0;
}
