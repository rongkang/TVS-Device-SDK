//
//  SessionViewController.h
//  Dingdang
//
//  Created by ZACARDFANG on 2017/6/12.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RecorderView.h"

@interface DeveloperUIVC : UIViewController<RecorderViewDelegate>

@property (strong, nonatomic) IBOutlet RecorderView *mRecorderView;
@property (strong, nonatomic) IBOutlet UITextView *tv_log;

@end
