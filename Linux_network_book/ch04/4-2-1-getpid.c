#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	pid_t pid,ppid;
	pid = getpid();
	ppid = getppid();

	printf("%d\n",pid);
	printf("%d\n",ppid);

	return 0;
}
