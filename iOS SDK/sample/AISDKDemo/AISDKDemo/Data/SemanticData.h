//
//  SemanticData.h
//  DobbySwift
//
//  Created by Rinc Liu on 27/9/2017.
//  Copyright © 2017 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, Slot_Type) {
    SLOT_DATETIME,
    SLOT_ENTITY,
    SLOT_LOCATION,
    SLOT_NUMBER,
};

@interface SemanticData : NSObject

@property (nonatomic,copy) NSDictionary* semanticDict, *dataDict;
@property (nonatomic,copy) NSArray *templateArray;
@property (nonatomic,copy) NSString *query, *scene, *action;
@property (nonatomic,copy) NSString *textContent, *speakText, *tipsText;
@property (nonatomic,assign) NSInteger contentType;

+ (SemanticData*)valueFromJson:(NSString*)json;

+ (NSString *)getSlotValue:(NSDictionary *)aSlot;

- (NSDictionary *)getSlotByName:(NSString *)slotName;
@end
