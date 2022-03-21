#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <cstring>
#include <sys/types.h>
#include <sys/un.h>

#define MY_SOCK_PATH "/somepath"

int main(int argc,char * argv[]){
	int sfd;
	struct sockaddr_un addr;
	sfd = socket(AF_UNIX,SOCK_STREAM,0);

	if(sfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&addr,0,sizeof(struct sockaddr_un));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,MY_SOCK_PATH,sizeof(addr.sun_path) - 1);

	if(bind(sfd, (struct sockaddr *)&addr,sizeof(struct sockaddr_un) == -1)) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	close(sfd);
	return 0;
}
