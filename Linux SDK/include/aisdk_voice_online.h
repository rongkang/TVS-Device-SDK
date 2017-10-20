
/**
 * @file
 * @author shengyujin
 * @date 2017/8/1
 * @brief 在线语音识别相关接口
 * @note
 */
#ifndef PACKAGE_TMS_AISDK_AISDK_VOICE_ONLINE_H
#define PACKAGE_TMS_AISDK_AISDK_VOICE_ONLINE_H

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
 * @brief 回调接口命令定义,在线识别开始，接受录音数据
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_START = 6000;

/**
 * @brief 回调接口命令定义,在线语音VAD检测到开始
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_SPEECH_START = AISDK_CMD_ONLINE_RECO_START + 1;

/**
 * @brief 回调接口命令定义,在线语音vad检测完成，可以停止输入录音数据
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_SPEECH_END = AISDK_CMD_ONLINE_RECO_START + 2;
/**
 * @brief 回调接口命令定义,返回在线识别结果
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_RESULT = AISDK_CMD_ONLINE_RECO_START + 3;
/**
 * @brief 回调接口命令定义,上报在线识别的中间结果
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_INTERMEDIATE_RESULT = AISDK_CMD_ONLINE_RECO_START + 4;
/**
 * @brief 回调接口命令定义,上报输入音频数据的音量值
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_DATA_VOLUME = AISDK_CMD_ONLINE_RECO_START + 5;
/**
 * @brief 回调接口命令定义,已取消在线识别
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_CANCELED = AISDK_CMD_ONLINE_RECO_START + 6;
/**
 * @brief 回调接口命令定义,在线识别超时，没有识别到有效输入
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_TIMEOUT = AISDK_CMD_ONLINE_RECO_START + 7;
/**
 * @brief 回调接口命令定义,在线识别出错，返回错误信息
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_ONLINE_RECO_ERROR = AISDK_CMD_ONLINE_RECO_START + 8;

/**
 * 函数返回错误码定义
 *
 * 模块还没有初始化
 */
const int AISDK_ERROR_ONLINE_RECO_NOT_STARTED = 6000;

/**
 * 函数返回错误码定义
 *
 * 创建在线识别模块失败
 */
const int AISDK_ERROR_ONLINE_RECO_CREATE_HANDLE_FAILED = AISDK_ERROR_ONLINE_RECO_NOT_STARTED + 1;

/**
 * 配置项键值定义
 */
// 配置项，key的起始值
const int AISDK_CONFIG_VOICE_ONLINE_BEGIN = 6000;
/**
 *
 * @see aisdkSetConfig()
 *
 * @brief 配置在线语音超时时间
 *
 * 配置项关键字。
 * ## 功能
 * 配置在线语音超时时间，单位ms
 * ## 值
 * 超时时长，默认10s
 * ## 示例：
 * ```
 * // 设置在线语音超时时长为10s
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_TIMEOUT,"10000")
 * ```
 */
const int AISDK_CONFIG_VOICE_ONLINE_TIMEOUT = AISDK_CONFIG_VOICE_ONLINE_BEGIN + 1;
///**
// *
// * @see aisdkSetConfig()
// *
// * @brief 配置连续对话超时时间
// *
// * 配置项关键字。
// * ## 功能
// * 配置连续对话超时时间，单位ms
// * ## 值
// * 超时时长
// * ## 示例：
// * ```
// * // 设置连续对话超时时长为10s
// * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_MORESPEECH_TIMEOUT,"10000")
// * ```
// */
////const int AISDK_CONFIG_VOICE_ONLINE_MORESPEECH_TIMEOUT = AISDK_CONFIG_VOICE_ONLINE_BEGIN + 2;

/**
 *
 * @see aisdkSetConfig()
 *
 * @brief 配置是否开启云端VAD
 *
 * 配置项关键字。
 * ## 功能
 * 配置是否开启云端VAD
 * ## 值
 * 值 |  说明
 *---|---
 * AISDK_CONFIG_VALUE_ENABLE|开启(默认)
 * AISDK_CONFIG_VALUE_DISABLE|关闭
 * ## 示例：
 * ```
 * //设置开启云端VAD
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_ENABLE_CLOUDVAD,AISDK_CONFIG_VALUE_ENABLE)
 * ```
 */
const int AISDK_CONFIG_VOICE_ONLINE_ENABLE_CLOUDVAD = AISDK_CONFIG_VOICE_ONLINE_BEGIN + 3;

/**
 *
 * @see aisdkSetConfig()
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
 * AISDK_CONFIG_VALUE_DISABLE|关闭(默认)
 * ## 示例
 * ```
 * //设置开启计算音量
 * aisdkSetConfig(AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME,AISDK_CONFIG_VALUE_ENABLE)
 * ```
 */
const int AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME = AISDK_CONFIG_VOICE_ONLINE_BEGIN + 4;



/**
 *
 * @see aisdkSetConfig()
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
//const int AISDK_CONFIG_VOICE_VAD_SILENT_MAX = AISDK_CONFIG_VOICE_ONLINE_BEGIN + 5;

// 配置项，key的结束值
const int AISDK_CONFIG_VOICE_ONLINE_END = 6999;

/**
 * @brief flags标志取值定义:清除上一次上下文
 * @deprecatede
 */
const int AISDK_FLAG_ONLINE_RECO_CLEAR_PREV_SESSION = 0x01;

/**
 * @brief flags标志取值定义:语音识别改为手动模式。
 */
const int AISDK_FLAG_ONLINE_RECO_MANUAL_MODE = 0x02;

/**
 * 返回的json数据中的code定义
 */
 /**
  * 成功
  */
const int AISDK_RESULT_CODE_ONLINE_OK = 0;

/**
 * @brief 开始一次语音识别流程
 * @param userData 自定义数据指针。callback时带回。
 * @param len 自定义数据长度。
 * @param flags 控制标志，参考AISDK_FLAG_ONLINE_RECO_*常量定义。如果不设置，传0即可。
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkStartOnlineVoice2Text(void* userData, int len, int flags);

/**
 * @brief 输入在线录音数据
 * @param data 录音数据存储区域。建议长度为4096.
 * @param dataLen 录音数据长度。
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 * @warning:
 *      上层应用应当把实时录音数据通过该接口输入到SDK（建议每次输入4096字节长度的音频）。
 *   在调用此接口过程中，会有VAD检测到开始、VAD检测到结束、实时音量、语音识别到结果等
 *   状态的回调。遇到AISDK_CMD_ONLINE_RECO_CANCELED/AISDK_CMD_ONLINE_RECO_TIME
 *   OUT/AISDK_CMD_ONLINE_RECO_ERROR/AISDK_CMD_ONLINE_RECO_RESULT时，停止调用
 *   该函数。
 */
AISDK_API_EXPORTS int aisdkInputOnlineVoice2TextAudioData(char* data, int dataLen);

/**
* @brief 取消本次语音识别
* @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
*/
AISDK_API_EXPORTS int aisdkCancelOnlineVoice2Text();

/**
* @brief 停止本次语音识别，获取语音识别结果。
 *@warning 停止后，不会中断语音识别，SDK会将现在已经接收到的音频发送到后台请求语音识别结果。
* @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
*/
AISDK_API_EXPORTS int aisdkStopOnlineVoice2Text();

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_VOICE_ONLINE_H
