#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	pid_t pid;
	pid = fork();
	if(-1 == pid) {
		printf("ERROR!\n");
		return -1;
	}else if(pid == 0){
		printf("子进程,fork,ID:%d,父进程%d,ID:%d\n",pid,getpid(),getppid());
	}else{
		printf("父进程,fork,ID:%d,父进程%d,ID:%d\n",pid,getpid(),getppid());
	}
	return 0;
}
