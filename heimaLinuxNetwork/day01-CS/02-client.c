#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(){
    // 创建socket，客户端的文件描述符用于和服务端通讯的
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd < 0) {
        perror("socket error!");
        return -1;
    }

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    // serv.sin_addr.s_addr = htonl(INADDR_ANY);//这么写可以的
    // int inet_pton(int af, const char *src, void *dst);//将一个点分十进制字符串转换成网络地址
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
    printf("[%x]\n",serv.sin_addr.s_addr);
    // int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);  
    // 连接服务器
    int ret = connect(cfd,(struct sockaddr*)&serv,sizeof(serv));
    if(ret < 0) {
        perror("connect error!");
        return -1;
    }

    int i = 0;
    int n = 0;
    char buf[1024];
    while(1) {
        //读标准输入数据
        memset(buf,0x00,sizeof(buf));
        n = read(STDIN_FILENO,buf,sizeof(buf));//从终端读取数据
        // printf("n==[%d],buf==[%s]\n",n,buf);

        //发送数据
        write(cfd,buf,n);//往发送缓冲区中写，谁真正发送了数据？一定是网卡，内核帮我们做了很多事情

        //读服务器发来的数据
        memset(buf,0x00,sizeof(buf));
        n = read(cfd,buf,sizeof(buf));
        if(n <= 0) {
            printf("read error or server close,n==[%d]\n",n);
            break;
        }
        printf("n==[%d],buf==[%s]\n",n,buf);
    }
    //关闭通讯套接字
    close(cfd);
    return 0;
}


// netstat -anp
// 测试过程中可以使用netstat命令查看监听状态和连接状态
// netstat命令:
// a表示显示所有
// n表示显示的时候以数字的方式来显示
// p表示显示进程信息(进程名和进程PID)

// name@name-hcp:~$ netstat -anp | grep 8888
//                 自己的一侧                  对方的一侧
// tcp        0      0 0.0.0.0:8888            0.0.0.0:*               LISTEN      10644/./server  //listen一定出现在服务端，说明这个进程已经处于listen状态了
// tcp        0      0 127.0.0.1:34568         127.0.0.1:8888          ESTABLISHED 10646/./client
// tcp        0      0 127.0.0.1:8888          127.0.0.1:34568         ESTABLISHED 10644/./server  //服务器的端口是绑定的

// ESTABLISHED,链接建立了
// 处于listen状态的进程，可以被客户端连接

// 先关闭服务端，没有马上结束，由于程序阻塞在读取标准输入了