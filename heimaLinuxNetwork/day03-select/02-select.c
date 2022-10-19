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
    //����fd_set���͵ı���
    fd_set readfds;         //�����ļ�������������
    fd_set tmpfds;          //Ϊ�˷�ֹreadfds���ı䣬�����������ʱ����������һ��

    //���readfds��tmpfds����
    FD_ZERO(&readfds);      //����ļ�������������
    FD_ZERO(&tmpfds);

    //��lfd���뵽readfds��,ί���ں˼��
    FD_SET(lfd,&readfds);   
    int maxfd = lfd;
    int i,n;
    int nready;
    char buf[1024];
    while(1) {
        // int select(int nfds, fd_set *readfds, fd_set *writefds,
        //           fd_set *exceptfds, struct timeval *timeout); 
        //ί���ں˼�ؿɶ�,��д,�쳣�¼�   
        tmpfds = readfds;   //��ֹreadfds�������Ժ�ǰ��Ͳ�������
        //tmpfds�������������:
        //����:�����ں�Ҫ�����Щ�ļ�������
        //���:�ں˸���Ӧ�ó�������Щ�ļ������������˱仯
        nready = select(maxfd+1,&tmpfds,NULL,NULL,NULL);
        //���ھͼ�ؿɶ����ļ�������
        //�Կ�д���쳣�¼��������ģ���ʱ�¼�NULL����ʾ��������
        if(nready < 0) {    //�����˴���
            if(errno == EINTR)  //����Ǳ��ź��жϵģ��ǾͿ��Լ���
                continue;
            break;
        }

        //����пͻ�������������
        if(FD_ISSET(lfd,&tmpfds)){
            cfd = accept(lfd,NULL,NULL);//��ô�ͽ����µĿͻ�����������
            FD_SET(cfd,&readfds);//��cfd���뵽readfds������

            if(maxfd < cfd)//�޸��ں˼�ص��ļ��������ķ�Χ
                maxfd = cfd;
            
            if(--nready == 0)//�������ֻ��һ���ͻ��˵����ӷ������ˣ��Ͳ��ü�����������
                continue;
        }

        //�пͻ������ݷ���
        for(i = lfd+1;i <= maxfd;i++){//��ûһ�����Ӷ�����һ��
            int sockfd = i;
            //�ж�sockfd�ļ��������Ƿ��б仯
            if(FD_ISSET(sockfd,&tmpfds)){
                n = read(sockfd,buf,sizeof(buf));//read����
                if(n <= 0){
                    close(i);
                    FD_CLR(sockfd,&readfds);//���ļ�������sockfd���ں���ȥ��

                }else{
                    printf("n==[%d],buf==[%s]\n",n,buf);
                    for(int k = 0;k < n;k++) 
                        buf[k] = toupper(buf[k]);//ת���ɴ�д
                    write(sockfd,buf,n);//writeӦ�����ݸ��ͻ���
                }


                if(--nready == 0)
                    break;
                
            }
        }

    }

    close(lfd);

    return 0;
}










































