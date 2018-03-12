//
//  TTSAudioPlayer.h
//  Dingdang
//
//  Created by ZACARDFANG on 2017/5/26.
//  Copyright © 2017年 tencent. All rights reserved.
//

/**
 语音播报-播放器控制，每个TTSAudioPlayer保持一个Queue
 */
#import <Foundation/Foundation.h>

@protocol TTSAudioPlayerDelegate <NSObject>

- (void)TTSAudioPlayerFinishedAll:(BOOL)success;

@end

@interface TTSAudioPlayer:NSObject

@property(nonatomic,weak) id<TTSAudioPlayerDelegate> delegate;

+(instancetype)shared;

-(void)addData:(NSData*)data;

-(void)clearAll;

@end
