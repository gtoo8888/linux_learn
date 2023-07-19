#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(){
    // ����socket���ͻ��˵��ļ����������ںͷ����ͨѶ��
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd < 0) {
        perror("socket error!");
        return -1;
    }

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    // serv.sin_addr.s_addr = htonl(INADDR_ANY);//��ôд���Ե�
    // int inet_pton(int af, const char *src, void *dst);//��һ�����ʮ�����ַ���ת���������ַ
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
    printf("[%x]\n",serv.sin_addr.s_addr);
    // int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);  
    // ���ӷ�����
    int ret = connect(cfd,(struct sockaddr*)&serv,sizeof(serv));
    if(ret < 0) {
        perror("connect error!");
        return -1;
    }

    int i = 0;
    int n = 0;
    char buf[1024];
    while(1) {
        //����׼��������
        memset(buf,0x00,sizeof(buf));
        n = read(STDIN_FILENO,buf,sizeof(buf));//���ն˶�ȡ����
        // printf("n==[%d],buf==[%s]\n",n,buf);

        //��������
        write(cfd,buf,n);//�����ͻ�������д��˭�������������ݣ�һ�����������ں˰��������˺ܶ�����

        //������������������
        memset(buf,0x00,sizeof(buf));
        n = read(cfd,buf,sizeof(buf));
        if(n <= 0) {
            printf("read error or server close,n==[%d]\n",n);
            break;
        }
        printf("n==[%d],buf==[%s]\n",n,buf);
    }
    //�ر�ͨѶ�׽���
    close(cfd);
    return 0;
}


// netstat -anp
// ���Թ����п���ʹ��netstat����鿴����״̬������״̬
// netstat����:
// a��ʾ��ʾ����
// n��ʾ��ʾ��ʱ�������ֵķ�ʽ����ʾ
// p��ʾ��ʾ������Ϣ(�������ͽ���PID)

// name@name-hcp:~$ netstat -anp | grep 8888
//                 �Լ���һ��                  �Է���һ��
// tcp        0      0 0.0.0.0:8888            0.0.0.0:*               LISTEN      10644/./server  //listenһ�������ڷ���ˣ�˵����������Ѿ�����listen״̬��
// tcp        0      0 127.0.0.1:34568         127.0.0.1:8888          ESTABLISHED 10646/./client
// tcp        0      0 127.0.0.1:8888          127.0.0.1:34568         ESTABLISHED 10644/./server  //�������Ķ˿��ǰ󶨵�

// ESTABLISHED,���ӽ�����
// ����listen״̬�Ľ��̣����Ա��ͻ�������

// �ȹرշ���ˣ�û�����Ͻ��������ڳ��������ڶ�ȡ��׼������