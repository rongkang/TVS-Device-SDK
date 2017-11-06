/*!
 @header VoiceSession.h
 @brief 语音识别能力提供者
 @author zacardfang
 @copyright © 2017 TENCENT. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "SpeechEngine.h"

/*! @brief 语音识别回调接口
 *
 * VoiceSessionDelegate 会在VoiceSession对象中注入
 */
@protocol VoiceSessionDelegate <NSObject>

/*!
 @brief 语音识别回调

 @param cmd 参照cmd说明,K_AISDK_CMD_ONLINE_RECO_xx
 @param code 通常返回0
 @param data 识别结果
 @param userData 自定义数据
 */
-(void)onOnlineVocieCallback:(NSInteger)cmd code:(NSInteger)code data:(NSString *)data userData:(id)userData;

/*!
 @brief 语音识别异常回调
 
 @param cmd 参照cmd说明, K_AISDK_ERROR_ONLINE_RECO_xx
 @param code 返回的json数据错误码，参照语义说明文档解析
 @param message 错误信息
 @param userData 自定义数据
 */
-(void)onOnlineVocieError:(NSInteger)cmd code:(NSInteger)code message:(NSString *)message userData:(id)userData;

@end

@interface VoiceSession : NSObject<SessionDelegate>

@property(nonatomic, assign)id<VoiceSessionDelegate> delegate;
@property(nonatomic, strong)dispatch_queue_t voiceQueue;

/*！
 * @brief 开始一次语音识别流程
 * @param userdata 自定义数据指针。callback时带回。
 * @param flags 控制标志，参考K_AISDK_FLAG_ONLINE_RECO_*常量定义。如果不设置，传0即可。
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 */
-(int)startVoice2text:(NSInteger)mode;

/*!
 * @brief 输入录音数据
 * @param audioBuffer 上传音频数据
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 * @warning:
 *      上层应用应当把实时录音数据通过该接口输入到SDK（建议每次输入4096字节长度的音频）。
 *   在调用此接口过程中，会有VAD检测到开始、VAD检测到结束、实时音量、语音识别到结果等
 *   状态的回调。遇到AISDK_CMD_ONLINE_RECO_CANCELED/AISDK_CMD_ONLINE_RECO_TIME
 *   OUT/AISDK_CMD_ONLINE_RECO_ERROR/AISDK_CMD_ONLINE_RECO_RESULT时，停止调用
 *   该函数。
 */
-(int)inputVoice2TextAudioData:(NSData *)audioBuffer;

/*!
 * @brief 取消本次语音识别
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 */
-(int)cancelVoice2Text;

/*!
 * @brief 停止本次语音识别，获取语音识别结果。
 * @warning 停止后，不会中断语音识别，SDK会将现在已经接收到的音频发送到后台请求语音识别结果。
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 */
-(int)stopVoice2Text;

@end

//常量定义

/*------语音识别--------*/
/*!
 * @brief 回调接口命令定义,在线识别开始，接受录音数据
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_START;

/*!
 * @brief 回调接口命令定义,在线语音VAD检测到开始
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_SPEECH_START;          // 在线语音VAD检测到开始

/*!
 * @brief 回调接口命令定义,在线语音vad检测完成，可以停止输入录音数据
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_SPEECH_END;                     // 在线语音vad检测完成，可以停止输入录音数据
/*!
 * @brief 回调接口命令定义,返回在线识别结果
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_RESULT;                   // 返回在线识别结果
/*!
 * @brief 回调接口命令定义,上报在线识别的中间结果
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_INTERMEDIATE_RESULT;      // 上报在线识别的中间结果
/*!
 * @brief 回调接口命令定义,上报输入音频数据的音量值
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_DATA_VOLUME;      // 上报输入音频数据的音量值
/*!
 * @brief 回调接口命令定义,已取消在线识别
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_CANCELED;                   // 已取消在线识别
/*!
 * @brief 回调接口命令定义,在线识别超时，没有识别到有效输入
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_TIMEOUT;                   // 在线识别超时
/*!
 * @brief 回调接口命令定义,在线识别出错，返回错误信息
 * @see VoiceSessionDelegate
 */
