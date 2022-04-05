#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <errno.h>



void perr_exit(const char *s) {
    perror(s);
    exit(-1);
}

int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr) {
    int n;
again:
    if((n = accept(fd,sa,salenptr) < 0)){
        if((errno == ECONNABORTED) || (errno == EINTR)) // 被信号打断
            goto again;//有的错误是可以容忍的
        else
            perr_exit("accept error");
    }
    return n;
}

int Bind(int fd,const struct sockaddr * sa,socklen_t salen){
    int n;

    if((n = bind(fd,sa,salen)) < 0)
        perr_exit("bind error");

    return n;
}

int Connect(int fd,const struct sockaddr *sa,socklen_t salen) {
    int n;
    n = connect(fd,sa,salen);
    if(n < 0)
        perr_exit("connect error");

    return n;
}

int Listen(int fd,int backlong) {
    int n;

    if((n = listen(fd,backlong)) < 0)
        perr_exit("listen error");

    return n;
}

int Socket(int family,int type,int protocol){
    int n;

    if((n = socket(family,type,protocol)) < 0 )
        perr_exit("socket error");

    return n;
}

ssize_t Read(int fd,void *ptr,size_t nbytes){
    ssize_t n;

again:
    if( (n = read(fd,ptr,nbytes)) == -1 ){
        if(errno == EINTR)// 被信号打断
        //读数据的时候，可能信号量比较大，读取的时候被打断了
        // 阻塞函数，被阻塞期间，被信号打断了，不应该算是一个错误
            goto again;
        else
            return -1;
    }

    return n;
}

ssize_t Write(int fd,const void *ptr,size_t nbytes){
    ssize_t n;

again:
if( (n = write(fd,ptr,nbytes)) == -1 ){
        if(errno == EINTR)  //缓存区不可用，缓存区写满了
            goto again;
        else
            return -1;
    }

    return n;
}

int Close(int fd){
    int n;
    if((n = close(fd) == -1))
        perr_exit("close error");

    return n;
}

/*参三: 应该读取的字节数*/    
//socket 4096  readn(cfd, buf, 4096)   nleft = 4096-1500
// 读n个数据，比如缓冲区有10K数据，每次智能读500个，得循环读
ssize_t Readn(int fd,void *vptr,size_t n){
    //vptr缓冲区
    size_t nleft;//usigned int 剩余未读取的字节数
    ssize_t nread;//int 实际读到的字节数
    char *ptr;

    ptr = vptr;
    nleft = n;//n 未读取字节数
    while(nleft > 0) {
        if((nread = read(fd,ptr,nleft)) < 0) {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return n - nleft;
}

// 写n个数据
// 往一个大的缓冲区中写
ssize_t Writen(int fd,void *vptr,size_t n) {
    size_t nleft;
    ssize_t nwritten;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0) {
        if(( nwritten = write(fd,ptr,nleft)) <= 0) {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;    //nleft = nleft - nread 
        ptr += nwritten;
    }
    return n;
}

// 读的量小一点
static ssize_t my_read(int fd,char *ptr) {
    static int read_cnt;
    static char *read_ptr;
    static char read_buf[100];

    if(read_cnt <= 0){
again:
        if( (read_cnt = read(fd,read_buf,sizeof(read_buf))) < 0) {
            if(errno == EINTR)
                goto again;
            return -1;
        }else if(read_cnt == 0)
            return 0;
        
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;

    return 1;
}

/*readline --- fgets*/    
//传出参数 vptr
ssize_t Readline(int fd,void *vptr,size_t maxlen) {
    ssize_t n,rc;
    char c,*ptr;
    ptr = vptr;

    for(n = 1;n < maxlen;n++){
        if((rc = my_read(fd,&c)) == 1) {
            *ptr++ = c;
            if(c == '\n')   //读一行，用\n结尾，一个个读取的，读的很慢
                break;
        }else if(rc == 0){
            *ptr = 0;
            return n-1;
        }else  
            return -1;
    }
    *ptr = 0;

    return 0;
}

int tcp4bind(short port,const char *IP) {
    struct sockaddr_in serv_addr;
    int lfd = Socket(AF_INET,SOCK_STREAM,0);
    bzero(&serv_addr,sizeof(serv_addr));
    if(IP == NULL) {
        serv_addr.sin_addr.s_addr = INADDR_ANY;
    }else{
        if(inet_pton(AF_INET,IP,&serv_addr.sin_addr.s_addr) <= 0){
            perror(IP);
            exit(1);
        }
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    return lfd;
}
































































