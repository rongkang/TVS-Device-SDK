/**
 * @file
 * @author shengyujin
 * @date 2017/8/1
 * @brief 在线TTS相关接口
 * @note
 */

#ifndef PACKAGE_TMS_AISDK_AISDK_TTS_ONLINE_H
#define PACKAGE_TMS_AISDK_AISDK_TTS_ONLINE_H

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
 * @brief 回调接口命令定义，当TTS返回结果时发出
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TTS_RESULT = 4000;
/**
 *
 * @brief 回调接口命令定义，当TTS返回出错时发出
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_TTS_ERROR = AISDK_CMD_TTS_RESULT + 1;

// 配置项，key的起始值
const int AISDK_CONFIG_TTS_ONLINE_BEGIN = 4000;
// 配置项，key的结束值
const int AISDK_CONFIG_TTS_ONLINE_END = 4999;

/**
 * 返回的json数据中的code定义
 */

/**
 * @brief TTS的语音包返回code，标识中间语音数据包
 * @note
 */
const int AISDK_RESULT_CODE_TTS_DATA = 0;
/**
 * @brief TTS的最后一个语音包返回code，标识最后一个语音数据包。
 * @note
 * 与AISDK_RESULT_CODE_TTS_DATA的不同在于:当文本较短时，tts语音包较短，只会有AISDK_RESULT_CODE_TTS_LAST_DATA
 */
const int AISDK_RESULT_CODE_TTS_LAST_DATA = 1;

/**
 * @brief TTS识别接口， TTS结果通过回调异步回调返回
 * @param text 需要转语音的文本，以utf8格式编码的文本串，以'\0'结尾
 * @param textLen  文本长度
 * @param userData 自定义数据
 * @param len 自定义数据长度
 * @return 0:ok, other：fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkText2Speech(const char* text, int textLen, void* userData, int len);
/**
 * @brief 取消此次的TTS请求
 * @warning 取消后， 这一次的tts请求结果不再返回。
 * @return 0:ok other:fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkCancelText2Speech();

#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_TTS_ONLINE_H
