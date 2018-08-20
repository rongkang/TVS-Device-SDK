//
//  TTSAudioPlayer.m
//  Dingdang
//
//  Created by ZACARDFANG on 2017/5/26.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "TTSAudioPlayer.h"
#import <AVFoundation/AVFoundation.h>

static TTSAudioPlayer *instance;

@interface TTSAudioPlayer()<AVAudioPlayerDelegate>
@property (nonatomic,strong) AVAudioPlayer *player;
@property (nonatomic,strong) NSMutableArray *dataArray;
@property (nonatomic,assign) NSInteger position;
@end

@implementation TTSAudioPlayer

+(instancetype)shared {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (instance == nil) {
            instance = [[self alloc]init];
        }
    });
    return instance;
}

-(instancetype) init {
    if (self = [super init]) {
        _dataArray = [NSMutableArray new];
        _position = -1;
    }
    return self;
}

-(void)activeSession {
    AVAudioSession* session = [AVAudioSession sharedInstance];
    NSError* err;
    [session setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:&err];
    if (err) {
        NSLog(@"TTSAudioPlayer setSessionCategory failed:%@", err.localizedDescription);
    }
    [session setActive:YES error:&err];
    if (err) {
        NSLog(@"TTSAudioPlayer setSessionActive failed:%@", err.localizedDescription);
    }
}

-(void)addData:(NSData*)data {
    [_dataArray addObject:data];
    if (_player == nil) {
        [self playNext];
    }
}

-(BOOL)playNext {
    NSInteger count = _dataArray.count;
    if (count > 0 && _position < count - 1) {
        _position++;
        [self activeSession];
        NSError *error = nil;
        _player = [[AVAudioPlayer alloc]initWithData:_dataArray[_position] error:&error];
        _player.delegate = self;
        if (error) {
            NSLog(@"TTSAudioPlayer error = %@", [error localizedDescription]);
        }
        BOOL prepare = [_player prepareToPlay];
        NSLog(@"TTSAudioPlayer prepare to play:%d", prepare);
        BOOL play = [_player play];
        NSLog(@"TTSAudioPlayer start to play:%d", play);
        return YES;
    }
    return NO;
}

-(void)clearAll {
    if (_player != nil) {
        [_player stop];
        _player = nil;
    }
    [_dataArray removeAllObjects];
    _position = -1;
}

#pragma mark AVAudioPlayerDelegate

-(void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    if (![self playNext]) {
        if (_delegate) {
            [_delegate TTSAudioPlayerFinishedAll:flag];
        }
        _player = nil;
    }
}

-(void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError * __nullable)error{
    NSLog(@"TTSAudioPlayer decode error: %@", [error localizedDescription]);
}

@end
