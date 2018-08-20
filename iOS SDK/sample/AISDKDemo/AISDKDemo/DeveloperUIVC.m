//
//  SessionViewController.m
//  Dingdang
//
//  Created by ZACARDFANG on 2017/6/12.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "DeveloperUIVC.h"
#import "VoiceAssistant.h"
#import <AVFoundation/AVFoundation.h>

#define IS_NULL(x) (x == nil || [x isKindOfClass:[NSNull class]])

@interface DeveloperUIVC ()<VoiceSessionDelegate, SemanticSessionDelegate, TtsSessionDelegate, AQRecorderDelegate, TTSAudioPlayerDelegate, SpeechWakeupDelegate>


@property(nonatomic, assign)BOOL hadWakeup;
@property(nonatomic, assign)BOOL wakeupFailed;
@property(nonatomic, strong)AQRecorder *aqRecorder;
@property(nonatomic, strong)TTSAudioPlayer *ttsAudioPlayer;
@property(nonatomic, strong) VoiceAssistant *voiceAssitant;

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
    
    [self initData];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)initData {
   
    _voiceAssitant = [VoiceAssistant sharedInstance];
    //voice
    //[_voiceSession setDelegate:self];
    [_voiceAssitant.voiceSession setDelegate:self];
    
    //semantic
    //[_semanticSession setDelegate:self];
    [_voiceAssitant.semanticSession setDelegate:self];
    
    //tts
    //[_ttsSession setDelegate:self];
    [_voiceAssitant.ttsSession setDelegate:self];
    
    //wakeup
    //[_wakeup setDelegate:self];
    [_voiceAssitant.wakeup setDelegate:self];
    
    NSString *modelPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"keywords_model.bundle"];
    
    //NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    //NSString *documentsDirectory = [paths objectAtIndex:0];
    
    //创建NSFileManager和NSDirectoryEnumerator来枚举Documents文件夹下的文件。
    /*
     NSFileManager *fileManager = [NSFileManager defaultManager];
     if ([fileManager fileExistsAtPath:modelPath]) {
     
     } else {
     NSLog(@"error ........");
     }
     NSDirectoryEnumerator *dirEnum = [fileManager enumeratorAtPath:modelPath];
     
     //最后显示Documents文件夹下所有文件。
     
     NSString *filepath;
     while ((filepath = [dirEnum nextObject]) != nil) {
     NSLog(@"filepath:%@", filepath);
     }
     */
    int ret = 0;
    if (_serviceType == SERVICE_TYPE_VOICE_WAKEUP) {
        ret = [_voiceAssitant.wakeup initOfflineWakupWithPath:modelPath.UTF8String];
        NSLog(@"initSDK initOfflineWakupWithPath ret=%d, path=%@.", ret, modelPath);
        if (ret > 0) {
            _wakeupFailed = YES;
            [self showAlertDialog:@"initOfflineWakupWithPath" withErrNo:ret];
        }

        ret = [_voiceAssitant.wakeup startOfflineWakupWithData:nil withLength:0 withFlags:0];
        NSLog(@"startOfflineWakupWithData ret=%d.", ret);
        if (ret > 0) {
            _wakeupFailed = YES;
            [self showAlertDialog:@"startOfflineWakupWithData" withErrNo:ret];
        }
    }
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
    if (_serviceType == SERVICE_TYPE_VOICE2WORDS) {
        [self appendToDisplay:[NSString stringWithFormat:@"语音转文字：%@", _voiceResultText]];
        return;
    }
    if (_serviceType == SERVICE_TYPE_VOICE_WAKEUP) {
        [self appendToDisplay:[NSString stringWithFormat:@"语音唤醒：failed"]];
        return;
    }
    if (_voiceResultText != nil && _voiceResultText.length > 0) {
        [_voiceAssitant.semanticSession text2semantic:_voiceResultText userData:self flags:0];// flags:K_AISDK_FLAG_SEMANTIC_EXIT_CUR_SESSION];
    }
}

