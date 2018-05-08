/**
 * @file
 * @author kangrong
 * @date 2018/3/13
 * @brief 手机与设备通信相关接口。
 * @note 用来实现设备发现、手机指令接收相关功能。
 * @copyright © 2017 TENCENT. All rights reserved.
 */
#ifndef PACKAGE_TMS_AISDK_AISDK_RECV_H
#define PACKAGE_TMS_AISDK_AISDK_RECV_H

#ifdef WIN32
#define AISDK_API_EXPORTS __declspec(dllexport)
#define AISDK_CALL_CONV __stdcall
#else
#define AISDK_API_EXPORTS
#define AISDK_CALL_CONV
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief  回调接口命令定义,获得设备基本信息，初始化后就会回调。
 * @note 获得设备基本信息。上层收到此CMD时，应当调用aisdkRecvSendDeviceInfo把设备信息设置到SDK中。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_GET_INFO = 9000;
/**
 * @brief  回调接口命令定义,获得AP列表。
 * @note 上层收到此CMD时，应当调用aisdkRecvSendApListByJson或者aisdkRecvSendApList把附件的Wifi信息发送到SDK中。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_GET_AP_LIST = 9001;
/**
 * @brief  回调接口命令定义,连接AP。
 * @note 上层收到此CMD时，应从返回的数据中取得要连接wifi信息，然后让设备连接wifi。
 * 最后应当调用aisdkRecvSendConnectState把Wifi连接情况发送到SDK中。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_CONNECT_AP = 9002;

/**
 * @brief  回调接口命令定义,通知上层手机端传过来账户信息事件。
 * @note 当手机端跟SDK绑定的时候，此CMD会被回调。如果需要获取详细的账户信息，可以调用aisdkGetAccountClientId。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_ON_BIND_SUCCESS = 9003;
/**
 * @brief  回调接口命令定义,恢复出厂设置。
 * @note 恢复出厂设置。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_RESTORE = 9004;
/**
 * @brief 回调接口命令定义,通知上层绑定状态解除事件。
 * @note 通知上层绑定状态解除事件。当手机端与SDK解除绑定时，此CMD会被回调。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_LOGOUT = 9005;

/**
 * @brief 回调接口命令定义,连接AP状态回调。
 * @note 特殊用途，可忽略。连接AP状态回调。当aisdkRecvSendConnectState发送成功或者失败的时候都会回调这个命令。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_RECV_CONNECT_AP_STATUS = 9006;


typedef enum {
    PAIRFAIL,       // 密码错误
    FAIL,           // 错误
    OK              // 连接成功
} AISDKConnectState;
typedef struct {
    char* ssid;      // ssid，应该用十六进制编码
    char* bssid;     // mac地址
    int rssi;           // 信号强度，
    int channel;        // 信道
    char* auth;      // 是否加密。WPA2PSK、OPEN，OPEN表示未加密
    char* encry;     // 加密类型。AES、TKIP或者NONE，NONE表示未加密
    char* extch;        //
} AISDKAPInfo;
/**
 * @brief 向SDK传递设备信息。
 * @note 当收到CMD:AISDK_CMD_RECV_GET_INFO时应该调用此函数
 * @param deviceSerialNum 设备序列号，应能唯一识别一台设备
 * @param productId 产品ID。叮当平台分配
 * @param apName 出厂设备开启的AP SSID。
 * @param netCard 网卡名，如果网卡没有特殊配置，传NULL即可，默认是wlan0。
 * @param guid 默认传NULL即可。
 * @return 0表示成功，其他表示失败
 */
AISDK_API_EXPORTS int aisdkRecvSendDeviceInfo(const char* deviceSerialNum, const char* productId, const char* apName,
                                              const char* netCard, const char* guid);
/**
 * @brief 将附件的wifi热点信息以json形式发送给SDK
 * @note 当收到CMD:AISDK_CMD_RECV_GET_AP_LIST时应该调用此函数或者aisdkRecvSendApList
 * @param apListJson wifi热点json格式。<br>
 * 示例
 * ```
 * {"res":"1",
 *  "aplist":[
 *      {"ssid":"wmmAudio_a7b8",
 *      "bssid":"00:22:6c:00:a7:b8",
 *      "rssi":"76",
 *      "channel":"1",
 *      "auth":"OPEN",
 *      "encry":"NONE",
 *      "extch":"1"
 *      }]
 * }
 * ```
 * 数据说明<br>
 * 字段|说明
 * --|--
 * res|返回列表数量
 * aplist|ssid列表
 * ssid|Wifi的可见名称, 应该用十六进制编码。
 * bssid|Mac地址
 * rssi|信号强度，正整数形式。
 * channel|Wifi的信道
 * auth|是否加密。OPEN表示未加密，WPA2PSK表示加密
 * encry|加密类型。AES或者NONE
 * @param length apListJson字符串长度
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvSendApListByJson(const char* apListJson, int length);
/**
 * @brief 将附近的wifi热点信息发送给SDK。
 * @note 当收到CMD:AISDK_CMD_RECV_GET_AP_LIST时应该调用此函数或者aisdkRecvSendApListByJson
 * @param apList ap列表
 * @param length apList数组长度
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvSendApList(const AISDKAPInfo* apList, int length);
/**
 * @brief 向SDK发送连接wifi热点状态。
 * @note 在收到CMD:AISDK_CMD_RECV_CONNECT_AP时，连接结果应当用此函数发送给SDK。
 * @param state 连接状态
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvSendConnectState(AISDKConnectState state);

/**
 * @brief 启动传输数据的HttpServer。SDK启动时默认就会启动HttpServer
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvStartHttpServer();
/**
 * @brief 关闭传输数据的HttpServer
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvStopHttpServer();
/**
 * @brief 启动设备发现功能。SDK启动时默认就会启动设备发现功能。
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvStartDeviceDiscovery();
/**
 * @brief 关闭设备发现功能。
 * @return 0:成功 其他失败
 */
AISDK_API_EXPORTS int aisdkRecvStopDeviceDiscovery();

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_RECV_H
