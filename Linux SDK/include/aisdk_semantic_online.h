/**
 * @file
 * @author shengyujin
 * @date 2017/8/1
 * @brief 在线语义相关接口
 * @note
 * @copyright © 2017 TENCENT. All rights reserved.
 */
#ifndef PACKAGE_TMS_AISDK_AISDK_TEXT_ONLINE_H
#define PACKAGE_TMS_AISDK_AISDK_TEXT_ONLINE_H

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
  * @brief  回调接口命令定义,语义返回的回调
  * @note 返回语义识别结果
  * @see AISDK_CALLBACK
  */
const int AISDK_CMD_SEMANTIC_RESULT = 2000;

/**
 * @brief 回调接口命令定义,独立请求媒体的接口结果返回
 * @note aisdkReqMusic 和aisdkReqFM函数请求的音乐/fm信息语义回调
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_MEDIA_SEMANTIC_RESULT = AISDK_CMD_SEMANTIC_RESULT + 1;


/**
 * @brief  回调接口命令定义,语义返回出错
 * @note 返回语义识别结果
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_SEMANTIC_ERROR = AISDK_CMD_SEMANTIC_RESULT + 2;
/**
 * @brief 回调接口命令定义,独立请求媒体出错
 * @note aisdkReqMusic 和aisdkReqFM函数请求的音乐/fm信息语义回调
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_MEDIA_SEMANTIC_ERROR = AISDK_CMD_SEMANTIC_RESULT + 3;



/**
 * @brief 回调接口命令定义,复合语义的接口结果返回
 * @note aisdkReqMusic 和aisdkReqFM函数请求的音乐/fm信息语义回调
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_COMPLEX_SEMANTIC_RESULT = AISDK_CMD_SEMANTIC_RESULT + 4;
/**
 * @brief 回调接口命令定义,复合语义请求出错
 * @note
 * @see AISDK_CALLBACK
 */
const int AISDK_CMD_COMPLEX_SEMANTIC_ERROR = AISDK_CMD_SEMANTIC_RESULT + 5;


// 配置项，key的起始值
const int AISDK_CONFIG_SEMANTIC_ONLINE_BEGIN = 2000;
// 配置项，key的结束值
const int AISDK_CONFIG_SEMANTIC_ONLINE_END = 2999;

/**
 * @brief 请求类型：文本请求
 * @note 用于cancel(int)参数
 */
const int AISDK_SEMANTIC_REQ_TYPE_TEXT = 1;
/**
 * @brief 请求类型：复合语义请求
 * @note 用于cancel(int)参数
 */
const int AISDK_SEMANTIC_REQ_TYPE_SEMANTIC = 2;
/**
 * @brief 请求类型：复合语义请求
 * @note 用于cancel(int)参数
 */
const int AISDK_SEMANTIC_REQ_TYPE_COMPLEX_SEMANTIC = 3;

//flags标志取值定义
/**
 * 清空上一次请求的上下文
 */
const int AISDK_FLAG_SEMANTIC_CLEAR_PREV_SESSION = 0x01;

/**
 * 退出当前请求的上下文
 */
const int AISDK_FLAG_SEMANTIC_EXIT_CUR_SESSION = 0x02;

/**
 *
 * @brief 在线语义识别接口， 结果通过回调异步回调返回
 * @param text 以utf8格式编码的文本串，以'\0'结尾
 * @param textLen 文本串长度
 * @param userData 自定义信息，callback时带回。
 * @param len 自定义信息长度
 * @param flags 控制标志，参考AISDK_FLAG_SEMANTIC_*常量定义，支持多flag或运算。默认设置为0即可。
 * @return 0：ok，other：fail。 错误码定义见AISDK_ERROR_*常量
 * @note
 * 获取"上一首/下一首"等.
 */
AISDK_API_EXPORTS int aisdkOnlineText2Semantic(const char* text, int textLen, void* userData, int len, int flags);
/**
 * @brief 特殊功能性接口。复合语义
 * @param semantic 语义JSON
 * @param len 语义JSON长度
 * @param userData 自定义数据，callback时带回。
 * @param userDataLen 自定义数据长度
 *
 * @return 0:ok, other:fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkComplexSemantic2Semantic(char * semanticJson, int len,void* userData, int userDataLen);

/**
 * @brief 请求单首音乐的详细信息
 * @param mediaId 音乐ID
 * @param mediaIdLength 音乐ID长度
 * @param userData 自定义信息，callback时带回。
 * @param len 自定义信息长度
 * @return 0:success other:fail。 错误码定义见AISDK_ERROR_*常量
 * @note 播放音乐时，音乐的地址可能会有变化，播放前应该用音乐的ID请求一次新的url。
 */
AISDK_API_EXPORTS int aisdkReqMusic(const char* mediaId, int mediaIdLength, void* userData, int len);
/**
 * @brief 请求单个FM的详细信息
 * @param showId
 * @param showIdLength
 * @param showType
 * @param userData 自定义信息，callback时带回。
 * @param len 自定义信息长度
 * @return 0:success other:fail。 错误码定义见AISDK_ERROR_*常量
 * @note 播放FM时，FM的地址可能会有变化，播放前应该用FM的ID请求一次新的url。
 */
AISDK_API_EXPORTS int aisdkReqFM(const char* showId, int showIdLength, int showType, void* userData, int len);
/**
 * @brief 取消全部语义请求
 * @return 0:success other:fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkCancelText2Semantic();
/**
 * @brief 根据外部传入数据，取消特定语义请求
 * @param userData 自定义信息，跟请求的时候传入的值一致
 * @return 0:success other:fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkCancelSemanticByUserData(void* userData);
/**
 * @brief 根据请求类型，取消特定语义请求，请求类型见AISDK_SEMANTIC_REQ_TYPE_*常量
 * @return 0:success other:fail。 错误码定义见AISDK_ERROR_*常量
 */
AISDK_API_EXPORTS int aisdkCancelSemanticByType(int iReqType);
#ifdef __cplusplus
}
#endif

#endif //PACKAGE_TMS_AISDK_AISDK_TEXT_ONLINE_H