#pragma mark RecorderViewDelegate
- (void)onRecorderClick{

    [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if (granted) {
            int status = [_mRecorderView currentStatus];

            if (status == STATUS_NORMAL || status == STATUS_EXCEPTION) {
            // 停止播报
            [_ttsAudioPlayer clearAll];

            // 如果没有唤醒，就开始唤醒启动录音
            //        if (!_hadWakeup && !_wakeupFailed) {
            //
            //            dispatch_async(dispatch_get_main_queue(), ^{
            //                [_aqRecorder start];
            //            });
            //        } else {
                [_voiceAssitant.voiceSession cancelVoice2Text];
                [_voiceAssitant.voiceSession startVoice2text:0];
            //}


            [self clearToDisplay];

            [self appendToDisplay:@"开始录音"];
            [_aqRecorder stop];
            [self setRecordStatus:STATUS_LOADING msg:@""];
            }
        } else {
            [self showAlertDialog:@"未开启录音权限" withErrNo:-1];
        }
    });

    NSLog(@"onRecorderClick end");
    }];
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
    NSLog(@"onOnlineVocieCallback cmd=%ld.", cmd);
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
            NSLog(@"RECO_DATA_VOLUME value：%f", [data floatValue]);
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
    NSLog(@"onOnlineSemanticCallback cmd = %ld", cmd);
    // 语义回调，解析业务场景
    [self appendToDisplay:[NSString stringWithFormat:@"语义回调结果：%@", data]];
    if (K_AISDK_CMD_SEMANTIC_RESULT == cmd) {
        SemanticData *sd = [SemanticData valueFromJson:data];
        // 处理业务，此处直接演示tts功能
        if (sd.speakText && ![sd.speakText isEqualToString:@""]) {
            [_voiceAssitant.ttsSession text2Speech:sd.speakText userData:self];
        } else {
            [_voiceAssitant.ttsSession text2Speech:sd.tipsText userData:self];
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
//    if (!_hadWakeup && !_wakeupFailed) {
    //不需要主动往唤醒模块传数据，底层识别模块会往唤醒模块传数据；
//       int ret = [_wakeup inputOfflineWakeupAudioData:data.bytes withLength:data.length];
//       NSLog(@"onInputVoice inputOfflineWakeupAudioData ret=%d.", ret);
//        if (ret > 0) {
//            _wakeupFailed = YES;
//            [self showAlertDialog:@"inputOfflineWakeupAudioData" withErrNo:ret];
//        }
//
//    } else {
        [_voiceAssitant.voiceSession inputVoice2TextAudioData:data];
    //}
    
}

#pragma mark TTSAudioPlayerDelegate
- (void)TTSAudioPlayerFinishedAll:(BOOL)success {
    // TODO 恢复其他播放
}

- (void)showAlertDialog:(NSString *)title withErrNo:(int)ret {
    NSString *errMsg = [NSString stringWithFormat:@"错误码：%d.", ret];
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:errMsg preferredStyle:UIAlertControllerStyleAlert];
    [alertController addAction:[UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleDefault handler:nil]];
    //[alertController addAction:[UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleDefault handler:nil]];
    //[alertController show:YES];
    [self presentViewController:alertController animated:YES completion:nil];
}

#pragma mark SpeechWakeupDelegate

-(void)onSpeechWakeupCallback:(NSInteger)cmd code:(NSInteger)code data:(NSString *)data userData:(id)userData {
    NSLog(@"onSpeechWakeupCallback cmd = %ld", cmd);
    if (cmd == K_AISDK_CMD_WAKEUP_RECO_RESULT) {
        _hadWakeup = YES;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [_aqRecorder stop];
            //[self showAlertDialog:@"唤醒成功" withErrNo:0];
            [self setRecordStatus:STATUS_NORMAL msg:@"叮当叮当"]; //_voiceResultText
            [self appendToDisplay:@"唤醒成功"];
        });

    }
}

-(void)onSpeechWakeupError:(NSInteger)cmd code:(NSInteger)code message:(NSString *)message userData:(id)userData {
    if (cmd == K_AISDK_CMD_WAKEUP_RECO_ERROR) {

        dispatch_async(dispatch_get_main_queue(), ^{
            [_aqRecorder stop];
            //[self showAlertDialog:@"唤醒失败" withErrNo:K_AISDK_CMD_WAKEUP_RECO_ERROR];
            [self setRecordStatus:STATUS_NORMAL msg:@"唤醒中。。。"];
            [self appendToDisplay:@"唤醒失败"];
        });
        
    }
}
- (IBAction)btnBackOnClick:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}
@end
