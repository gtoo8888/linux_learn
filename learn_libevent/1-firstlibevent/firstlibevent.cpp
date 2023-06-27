#include <event2/event.h>
#include <iostream>
using namespace std;

int main(){
    std::cout << "test libevent\n" ;
    event_base *base = event_base_new();
    if(base){
        std::cout << "event_base_new success\n";
    }else{
        std::cout << "event_base_new failed\n";
    }
    return 0;
}