#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define K 1024
#define WRITELEN (128*K)

int main(void) {
    int result = -1;
    int fd[2];
    int nbytes;
    pid_t pid;

    char string[WRITELEN] = "hello pipe";
    char readbuffer[10*K];
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
        int write_size = WRITELEN;
        result = 0;
        close(*read_fd);
        while(write_size >= 0){
            result = write(*write_fd,string,strlen(string));
            if(result > 0){
                write_size -= result;
                printf("write date:%d,remain date:%d\n",result,write_size);
            }
            else{
                sleep(10);
            }
        }
        return 0;        
    }else{
        close(*write_fd);
        while(1) {
            nbytes = read(*read_fd,readbuffer,sizeof(readbuffer));
            if(nbytes <= 0) {
                printf("no date input\n");
                break;
            }
            printf("read date:%d,Content is :" "\n",nbytes);
        }
    }
    return 0;
}