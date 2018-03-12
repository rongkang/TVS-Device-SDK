//
//  SemanticData.m
//  DobbySwift
//
//  Created by Rinc Liu on 27/9/2017.
//  Copyright © 2017 tencent. All rights reserved.
//

#import "SemanticData.h"

@implementation SemanticData

+ (SemanticData*)valueFromJson:(NSString*)json{
    if (json != nil) {
        NSError *jsonError;
        NSData *objectData = [json dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:objectData options:NSJSONReadingMutableContainers error:&jsonError];
        if (jsonError == nil && jsonDict != nil) {
            SemanticData *semanticData = [SemanticData new];
            semanticData.dataDict = jsonDict[@"data"];
            semanticData.semanticDict = jsonDict[@"semantic"];
            semanticData.templateArray = jsonDict[@"template"];
            semanticData.query = jsonDict[@"query"];
            semanticData.scene = jsonDict[@"service"];
            semanticData.action = jsonDict[@"operation"];
            semanticData.tipsText = jsonDict[@"tips"];
            semanticData.textContent = jsonDict[@"answer"];
            semanticData.speakText = jsonDict[@"noscreen_answer"];
            if (semanticData.speakText == nil || semanticData.speakText.length == 0) {
                semanticData.speakText = semanticData.textContent;
            }
            semanticData.contentType = [jsonDict[@"content_type"] integerValue];
            return semanticData;
        }
    }
    return nil;
}

+ (NSString *)getSlotValue:(NSDictionary *)aSlot{
    if (!aSlot) {
        return nil;
    }
    
    NSInteger slotType = [[aSlot objectForKey:@"slot_struct"] integerValue];
    if (SLOT_ENTITY == slotType) {
        NSArray *values = [aSlot objectForKey:@"values"];
        if (values && values.count > 0) {
            // 优先取original_text
            NSString *value = [values[0] objectForKey:@"original_text"];
            if(!value) {
                value = [values[0] objectForKey:@"text"];
            }
            return value;
        }
    }
    return nil;
}

/**
 * 获取slot对象
 */
- (NSDictionary *)getSlotByName:(NSString *)slotName{
    if (!slotName){
        return nil;
    }
    
    NSArray *slots = [_semanticDict objectForKey:@"slots"];
    if (!slots){
        return nil;
    }
    
    for (NSDictionary *slot in slots) {
        if (slot) {
            if ([slotName isEqualToString:[slot objectForKey:@"name"]]){
                return slot;
            }
        }
    }
    return nil;
}

@end
