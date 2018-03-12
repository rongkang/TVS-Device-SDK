//
//  SessionViewController.m
//  Dingdang
//
//  Created by ZACARDFANG on 2017/6/12.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "DeveloperUIVC.h"
#import <AISDK/AISDK.h>
#import "AQRecorder.h"
#import "TTSAudioPlayer.h"

#import "SemanticData.h"

#import "TtsFormater.h"

#define IS_NULL(x) (x == nil || [x isKindOfClass:[NSNull class]])

@interface DeveloperUIVC ()<VoiceSessionDelegate, SemanticSessionDelegate, TtsSessionDelegate, AQRecorderDelegate, TTSAudioPlayerDelegate>

@property(nonatomic, strong)SpeechEngine *aisdk;
@property(nonatomic, strong)VoiceSession *voiceSession;
@property(nonatomic, strong)SemanticSession *semanticSession;
@property(nonatomic, strong)TtsSession *ttsSession;

@property(nonatomic, strong)AQRecorder *aqRecorder;
@property(nonatomic, strong)TTSAudioPlayer *ttsAudioPlayer;

@property(nonatomic, strong)NSString *voiceResultText;

@property(nonatomic, strong)NSMutableString * displayLog;
@end

@implementation DeveloperUIVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    //录音
    _aqRecorder = [[AQRecorder alloc] init];
    _aqRecorder.delegate = self;
    
    //播报
    _ttsAudioPlayer = [TTSAudioPlayer shared];
    _ttsAudioPlayer.delegate = self;
    
    [self initRecorderView];
    _displayLog = [[NSMutableString alloc] init];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initSDK {
    _aisdk = [SpeechEngine sharedInstance];
    NSLog(@"sdk version = %@", [_aisdk getSDKVersion]);
    
    //[_aisdk setConfig:K_AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME value:K_AISDK_CONFIG_VALUE_DISABLE];
    
    //voice
    _voiceSession = [[VoiceSession alloc]init];
    [_voiceSession setDelegate:self];
    [_aisdk addSession:_voiceSession];
    //semantic
    _semanticSession = [[SemanticSession alloc]init];
    [_semanticSession setDelegate:self];
    [_aisdk addSession:_semanticSession];
    //tts
    _ttsSession = [[TtsSession alloc]init];
    [_ttsSession setDelegate:self];
    [_aisdk addSession:_ttsSession];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)initRecorderView {
    [_mRecorderView setDelegate:self];
    [_mRecorderView setRecorderStatus:STATUS_NORMAL msg:@"点击开始录音"];
    [_mRecorderView setMsgTextHidden:NO];
}

-(void)semantic {
    if (_voiceResultText != nil && _voiceResultText.length > 0) {
        [_semanticSession text2semantic:_voiceResultText userData:self flags:K_AISDK_FLAG_SEMANTIC_EXIT_CUR_SESSION];
    }
}

#pragma mark RecorderViewDelegate
- (void)onRecorderClick{
    [self initSDK];
    
    
    int status = [_mRecorderView currentStatus];
    
    if (status == STATUS_NORMAL || status == STATUS_EXCEPTION) {
        // 停止播报
        [_ttsAudioPlayer clearAll];
        
        // 启动录音
        [_voiceSession cancelVoice2Text];
        
        [_voiceSession startVoice2text:0];
        
        [self clearToDisplay];
        
        [self appendToDisplay:@"开始录音"];
        
        [self setRecordStatus:STATUS_LOADING msg:@""];
    }
}

- (void)setRecordStatus:(NSInteger)status msg:(NSString *)msg{
    [_mRecorderView setRecorderStatus:status msg:msg];
}

#pragma mark log
- (void)appendToDisplay:(NSString *)content {
    [_displayLog appendString:content];
    [_displayLog appendString:@"\n"];
    [self onDisplayChanged: _displayLog];
}

- (void)clearToDisplay {
    [_displayLog setString:@""];
    [self onDisplayChanged: _displayLog];
}

- (void)onDisplayChanged:(NSString *)content{
    dispatch_async(dispatch_get_main_queue(), ^{
        [_tv_log setText:content];
        
        [_tv_log scrollRangeToVisible:NSMakeRange(_tv_log.text.length - 1, 1)];
    });
    
}

