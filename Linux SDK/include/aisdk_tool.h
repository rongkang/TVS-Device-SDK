//
// Created by kangrong on 2017/11/3.
//

#ifndef PACKAGE_TMS_AISDK_AISDK_TOOL_H
#define PACKAGE_TMS_AISDK_AISDK_TOOL_H
/**
 * @file
 * @author kangrong
 * @date 2017/11/3
 * @brief 设备扫描、配网相关接口
 * @note
 * @copyright © 2017 TENCENT. All rights reserved.
 */

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
 * @brief  回调接口命令定义,UDP Server开启成功
 * @note 返回UDP Server启动成功
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TOOL_BIND_SERVER_STARTED = 8000;
/**
 * @brief 回调接口命令定义
 * @note 返回绑定结果
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TOOL_BIND_RESULT = AISDK_CMD_TOOL_BIND_SERVER_STARTED + 1;
/**
 * @brief 回调接口命令定义，UDP SERVER已经关闭。
 * @note SERVER关闭
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TOOL_BIND_SERVER_STOPED = AISDK_CMD_TOOL_BIND_SERVER_STARTED + 2;


/**
 * @brief 回调接口命令定。
 * @note 配网成功
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TOOL_BIND_NETWORK_CONNECTED = AISDK_CMD_TOOL_BIND_SERVER_STARTED + 3;

/**
 * @brief 错误码定义: 加载动态库错误
 */
const int AISDK_ERROR_TOOL_SO_INVALID=8000;
/**
 * @brief 当被扫描的时候，设置设备显示的数据。
 *
 * @param manufacturer 制造商
 * @param deviceName 设备名称
 * @param brandIcon 品牌图片标识
 * @param productId 设备唯一ID
 * @param dsn
 * @param mac 设备mac地址
 * @param os 设备操作系统
 * @param package 包名
 * @return
 */
AISDK_API_EXPORTS int aisdkSetDeviceShowInfo(const char * manufacturer,
                                             const char * deviceName,
                                             const char * brandIcon,
                                             const char * productId,
                                             const char * dsn,
                                             const char * mac,
                                             const char * os,
                                             const char *package
                                            );
/**
 * @brief 开启设备UDP 服务，等待被扫描
 */
AISDK_API_EXPORTS void aisdkStartUdpServer();
/**
 * @brief 关闭设备UDP 服务，停止被扫描
 */
AISDK_API_EXPORTS void aisdkStopUpdServer();

/**
 * @brief 设置配网so和配网类型。
 *
 * @param type
 *
 * |type|说明
 * |--|--|
 * |1 |AP配网|
 * @param soPath 配网so路径。so应实现相应的接口。
 * @return 0 成功
 */

AISDK_API_EXPORTS int aisdkSetNetworkPlugin(int type, const char * soPath);


#ifdef __cplusplus
}
#endif


#endif //PACKAGE_TMS_AISDK_AISDK_TOOL_H
