/*********************************
    > File Name: echo_client2.c
    > Author: Zeno
    > Mail:340562424@qq.com 
    > Created Time: 2015年09月19日 星期六 10时00分59秒
 ********************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_adr;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;

	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\n ", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);//转换ｉｐ
	serv_adr.sin_port = htons(atoi(argv[2]));//转换端口号

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");	
	else
		puts("Connected .....");
	while(1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		str_len = write(sock, message, strlen(message));

		recv_len = 0;
		while(recv_len < str_len)
		{
			recv_len = read(sock,&message[recv_len], BUF_SIZE - 1);
			if(recv_cnt == -1)
				error_handling("read() error");
			recv_len += recv_cnt;
		}
		message[str_len] = 0;
		printf("Mesage from server : %s \n", message);
	}
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}