#pragma mark VoiceSessionDelegate
-(void)onOnlineVocieCallback:(NSInteger)cmd code:(NSInteger)code data:(NSString *)data userData:(id)userData{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (cmd == K_AISDK_CMD_ONLINE_RECO_START){
            // 在线识别开始，接受录音数据
            [self appendToDisplay:@"在线识别开始"];
            dispatch_async(dispatch_get_main_queue(), ^{
                [_aqRecorder start];
            });
            
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_SPEECH_START){
            // 在线语音VAD检测到开始
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_SPEECH_END){
            // 在线语音vad检测完成，可以停止输入录音数据
            [self appendToDisplay:@"识别完成，可以停止输入录音数据"];
            dispatch_async(dispatch_get_main_queue(), ^{
                [_aqRecorder stop];
                [self setRecordStatus:STATUS_NORMAL msg:_voiceResultText];
            });
            
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_RESULT){
            // 返回在线识别结果
            NSLog(@"语音识别完成：%@", data);
//            [self appendToDisplay:@"识别完成，可以停止输入录音数据"];
            dispatch_async(dispatch_get_main_queue(), ^{
                [_aqRecorder stop];
                [self setRecordStatus:STATUS_NORMAL msg:_voiceResultText];
            });
            
            _voiceResultText = data;
            [_mRecorderView setMsgText:_voiceResultText];
            
            [self appendToDisplay:[NSString stringWithFormat:@"识别结果：%@", data]];
            [self semantic];
            
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_INTERMEDIATE_RESULT){
            // 上报在线识别的中间结果
            NSLog(@"语音识别中：%@", data);
            _voiceResultText = data;
            [_mRecorderView setMsgText:_voiceResultText];
            
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_DATA_VOLUME){
            // 上报输入音频数据的音量值
        } else if (cmd == K_AISDK_CMD_ONLINE_RECO_CANCELED){
            // 已取消在线识别
            [self appendToDisplay:@"已取消在线识别"];
            dispatch_async(dispatch_get_main_queue(), ^{
                [_aqRecorder stop];
                [self setRecordStatus:STATUS_NORMAL msg:_voiceResultText];
            });
        }
        
    });
}

-(void)onOnlineVocieError:(NSInteger)cmd code:(NSInteger)code message:(NSString *)message userData:(id)userData{
    dispatch_async(dispatch_get_main_queue(), ^{
        [_aqRecorder stop];
        [self appendToDisplay:[NSString stringWithFormat:@"onOnlineVocieError cmd =%ld, message=%@", code, message]];
        [self setRecordStatus:STATUS_NORMAL msg:_voiceResultText];
    });
}

#pragma mark SemanticSessionDelegate
-(void)onOnlineSemanticCallback:(NSInteger)cmd code:(NSInteger)code data:(NSString *)data userData:(id)userData {
    // 语义回调，解析业务场景
    [self appendToDisplay:[NSString stringWithFormat:@"语义回调结果：%@", data]];
    if (K_AISDK_CMD_SEMANTIC_RESULT == cmd) {
        SemanticData *sd = [SemanticData valueFromJson:data];
        // 处理业务，此处直接演示tts功能
        if (sd.speakText && ![sd.speakText isEqualToString:@""]) {
            [_ttsSession text2Speech:sd.speakText userData:self];
        } else {
            [_ttsSession text2Speech:sd.tipsText userData:self];
        }
        
    }
}

- (void)onOnlineSemanticError:(NSInteger)cmd code:(NSInteger)code message:(NSString *)message userData:(id)userData {
    [self appendToDisplay:[NSString stringWithFormat:@"语义回调错误：%@", message]];
}

#pragma mark TtsSessionDelegate
-(void)onOnlineTtsCallback:(NSInteger)cmd code:(NSInteger)code pcm:(NSData *)pcm userData:(id)userData{
    if (pcm) {
        // 转换pcm格式为wav格式播放，也可调用系统AudioQueue播放pcm
        [_ttsAudioPlayer addData:[TtsFormater translatePcm2Wav:pcm]];
    }
}

-(void)onOnlineTtsError:(NSInteger)cmd code:(NSInteger)code message:(NSString *)message userData:(id)userData{
    //NSLog(@"tts error cmd:%ld data:%@", cmd, data);
}

#pragma mark AQRecorderDelegate
-(void)onInputVoice:(NSData *)data{
    [_voiceSession inputVoice2TextAudioData:data];
}

#pragma mark TTSAudioPlayerDelegate
- (void)TTSAudioPlayerFinishedAll:(BOOL)success {
    // TODO 恢复其他播放
}

@end
