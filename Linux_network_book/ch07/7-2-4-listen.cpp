#include <stdio.h>	//perror()输出错误信息
#include <stdlib.h>	//exit()
#include <sys/types.h>
#include <unistd.h>	//close()
#include <cstring>	//bzero()
#include <sys/socket.h>
#include <arpa/inet.h> 	//htons()


#define MYPORT 3490
int main(int argc,char *argv[]) {
	int sockfd;
	struct sockaddr_in my_addr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = inet_addr("192.168.1.15");
	bzero(&(my_addr.sin_zero),8);

	if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}	
	if(listen(sockfd,5) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	close(sockfd);

	return 0;
}
