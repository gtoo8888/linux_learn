#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

// #include "warp.h"

int main(){
    // 创建socket
    int lfd = socket(AF_INET,SOCK_STREAM,0);

    // 绑定
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(lfd,(struct sockaddr*)&serv,sizeof(serv));

    //监听
    listen(lfd,128);

    pid_t pid;
    int cfd;
    char sIP[16];
    socklen_t len;
    struct sockaddr_in client;
    while(1){
        len = sizeof(client);
        cfd = accept(lfd,(struct sockaddr *)&client,&len);
        
        memset(sIP,0x00,sizeof(sIP));
        // printf("client,IP:[%s],PORT:[%d]\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,sIP,sizeof(sIP)),noths(client.sin_port));

        //接受一个新的连接，创建一个子进程,让子进程完成数据的收发操作
        pid = fork();
        if(pid < 0) {
            perror("fork error!");
            return -1;
        }
        else if(pid > 0) {
            //关闭通信文件描述符cfd
            close(cfd);
        }else if(pid == 0){
            close(lfd);//关闭监听文件描述符lfd
            int n = 0,i = 0;
            char buf[128];
            while(1){
                n = read(cfd,buf,sizeof(buf));//读数据
                if(n <= 0) {
                    printf("read error or client close,n==[%d]\n",n);
                    break;
                }
                printf("client,IP:[%s],PORT:[%d]\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,sIP,sizeof(sIP)),ntohs(client.sin_port));
                printf("[%d]-->:n==[%d],buf==[%s]\n",ntohs(client.sin_port),n,buf);
                for(i = 0;i < n;i++) {
                    buf[i] = toupper(buf[i]);//转换成大写
                }
                write(cfd,buf,n);//发数据
            }
            close(cfd);
            exit(0);
        }
    }
    // close(lfd);
    // close(cfd); 

    return 0;
}
