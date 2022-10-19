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


// ���̻߳ص�����:
void *thread_work(void *arg) {
    // sleep(10); //��߼���sleep�Ϳ��Կ���cfd��ֵ��������һ���ͻ����źŵķ��������ı���
    //��ò���:ͨ���ļ�������
    int cfd = *(int *)arg;
    // ����sleep�������������棬��û�����ˣ���Ϊcfd�Ѿ����ı���

    int n = 0,i = 0;
    char buf[128];
    while(1){
        memset(buf,0x00,sizeof(buf));
        n = Read(cfd,buf,sizeof(buf));//������
        if(n <= 0) {
            printf("read error or client close,n==[%d]\n",n);
            //perror��ò�Ҫ�����߳�����
            break;
        }
        printf("n==[%d],buf==[%s]\n",n,buf);
        for(i = 0;i < n;i++) {
            buf[i] = toupper(buf[i]);//ת���ɴ�д
        }
        Write(cfd,buf,n);//������
    }
    close(cfd);
    pthread_exit(NULL);
}


int main(){
    // ����socket
    int lfd = Socket(AF_INET,SOCK_STREAM,0);

    // ��
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = Bind(lfd,(struct sockaddr*)&serv,sizeof(serv));

    //����
    Listen(lfd,128);

    int cfd;
    pthread_t threadID;
    struct sockaddr_in client;
    while(1) {
        //�����µĿͻ�����������
        cfd = Accept(lfd,NULL,NULL);

        //����һ�����߳�
        pthread_create(&threadID,NULL,thread_work,&cfd);
        //thread_work�̻߳ص�����

        //�����߳�Ϊ��������
        pthread_detach(threadID);
    }
    //�رռ����ļ�������
    Close(lfd);
    return 0;
}





// ���⣺
// 1.lfd�ܲ��������߳�ִ�к����йر�
// 2.�����������Ͽͻ���ͬʱ������cfd��ʲô�������
// ���̶߳����cfd,���Ա��������̹߳�����ôcf�����ֵ����˭��ֵ�����һ����ֵ


// 1���߳��ܷ�ر�lfd
// 2���߳��ܷ�ر�cfd
// 3������̹߳���cfd������ʲô���ⷢ��?l


// gcc XXX -lpthread

































