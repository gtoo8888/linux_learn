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

    int cfd;
    //定义fd_set类型的变量
    fd_set readfds;         //定义文件描述符集变量
    fd_set tmpfds;          //为了防止readfds被改变，所以用这个临时变量来保存一下

    //清空readfds和tmpfds集合
    FD_ZERO(&readfds);      //清空文件描述符集变量
    FD_ZERO(&tmpfds);

    //将lfd加入到readfds中,委托内核监控
    FD_SET(lfd,&readfds);   
    int maxfd = lfd;
    int i,n;
    int nready;
    char buf[1024];
    while(1) {
        // int select(int nfds, fd_set *readfds, fd_set *writefds,
        //           fd_set *exceptfds, struct timeval *timeout); 
        //委托内核监控可读,可写,异常事件   
        tmpfds = readfds;   //防止readfds，变了以后，前面就不能用了
        //tmpfds是输入输出参数:
        //输入:告诉内核要监测哪些文件描述符
        //输出:内核告诉应用程序有哪些文件描述符发生了变化
        nready = select(maxfd+1,&tmpfds,NULL,NULL,NULL);
        //现在就监控可读的文件描述符
        //对可写，异常事件，不关心，超时事件NULL，表示永久阻塞
        if(nready < 0) {    //发生了错误
            if(errno == EINTR)  //如果是被信号中断的，那就可以继续
                continue;
            break;
        }

        //如果有客户端连接请求到来
        if(FD_ISSET(lfd,&tmpfds)){
            cfd = accept(lfd,NULL,NULL);//那么就接受新的客户端连接请求
            FD_SET(cfd,&readfds);//将cfd加入到readfds集合中

            if(maxfd < cfd)//修改内核监控的文件描述符的范围
                maxfd = cfd;
            
            if(--nready == 0)//如果现在只有一个客户端的链接发过来了，就不用继续往下走了
                continue;
        }

        //有客户端数据发来
        for(i = lfd+1;i <= maxfd;i++){//把没一个链接都处理一下
            int sockfd = i;
            //判断sockfd文件描述符是否有变化
            if(FD_ISSET(sockfd,&tmpfds)){
                n = read(sockfd,buf,sizeof(buf));//read数据
                if(n <= 0){
                    close(i);
                    FD_CLR(sockfd,&readfds);//将文件描述符sockfd从内核中去除

                }else{
                    printf("n==[%d],buf==[%s]\n",n,buf);
                    for(int k = 0;k < n;k++) 
                        buf[k] = toupper(buf[k]);//转换成大写
                    write(sockfd,buf,n);//write应答数据给客户端
                }


                if(--nready == 0)
                    break;
                
            }
        }

    }

    close(lfd);

    return 0;
}










































