#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    int result = -1;
    int fd[2];
    int nbytes;
    pid_t pid;

    char string[] = "hello pipe";
    char readbuffer[80];
    int *write_fd = &fd[1];
    int *read_fd = &fd[0];

    result = pipe(fd);
    if(-1 == result) {
        printf("pipe error!\n");
        return -1;
    }
    pid = fork();
    if(-1 == pid) {
        printf("fork error!\n");
        return -1;   
    }
    if(0 == pid) {
        close(*read_fd);
        result = write(*write_fd,string,strlen(string));
    }else{
        close(*write_fd);
        nbytes = read(*read_fd,readbuffer,sizeof(readbuffer));
        printf("get number:%d,%s\n",nbytes,readbuffer);
    }
    return 0;
}