//
//  NumberInputView.h
//  LFDistributionApp
//
//  Created by 司小波 on 16/3/25.
//  Copyright © 2016年 LetvFinancial. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PassGuardCtrl.h"

@protocol NumberInputDelegate <NSObject>

- (void)tapAction;

@end

@interface NumberInputView : UIView
{
    PassGuardTextField *m_textfield;
}
@property (nonatomic, copy) void (^borderBlock)(BOOL max,PassGuardTextField *pgTextField);  //边界调用
@property (nonatomic, copy) void (^tapBlock)(NumberInputView *input);
@property (nonatomic, assign) BOOL max; //是否最大
@property (nonatomic, assign) long lenth;
@property (nonatomic, copy, readonly) NSString *numberStr;
@property (nonatomic, copy, readonly) NSString *encStr;//输出密文
@property (nonatomic, copy) PassGuardTextField *m_textfield;

@property (nonatomic, assign)id<NumberInputDelegate>delegate;

/*!
 *  @brief 初始化接口
 *
 *  @param count     输入长度
 *  @param topoff    topoff
 *  @param m_license 密码控件签名标识
 *
 *  @return NumberInputView
 */
- (instancetype)initWithCount:(NSInteger)count topOff:(CGFloat)topoff pgM_license:(NSString *)m_license;

- (void)inPutIndex;

- (void)inPutIndexWithNum:(NSInteger)num;

- (void)clearIndex;
//调起键盘
- (void)tapAction:(NumberInputView *)input;
//重置
- (void)reset;




@end
