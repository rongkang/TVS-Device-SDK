//
//  VoiceAssistant.m
//  AISDKDemo
//
//  Created by fredyfang(方义) on 2018/4/19.
//  Copyright © 2018年 Zacard Fang. All rights reserved.
//

#import "VoiceAssistant.h"

@interface VoiceAssistant()


@end

@implementation VoiceAssistant

+ (id)sharedInstance
{
    static VoiceAssistant *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init{
    if (self = [super init]){
        [self initSDK];
    }
    return self;
}

- (void)initSDK {
    _aisdk = [SpeechEngine sharedInstance];
    
    NSLog(@"sdk version = %@", [_aisdk getSDKVersion]);
    
    [_aisdk setConfig:K_AISDK_CONFIG_VOICE_ONLINE_ENABLE_CALCULATE_VOLUME value:K_AISDK_CONFIG_VALUE_ENABLE];
    
    //voice
    _voiceSession = [[VoiceSession alloc]init];
    //[_voiceSession setDelegate:self];
    [_aisdk addSession:_voiceSession];
    //semantic
    _semanticSession = [[SemanticSession alloc]init];
    //[_semanticSession setDelegate:self];
    [_aisdk addSession:_semanticSession];
    //tts
    _ttsSession = [[TtsSession alloc]init];
    //[_ttsSession setDelegate:self];
    [_aisdk addSession:_ttsSession];
    
    _wakeup = [[SpeechWakeup alloc] init];
    //[_wakeup setDelegate:self];
    [_aisdk addSession:_wakeup];
    

}


@end
