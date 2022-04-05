#include <stdio.h>  //perror()输出错误信息
#include <stdlib.h> //exit()
#include <sys/types.h>
#include <sys/socket.h>     //socket(),bind(),listen()
#include <string.h> //bzero()
#include <arpa/inet.h> //htons(),inet_pton()
#include <unistd.h> //read(),write(),close()
#include <ctype.h> //toupper()


// man 7 ip 查看地址
int main(){
    // 创建socket，服务端的文件描述符用于和监听
    // int socket(int domain, int type, int protocol);
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd < 0){
		perror("socket error!");
        return -1;
    }

    // struct sockaddr_in {
    //            sa_family_t    sin_family; /* address family: AF_INET */
    //            in_port_t      sin_port;   /* port in network byte order */
    //            struct in_addr sin_addr;   /* internet address */
    //        };
    //  /* Internet address. */
    //        struct in_addr {
    //            uint32_t       s_addr;     /* address in network byte order */
    //        };
    struct sockaddr_in serv;
    // void bzero(void *s, size_t n);   //将内存块的前n个字节清零
    bzero(&serv,sizeof(serv));
    //结构体使用之前需要初始化
    //确保你使用的这块内存已经初始化了，否则结构体这块内存里面是随机值，容易误用导致不可预知的后果，严重的可能导致程序崩溃。
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY); //表示使用本机任意可用IP
    // 绑定，绑定之前需要先定义结构体
    // int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    //既有传入又有传出的时候要用地址
    int ret = bind(lfd,(struct sockaddr *)&serv,sizeof(serv));
    if(ret < 0) {
        perror("bind error!");
        return -1;
    }

    // int listen(int sockfd, int backlog);
    // 监听，不管返回值
    listen(lfd,128);

    // sleep(30);//观察listen以后，这个链接是不是已经有了
    //链接是在accept之前已经建立了
    // 调用accept函数不是说新建一个连接，而是从已连接队列中取出一个可用连接


    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    // 第二个是客户端IP的端口，不关心就不写了
    // 接收一个网络请求，返回值是一个文件描述符，用来通讯
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    // int cfd = accept(lfd,NULL,NULL); 
    int cfd = accept(lfd,(struct sockaddr*)&client,&len); //len是一个输入输出参数
    //获取客户端的IP,作用：设置黑名单，可以知道谁来连我了
    //  const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
    //获取client端的IP和端口
    char sIP[16];
    memset(sIP,0x00,sizeof(sIP));
    printf("client-->IP:[%s],PORT:[%d]\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,sIP,sizeof(sIP)),ntohs(client.sin_port));
    printf("lfd==[%d],cfd==[%d]\n",lfd,cfd);

    int i = 0;
    int n = 0;
    char buf[1024];
    while(1) {
        // void *memset(void *s,int ch,size_t n);  //清零也可以使用这个
        // memset(&my_addr, 0, sizeof(struct sockaddr_un));
        // 读数据
        memset(buf,0x00,sizeof(buf));
        //  ssize_t read(int fd, void *buf, size_t count); 
        n = read(cfd,buf,sizeof(buf));
        if(n <= 0) {
            //0是对方关闭链接
            //-1为读取失败
            printf("read error or client close,n==[%d]\n",n);
            break;
        }
        printf("n==[%d],buf==[%s]",n,buf);

        for(i = 0;i < n;i++) {
            // int toupper(int c);
            buf[i] = toupper(buf[i]);//转换成大写
        }
        //  发数据
        //  ssize_t write(int fd, const void *buf, size_t count);
        write(cfd,buf,n);//接收到几位，转换成大写发送几位
    }
    // int close(int fd);
    // 关闭监听文件描述符、通信文件描述符
    close(lfd);
    close(cfd);

    return 0;
}


// 使用nc测试工具进行测试
// nc 127.0.0.1 8888
// nc 127.1 8888
// 直接发送比如，nihao,hello,会转换成大写
// 最开始程序在关闭nc以后，服务器会一直接收数据，大量重复显示