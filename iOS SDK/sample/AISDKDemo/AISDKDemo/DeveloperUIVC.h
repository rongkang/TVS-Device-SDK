//
//  SessionViewController.h
//  Dingdang
//
//  Created by ZACARDFANG on 2017/6/12.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RecorderView.h"

enum {SERVICE_TYPE_VOICE2WORDS = 0x01, SERVICE_TYPE_VOICE_WAKEUP = 0x02, SERVICE_TYPE_VOICE_ASSISTANT = 0x03};


@interface DeveloperUIVC : UIViewController<RecorderViewDelegate>

@property (strong, nonatomic) IBOutlet RecorderView *mRecorderView;
@property (strong, nonatomic) IBOutlet UITextView *tv_log;

@property (weak, nonatomic) IBOutlet UILabel *funcTitle;

@property (nonatomic,assign) int serviceType; //1---voice2words,

@end
