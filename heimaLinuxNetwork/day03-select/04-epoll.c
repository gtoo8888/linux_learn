#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>     //FD_SET(),FD_LISTEN(),FD_ZERO(),FD_CLR()
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/epoll.h>

int main(){

    int lfd = socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
    bind(lfd,(struct sockaddr*)&serv,sizeof(serv));

    listen(lfd,128);

    // 创建一棵epoll树
    //返回个文件描述符,这个文件描述符就表示epoll树的树根节点
    int epfd = epoll_create(1024);
    if(epfd < 0){
        perror("create epoll error");
        return -1;
    }

    //将监听文件描述符上树
    struct epoll_event ev;
    ev.events = EPOLLIN;    //可读事件
    ev.data.fd = lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);  //让内核监听lfd


    char buf[1024];
    int nready;
    struct epoll_event events[1024];
    while(1){//进入while循环，等待事件发生
        nready = epoll_wait(epfd, events,1024,-1);//一直阻塞
        //只要epoll_wait返回了，就一定有事件发生了
        //events上树的时候是什么，下树的时候就是什么
        //写起来看起来比select简单，因为epoll只将发生变化的事件通过events告诉我们，没有变化的没有说

        if(nready < 0) {    
            perror("epoll_wait error");
            if(errno == EINTR)  //如果是被信号中断
                continue;
            break;
        }

        for(int i = 0;i < nready;i++){
            int sockfd = events[i].data.fd;
            //有客户端连接请求到来
            if(sockfd == lfd) {
                int cfd = accept(lfd,NULL,NULL);

                //将cfd对应的读事件上epoll树
                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
                continue;

            }

            //有客户端发送数据过来
            memset(buf,0x00,sizeof(buf));
            int n = read(sockfd,buf,sizeof(buf));//read数据
            if(n <= 0){
                close(sockfd);
                //将sockfd对应的事件节点从epoll树上删除
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                perror( "read error or client closed");
                continue;
            }else{
                printf("n==[%d],buf==[%s]\n",n,buf);
                for(int k = 0;k < n;k++) 
                    buf[k] = toupper(buf[k]);//转换成大写
                write(sockfd,buf,n);//write应答数据给客户端
            }
        }
    }
    close(epfd);
    close(lfd);

    return 0;
}










































