//
//  TtsFormater.h
//  CodooDemo
//
//  Created by Zacard Fang on 2017/10/25.
//  Copyright © 2017年 Zacard Fang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface TtsFormater : NSObject

+ (NSData *)translatePcm2Wav:(NSData *)pcmData;
@end
