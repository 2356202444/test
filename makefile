all:cli ser dap
ser:sever.o 
	gcc -pthread -o ser sever.o -lmysqlclient 
cli:client.o 
	gcc -pthread -o cli client.o  
dap:dapeng.o 
	gcc -pthread -o dap dapeng.o  
sever.o:sever.c 1.h
	gcc -c sever.c
client.o:client.c 1.h
	gcc -c client.c
dapeng.o:dapeng.c 1.h
	gcc -c dapeng.c
	

