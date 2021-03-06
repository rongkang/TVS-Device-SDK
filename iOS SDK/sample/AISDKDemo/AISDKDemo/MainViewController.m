//
//  MainViewController.m
//  AISDKDemo
//
//  Created by fredyfang(方义) on 2018/4/18.
//  Copyright © 2018年 Zacard Fang. All rights reserved.
//

#import "MainViewController.h"
#import "DeveloperUIVC.h"

#define Storyboard(s) [UIStoryboard storyboardWithName:s bundle:nil]
#define StoryboardVC(s,vc) [Storyboard(s) instantiateViewControllerWithIdentifier:vc]

@interface MainViewController ()
//@property (weak, nonatomic) IBOutlet UIButton *voice2word;
//@property (weak, nonatomic) IBOutlet UIButton *word2semantic;
//@property (weak, nonatomic) IBOutlet UIButton *word2voice;
//@property (weak, nonatomic) IBOutlet UIButton *wakeup;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)btnVoice2WordsClick:(id)sender {
    //DeveloperUIVC *vc = [[DeveloperUIVC alloc] init];
    DeveloperUIVC *vc = StoryboardVC(@"Main", @"DeveloperUIVC");
    vc.serviceType = SERVICE_TYPE_VOICE2WORDS;
    [self presentViewController:vc animated:YES completion:nil];
}

- (IBAction)btnAssistantClick:(id)sender {
    //DeveloperUIVC *vc = [[DeveloperUIVC alloc] init];
    DeveloperUIVC *vc = StoryboardVC(@"Main", @"DeveloperUIVC");
    vc.serviceType = SERVICE_TYPE_VOICE_ASSISTANT;
    [self presentViewController:vc animated:YES completion:nil];
}
- (IBAction)btnWakeupClick:(id)sender {
    DeveloperUIVC *vc = StoryboardVC(@"Main", @"DeveloperUIVC");
    vc.serviceType = SERVICE_TYPE_VOICE_WAKEUP;
    [self presentViewController:vc animated:YES completion:nil];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
