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

    // ����һ��epoll��
    //���ظ��ļ�������,����ļ��������ͱ�ʾepoll���������ڵ�
    int epfd = epoll_create(1024);
    if(epfd < 0){
        perror("create epoll error");
        return -1;
    }

    //�������ļ�����������
    struct epoll_event ev;
    ev.events = EPOLLIN;    //�ɶ��¼�
    ev.data.fd = lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);  //���ں˼���lfd


    char buf[1024];
    int nready;
    struct epoll_event events[1024];
    while(1){//����whileѭ�����ȴ��¼�����
        nready = epoll_wait(epfd, events,1024,-1);//һֱ����
        //ֻҪepoll_wait�����ˣ���һ�����¼�������
        //events������ʱ����ʲô��������ʱ�����ʲô
        //д������������select�򵥣���Ϊepollֻ�������仯���¼�ͨ��events�������ǣ�û�б仯��û��˵

        if(nready < 0) {    
            perror("epoll_wait error");
            if(errno == EINTR)  //����Ǳ��ź��ж�
                continue;
            break;
        }

        for(int i = 0;i < nready;i++){
            int sockfd = events[i].data.fd;
            //�пͻ�������������
            if(sockfd == lfd) {
                int cfd = accept(lfd,NULL,NULL);

                //��cfd��Ӧ�Ķ��¼���epoll��
                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
                continue;

            }

            //�пͻ��˷������ݹ���
            memset(buf,0x00,sizeof(buf));
            int n = read(sockfd,buf,sizeof(buf));//read����
            if(n <= 0){
                close(sockfd);
                //��sockfd��Ӧ���¼��ڵ��epoll����ɾ��
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                perror( "read error or client closed");
                continue;
            }else{
                printf("n==[%d],buf==[%s]\n",n,buf);
                for(int k = 0;k < n;k++) 
                    buf[k] = toupper(buf[k]);//ת���ɴ�д
                write(sockfd,buf,n);//writeӦ�����ݸ��ͻ���
            }
        }
    }
    close(epfd);
    close(lfd);

    return 0;
}










































