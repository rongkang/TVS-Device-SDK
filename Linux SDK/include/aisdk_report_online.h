/**
 * @file
 * @author cassliu
 * @date 2017/9/14
 * @brief 上报相关接口
 * @note 为了获得更精准的语义和服务结果，开发者需要调用使用该函数库，上报状态。
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

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_REPORT_H
