/**
 * @file
 * @author kangrong
 * @date 2017/8/28
 * @brief 示例代码：设备接收手机指令进行配网
 * @version 0.1.0
 * @note
 */


#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <sstream>

#include "aisdk_common_api.h"
#include "aisdk_account_online.h"
#include "aisdk_recv.h"
using namespace std;
void * myGetApThread(void *args){
    string apList;
    /**
     * getAPList(apList);获取ap列表需要实现
     *
     */

    aisdkRecvSendApListByJson(apList.c_str(),apList.size());
    return NULL;
}

void * myConnectApThread(void *args){

    //连接ap，需要实现

    //连接成功就发送成功给SDK。
    aisdkRecvSendConnectState(AISDKConnectState::OK);
    //aisdkRecvSendConnectState(AISDKConnectState::FAIL);
    return NULL;
}

void callback(int cmd, char* data, int dataLen, void* userData, int userDataLen, void *extra, int extraLen)
{
    // 任何情况下，不要阻塞回调线程。
    string result(data, dataLen);
    cout << "callback cmd: " << cmd  << "  result:"<<result<<endl;

    switch(cmd) {
        case AISDK_CMD_RECV_GET_INFO:{
            cout<<"CMD: AISDK_CMD_RECV_GET_INFO"<<endl;
            aisdkRecvSendDeviceInfo("deviceSerialNum", "productId", "AP_NAME", "wlan0", NULL);
            break;
        }
        case AISDK_CMD_RECV_ON_BIND_SUCCESS:{
            //账号登录
            cout<<"CMD: AISDK_CMD_BIND_ON_BIND_SUCCESS"<<endl;

            /**
             * 可以通过以下代码获得clientId
                char* clientId=NULL;
                int ret=aisdkGetAccountClientId(&clientId);
             */
            break;
        }
        case AISDK_CMD_RECV_CONNECT_AP:{

            cout<<"CMD: AISDK_CMD_BIND_CONNECT_AP"<<endl;
            /**
             * 解析json数据，连接ap。并将连接状态发送给SDK。
             *
             *
             */
            pthread_t connectApThread;
            pthread_create(&connectApThread, NULL, myConnectApThread, NULL);

            break;
        }
        case AISDK_CMD_RECV_GET_AP_LIST:{
            //完成
            cout<<"CMD: AISDK_CMD_BIND_GET_AP_LIST"<<endl;
            pthread_t getApThread;
            pthread_create(&getApThread,NULL,myGetApThread,NULL);
            break;
        }

        case AISDK_CMD_RECV_LOGOUT:{
            // 账号登出
            cout<<"CMD: AISDK_CMD_BIND_LOGOUT"<<endl;

            break;
        }
        case AISDK_CMD_RECV_RESTORE:{
            // 恢复出厂设置。
            cout<<"CMD: AISDK_CMD_BIND_RESTORE"<<endl;

            break;
        }
        case AISDK_CMD_RECV_CONNECT_AP_STATUS:{
            // 上层可以忽略
            cout<<"CMD: AISDK_CMD_BIND_CONNECT_AP_STATUS"<<endl;

            break;
        }
        default:
            cout<<"CMD: OTHER"<<endl;
            break;
    }

}

/**
 * 程序后面跟一个参数，指定读取的录音文件。
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{

    //先设置回调函数
    aisdkSetCallback(callback);
    //初始化SDK
    int res = aisdkInit(".", "1234", "asdf");

    if(res != 0) {
        std::cerr << "init iva fail, err:" << res << std::endl;
        return -2;
    }


    std::string cmd;
    while(true) {
        std::cout << "cmd>>> 1:退出" << std::endl;
        std::cin >> cmd;
        int ran_num = rand() % 4;
        std::cout << "cmd:" << cmd << std::endl;
        if (cmd == "1") {
            std::cout << "退出测试程序" << std::endl;
            break;
        } else {
            std::cerr << "cmd:" << cmd << ", not match 1/2/3/4/5" << std::endl;
        }

        sleep(5);   // 由于异步操作，主线程等待5s
    }
    return 0;
}