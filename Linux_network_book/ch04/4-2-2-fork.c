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
	}else if(pid == 0){	//子进程中执行的代码
		printf("子进程,fork,返回值:%d,ID:%d,父进程:%d\n",pid,getpid(),getppid());
	}else{	//父进程中执行的代码
		printf("父进程,fork,返回值:%d,ID:%d,父进程:%d\n",pid,getpid(),getppid());
	}
	return 0;
}
