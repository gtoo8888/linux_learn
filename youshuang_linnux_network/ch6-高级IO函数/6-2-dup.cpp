#include <stdio.h>
#include <libgen.h> // man 3 basename
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h> // atoi
#include <string.h>
#include <assert.h>
#include <unistd.h> //dup,STDOUT_FILENO

int main(int argc,char* argv[]){
    if(argc < 2){
        printf("%s\n",basename(argv[0])); //得到特定的路径中的最后一个'/',后面的内容
            // 得到文件名
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);   // 字符串数字转整型

    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);


    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);
    int ret = bind(sock,(struct sockaddr *)&address,sizeof(address));
    assert(ret != -1);
    listen(sock,5);
    assert(ret != -1);


    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int connfd = accept(sock,(struct sockaddr*)&client,&len); 
    if(connfd < 0){

    }else{
        close(STDOUT_FILENO);   // 关闭标准输出文件描述符
        dup(connfd);
        printf("abcd\n");   // 这个printf的内容会直接发送到客户端上
        close(connfd);
    }
    close(sock);
    return 0;


    return 0;
}