extern const int K_AISDK_CMD_ONLINE_RECO_ERROR;                   // 在线识别出错

/*!
 * 错误码定义
 *
 * 模块还没有初始化
 */
extern const int K_AISDK_ERROR_ONLINE_RECO_NOT_STARTED;

/*!
 * 错误码定义
 *
 * 创建在线识别模块失败
 */
extern const int K_AISDK_ERROR_ONLINE_RECO_CREATE_HANDLE_FAILED;

/*!
 * 配置项键值定义
 */
// 配置项，key的起始值
extern const int K_AISDK_CONFIG_VOICE_ONLINE_BEGIN;
/*!
 *
 * @see setConfig:value:
 *
 * @brief 配置在线语音超时时间
 *
 * 配置项关键字。
 * ## 功能
 * 配置在线语音超时时间，单位ms
 * ## 值
 * 超时时长
 * ## 示例：
 * ```
 * // 设置在线语音超时时长为10s
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_TIMEOUT,"10000")
 * ```
 */
extern const int K_AISDK_CONFIG_VOICE_ONLINE_TIMEOUT;
/*!
 *
 * @see setConfig:value:
 *
 * @brief 配置连续对话超时时间
 *
 * 配置项关键字。
 * ## 功能
 * 配置连续对话超时时间，单位ms
 * ## 值
 * 超时时长
 * ## 示例：
 * ```
 * // 设置连续对话超时时长为10s
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_MORESPEECH_TIMEOUT,"10000")
 * ```
 */
extern const int K_AISDK_CONFIG_VOICE_ONLINE_MORESPEECH_TIMEOUT;

/*!
 *
 * @see setConfig:value:
 *
 * @brief 配置是否开启云端VAD
 *
 * 配置项关键字。
 * ## 功能
 * 配置是否开启云端VAD
 * ## 值
 * 值 |  说明
 *---|---
 * AISDK_CONFIG_VALUE_ENABLE|开启
 * AISDK_CONFIG_VALUE_DISABLE|关闭
 * ## 示例：
 * ```
 * //设置开启云端VAD
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_ENABLE_CLOUDVAD,AISDK_CONFIG_VALUE_ENABLE)
 * ```
 */
extern const int K_AISDK_CONFIG_VOICE_ONLINE_ENABLE_CLOUDVAD;

/*!
 *
 * @see setConfig:value:
 *
 * @brief 配置是否开启计算音量
 *
 * 配置项关键字
 * ## 功能
 * 配置是
 * 否开启计算音量
 * ## 值
 * 值 |  说明
 *---|---
 * AISDK_CONFIG_VALUE_ENABLE|开启
 * AISDK_CONFIG_VALUE_DISABLE|关闭
 * ## 示例
 * ```
 * //设置开启计算音量
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME,AISDK_CONFIG_VALUE_ENABLE)
 * ```
 */
extern const int K_AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME;



/*!
 *
 * @see setConfig:value:
 *
 * @brief 配置vad静音超时时间，默认500ms
 *
 * 配置项关键字
 * ## 功能
 * 配置vad静音超时时间
 * ## 值
 * ## 示例
 * ```
 * //设置静音时间为500ms
 * aisdkSetConfig(AISDK_CONFIG_VAD_SILENT_MAX,"500")
 * ```
 */
extern const int K_AISDK_CONFIG_VOICE_VAD_SILENT_MAX;

// 配置项，key的结束值
extern const int K_AISDK_CONFIG_VOICE_ONLINE_END;

/**
 * @brief flags标志取值定义:语音识别改为模式。
 */
//extern const int K_AISDK_FLAG_ONLINE_RECO_CLEAR_PREV_SESSION;     // 清空上一次请求的上下文

/*!
 * @brief flags标志取值定义:语音识别改为手动模式。
 */
extern const int K_AISDK_FLAG_ONLINE_RECO_MANUAL_MODE;     // 语音识别改为手动模式。

/*!
 * @brief 返回的json数据中的code定义,成功
 */
extern const int K_AISDK_RESULT_CODE_ONLINE_OK;
