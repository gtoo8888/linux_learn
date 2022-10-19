#include <signal.h>
#include <shttpd.h>



int main(int argc,char *argv[]) {
    signal(SIGINT,sig_int);         //挂接信号SIGINT
    Para_Init(argc,argv);           //参数初始化
    int s = do_listen();            //套接字初始化
    Worker_ScheduleRun(s);          //任务调度
    return 0;
}

//SIGINT信号截取函数
static void sig_int(int num){
    Worker_ScheduleStop();
    return;
}


