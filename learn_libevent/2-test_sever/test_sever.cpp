#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <signal.h>
#include <string.h>

void listen_cb(struct evconnlistener *e, evutil_socket_t s, struct sockaddr *a, int socklen, void *arg){
    std::cout << "listen_cb\n"; 
}

int main(){
    // 忽略SIGPIPE信号，防止因为客户端断开连接而导致服务器退出
    if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
        return 1;
    std::cout << "test libevent\n" ;
    event_base *base = event_base_new();
    if(base)
        std::cout << "event_base_new success\n";

    sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(5001);
    //socket, bind, listen
    evconnlistener *ev = evconnlistener_new_bind(base, //libevent上下文
        listen_cb, // 回调函数
        base, // 回调函数获取的参数
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,  // 地址重用，listen关闭同时关闭socket
        10,// 连接队列大小，对应listen函数
        (sockaddr*)&sin,
        sizeof(sin)
        );

    // 事件分发处理
    if(base)
        event_base_dispatch(base);
    if(ev)
        evconnlistener_free(ev);

    if(base)
        event_base_free(base);
    return 0;
}



