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

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_REPORT_H
