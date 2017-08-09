//
//  RCTPassGuardInput.m
//  RCTPassGuardInput
//
//  Created by RocWang on 2017/8/7.
//  Copyright © 2017年 RocWang. All rights reserved.
//

#import "RCTPassGuardInput.h"
#import "RCTBridgeModule.h"
#import "NumberInputView.h"

@interface RCTPassGuardInput () <NumberInputDelegate>
{
    NumberInputView * _numberInputView;
}

@end

@implementation RCTPassGuardInput

RCT_EXPORT_MODULE()

RCT_EXPORT_VIEW_PROPERTY(onTap,RCTBubblingEventBlock)

- (void)tapAction {
    RCTLog(@">>>>>  tapAction  >>>>>");
}

- (UIView *)view
{
    RCTLog(@">>>>>  aaaaaaaaaaaaaaaaa  >>>>>");
    return [[NumberInputView alloc] initWithCount:6 topOff:100 pgM_license:@"VVlvOEExbkwzNk5hcDFmNHAzMU5QWktYWTlsTHloT0RaQldXNFRYa1lDVUp1TzFTN1NVVzBOcTZRRVp0MDFIZ1FnaXYwd1hCRC9xNW05ZXY4Mml3cE81MXdMZDUzSlZUVHlYRFR3cXYzcFNZV3JvRUtiR3ZZaEJmc0pIQW4valJsdmtwOTAzRmloNU15NERRMnp1UU1JbXhwdXdsNXZJSEprU2VzWmkrY2JFPXsiaWQiOjAsInR5cGUiOiJ0ZXN0IiwicGxhdGZvcm0iOjEsIm5vdGJlZm9yZSI6IjIwMTYwNjI5Iiwibm90YWZ0ZXIiOiIyMDE2MDkyOSJ9"];
}

@end
