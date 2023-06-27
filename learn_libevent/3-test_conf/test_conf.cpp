#include <event2/event.h>
#include <iostream>
#include <signal.h>
#include <string.h>

int main(){
    if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
        return 1;
    std::cout << "test libevent\n" ;

    // 创建配置上下文
    event_config *conf = event_config_new();
    if(conf)
        std::cout << "event_config_new success\n";
    else
        std::cout << "event_config_new failed\n";
    
    // 显示支持的网络模式
    const char **methods = event_get_supported_methods();
    std::cout << "supported methods:\n";
    for(int i = 0; methods[i] != NULL; ++i){
        std::cout << methods[i] << std::endl;
    }
    // 设置特征
    // 设置了EV_FEATURE_FDS,其他特征都会被忽略
    event_config_require_features(conf, EV_FEATURE_FDS);


    // 初始化配置libevent上下文
    event_base *base = event_base_new_with_config(conf);
    event_config_free(conf);
    


    if(!base){
        std::cerr << "event_base_new_with_config failed\n";
        event_base_free(base);
        base = event_base_new();
        if(!base)
            std::cerr << "event_base_new failed\n";

    }
    else{
        
        int f = event_base_get_features(base);
        if(f & EV_FEATURE_ET)
            std::cout << "EV_FEATURE_ET supported\n";
        else
            std::cout << "EV_FEATURE_ET not supported\n";

        if(f & EV_FEATURE_O1)
            std::cout << "EV_FEATURE_O1 supported\n";
        else
            std::cout << "EV_FEATURE_O1 not supported\n";

        if(f & EV_FEATURE_FDS)
            std::cout << "EV_FEATURE_FDS supported\n";
        else
            std::cout << "EV_FEATURE_FDS not supported\n";
        
        if(f & EV_FEATURE_EARLY_CLOSE)
            std::cout << "EV_FEATURE_EARLY_CLOSE supported\n";
        else
            std::cout << "EV_FEATURE_EARLY_CLOSE not supported\n";
    }

    return 0;
}



