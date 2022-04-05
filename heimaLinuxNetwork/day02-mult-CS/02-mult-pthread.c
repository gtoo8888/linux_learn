#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
// #include <pthread.h>
#include "warp.h"


// 子线程回调函数:
void *thread_work(void *arg) {
    // sleep(10); //这边加上sleep就可以看到cfd的值会随着又一个客户端信号的发过来而改变了
    //获得参数:通信文件描述符
    int cfd = *(int *)arg;
    // 但是sleep如果加在这个后面，就没有用了，因为cfd已经被改变了

    int n = 0,i = 0;
    char buf[128];
    while(1){
        memset(buf,0x00,sizeof(buf));
        n = Read(cfd,buf,sizeof(buf));//读数据
        if(n <= 0) {
            printf("read error or client close,n==[%d]\n",n);
            //perror最好不要在子线程中用
            break;
        }
        printf("n==[%d],buf==[%s]\n",n,buf);
        for(i = 0;i < n;i++) {
            buf[i] = toupper(buf[i]);//转换成大写
        }
        Write(cfd,buf,n);//发数据
    }
    close(cfd);
    pthread_exit(NULL);
}


int main(){
    // 创建socket
    int lfd = Socket(AF_INET,SOCK_STREAM,0);

    // 绑定
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = Bind(lfd,(struct sockaddr*)&serv,sizeof(serv));

    //监听
    Listen(lfd,128);

    int cfd;
    pthread_t threadID;
    struct sockaddr_in client;
    while(1) {
        //接受新的客户端连接请求
        cfd = Accept(lfd,NULL,NULL);

        //创建一个子线程
        pthread_create(&threadID,NULL,thread_work,&cfd);
        //thread_work线程回调函数

        //设置线程为分离属性
        pthread_detach(threadID);
    }
    //关闭监听文件描述符
    Close(lfd);
    return 0;
}





// 问题：
// 1.lfd能不能在子线程执行函数中关闭
// 2.有两个及以上客户端同时到来，cfd有什么情况发生
// 主线程定义的cfd,可以被所有子线程共享，那么cf保存的值，是谁的值，最后一个的值


// 1子线程能否关闭lfd
// 2主线程能否关闭cfd
// 3多个子线程共享cfd，会有什么问题发生?l


// gcc XXX -lpthread

































