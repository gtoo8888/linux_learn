#include <signal.h>
#include <shttpd.h>



int main(int argc,char *argv[]) {
    signal(SIGINT,sig_int);         //�ҽ��ź�SIGINT
    Para_Init(argc,argv);           //������ʼ��
    int s = do_listen();            //�׽��ֳ�ʼ��
    Worker_ScheduleRun(s);          //�������
    return 0;
}

//SIGINT�źŽ�ȡ����
static void sig_int(int num){
    Worker_ScheduleStop();
    return;
}


