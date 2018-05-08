/**
 * @file
 * @author cassliu
 * @date 2017/9/14
 * @brief 上报相关接口
 * @note 为了获得更精准的语义和服务结果，开发者需要调用使用该函数库，上报状态。
 * @copyright © 2017 TENCENT. All rights reserved.
 */
#ifndef PACKAGE_TMS_AISDK_AISDK_REPORT_H
#define PACKAGE_TMS_AISDK_AISDK_REPORT_H

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
 * @brief  回调接口命令定义，媒体播放开始状态上报成功
 * @note 上报媒体播放开始状态成功。上层收到此CMD时，可以确保服务端已正确处理了上报，有些业务可能依赖此状态。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS = 10000;

/**
 * @brief  回调接口命令定义，媒体播放开始状态上报失败
 * @note 上报媒体播放开始状态失败。上层收到此CMD时，可能因为网络原因导致上报失败，可以尝试重试上报。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_STARTED_ERROR = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 1;

/**
 * @brief  回调接口命令定义，媒体播放被切换状态上报成功
 * @note 上报媒体播放被切换状态成功。上层收到此CMD时，可以确保服务端已正确处理了上报，有些业务可能依赖此状态。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_STOPPED_SUCCESS = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 2;

/**
 * @brief  回调接口命令定义，媒体播放被切换状态上报失败
 * @note 上报媒体播放被切换状态失败。上层收到此CMD时，可能因为网络原因导致上报失败，可以尝试重试上报。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_STOPPED_ERROR = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 3;

/**
 * @brief  回调接口命令定义，媒体播放结束状态上报成功
 * @note 上报媒播放结束体状态成功。上层收到此CMD时，可以确保服务端已正确处理了上报，有些业务可能依赖此状态。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_FINISHED_SUCCESS = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 4;

/**
 * @brief  回调接口命令定义，媒体播放结束状态上报失败
 * @note 上报媒体播放结束状态失败。上层收到此CMD时，可能因为网络原因导致上报失败，可以尝试重试上报。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_MEDIA_FINISHED_ERROR = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 5;

/**
 * @brief  回调接口命令定义，通用终端状态上报成功
 * @note 通用终端状态上报成功。上层收到此CMD时，可以确保服务端已正确处理了上报，有些业务可能依赖此状态。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_CLIENT_STATE_SUCCESS = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 6;

/**
 * @brief  回调接口命令定义，通用终端状态上报失败
 * @note 通用终端状态上报失败。上层收到此CMD时，可能因为网络原因导致上报失败，可以尝试重试上报。
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_REPORT_CLIENT_STATE_ERROR = AISDK_CMD_REPORT_MEDIA_STARTED_SUCCESS + 7;

/**
 * @brief 上报，只是做记录
 * @note 异常上报的Level
 * @see aisdkReportError
 */
const int EXCEPTION_LEVEL_REPORT = 1;
/**
 * @brief 一般
 * @note 异常上报的Level
 * @see aisdkReportError
 */
const int EXCEPTION_LEVEL_WARNNING = 2;
/**
 * @brief 注意
 * @note 异常上报的Level
 * @see aisdkReportError
 */
const int EXCEPTION_LEVEL_MINOR = 3;
/**
 * @brief 严重
 * @note 异常上报的Level
 * @see aisdkReportError
 */
const int EXCEPTION_LEVEL_MAJOR = 4;
/**
 * @brief 极其严重
 * @note 异常上报的Level
 * @see aisdkReportError
 */
const int EXCEPTION_LEVEL_CRITICAL = 5;

/**
 *
 * @brief 统计媒体播放开始
 * @param in mediaId 媒体的id，由服务器下发
 * @return
 * @note
 * 当媒体开始播放的时候调用
 */
AISDK_API_EXPORTS void aisdkReportMediaStarted(const char* mediaId);

/**
 *
 * @brief 统计媒体被切换
 * @param in mediaId 媒体的id，由服务器下发
 * @param in duration 媒体播放了多长时间（毫秒）
 * @return
 * @note
 * 当媒体被切换成其他媒体的时候调用
 */
AISDK_API_EXPORTS void aisdkReportMediaStopped(const char* mediaId, long long duration);

/**
 *
 * @brief 统计媒体播放结束
 * @param in mediaId 媒体的id，由服务器下发
 * @param in duration 媒体播放的时长（毫秒）
 * @return
 * @note
 * 当媒体播放完成后调用
 */
AISDK_API_EXPORTS void aisdkReportMediaFinished(const char* mediaId, long long duration);

/**
 *
 * @brief 异常情况上报
 * @param in sbussinessName 业务名，如属于哪个上层SDK
 * @param in sVersion 业务的版本号
 * @param in sModuleName 模块名
 * @param in sFunctionName 方法名
 * @param in exceptionLevel（详见 EXCEPTION_LEVEL_* 常量）
 * @param in iErrorCode（详见 aisdk_common_api.h：AISDK_ERROR_* 常量）
 * @param in sErrorMessage 错误信息说明
 * @param in sExtraData 附加信息
 * @return
 * @note 仅限各层SDK使用
 */
AISDK_API_EXPORTS void aisdkReportError(const char* sbussinessName, const char* sVersion, const char* sModuleName,const char* sFunctionName,
                              int exceptionLevel, int iErrorCode, const char* sErrorMessage, const char* sExtraData);

/**
 *
 * @brief 通用状态上报接口
 * @param in sJsonData JSON格式的上报数据，根据类型不同数据也有所不同，具体请参考文档
 * @param void* 用户数据，调用方自定义，在回调时传回，不用可传NULL
 * @Param int 用户数据长度，在回调时传回，不用可传0
 * @return
 */
AISDK_API_EXPORTS void aisdkReportClientState(const char* sJsonData, void* userData, int userDataLen);

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_REPORT_H
