//
//  NumberInputView.m
//  LFDistributionApp
//
//  Created by 司小波 on 16/3/25.
//  Copyright © 2016年 LetvFinancial. All rights reserved.
//

#import "NumberInputView.h"

@interface blackPoint : UIView
{
    
}
@end

@implementation blackPoint


- (void)drawRect:(CGRect)rect {
    UIBezierPath *path = [UIBezierPath bezierPathWithOvalInRect:self.bounds];
    [[UIColor blackColor] setFill];
    [path fill];
    [path addClip];
}

@end

@interface NumberInputView()<instertWebviewTextDelegate>
{
    
}

@end
@implementation NumberInputView {
    NSInteger _count;
    NSInteger _index;
}

- (instancetype)initWithCount:(NSInteger)count topOff:(CGFloat)topoff pgM_license:(NSString *)m_license{
    CGFloat off = 16;
    CGFloat itemWidth = ([[UIScreen mainScreen] bounds].size.width - off * 2)/count;
    CGFloat itemHeight = 44.f;
    if (self = [super initWithFrame:CGRectMake(off, topoff, count * itemWidth, itemHeight)]) {
        _count = count;
        _index = 0;
        _lenth = 0;
        self.backgroundColor = [UIColor colorWithRed:189.f/255 green:189.f/255 blue:189.f/255 alpha:1];
        CGFloat sp = 0.5;
        CGFloat space = (itemWidth * count - sp * (count + 1)) / count;
        for (NSInteger i = 0; i < count; i ++) {
            UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(i * (space + sp) + sp, sp, space, itemHeight - 2 * sp)];
            label.textAlignment = NSTextAlignmentCenter;
            label.backgroundColor = [UIColor whiteColor];
            label.tag = i + 1;
            [self addSubview:label];
            blackPoint *point = [[blackPoint alloc] initWithFrame:CGRectMake(0, 0, 15, 15)];
            point.center = label.center;
            point.tag = i + 100;
            point.hidden = YES;
            point.backgroundColor = [UIColor clearColor];
            [self addSubview:point];
        }
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapAction:)];
        [self addGestureRecognizer:tap];
        self.userInteractionEnabled = YES;
        
        /**
            加载密码控件
         */
        m_textfield = [[PassGuardTextField alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
        [m_textfield setM_license:m_license];
        m_textfield.keyboardType = UIKeyboardTypeNumberPad;
        [m_textfield setM_iMaxLen:(int)count];//设置输入最大长度
        [m_textfield setWebdelegate:self];//设置委托回调
        m_textfield.m_ikeyordertype = KEY_IPAD_KEY_PRESS;
        [self addSubview:m_textfield];        
    }
    return self;
}

/*!
 *  @brief 密码键盘输入字符回调接口
 */
-(void)instertWText{
    NSLog(@"本次长度%ld",[m_textfield getOutput3]);
    NSLog(@"上次长度%ld",(long)_lenth);
    NSLog(@"%ld",(long)_index);
    if(_index == 7 && [m_textfield getOutput3] == 5){
        [self reset];
        return;
    }

    if([m_textfield getOutput3] > _count){
        return;
    }else{
       [self inPutIndexWithNum:0 ];
    }
}

- (void)tapAction:(NumberInputView *)input {
   [m_textfield becomeFirstResponder];
    
    if (_tapBlock) {
        _tapBlock(self);
    }
}

- (void)inPutIndex {
    [self inPutIndexWithNum:-1];
}

- (void)inPutIndexWithNum:(NSInteger)num {
//    if (_index > _count - 1) {
//        return;
//    }
    if ([m_textfield getOutput3] < _lenth){
        blackPoint *view = (blackPoint *)[self viewWithTag:_index - 100];
        if ([view isKindOfClass:[blackPoint class]] && view.hidden) {
            view.hidden = YES;
        }
    }else{
        blackPoint *view = (blackPoint *)[self viewWithTag:_index + 100];
        if ([view isKindOfClass:[blackPoint class]] && view.hidden) {
            view.hidden = NO;
        }
    }
    
    blackPoint *view = (blackPoint *)[self viewWithTag:_index + 100];

        if ([m_textfield getOutput3] <= _lenth){
                [self viewWithTag:100 + _lenth -1].hidden = YES;
            _index = [m_textfield getOutput3];
        }else{
            view.hidden = NO;
            _index++;
        }
//    }
//    _index++;
    if (num != - 1) {
        if (!_numberStr) {
            _numberStr = @"";
        }
        _numberStr = [m_textfield text];
    }
    if (_index == _count) {
        _max = YES;
        if (_borderBlock) {
            //收起键盘
            [m_textfield resignFirstResponder];
        
            _borderBlock(YES,m_textfield);
        }
    }
    _lenth = [m_textfield getOutput3];
    _index = [m_textfield getOutput3];
}

//重置
- (void)reset {
    [m_textfield Clean];
    [m_textfield resignFirstResponder];
    _index = 0;
    _lenth = 0;
    for (NSInteger i = 0; i < _count; i ++) {
        [self viewWithTag:100 + i].hidden = YES;
    }
}



@end
