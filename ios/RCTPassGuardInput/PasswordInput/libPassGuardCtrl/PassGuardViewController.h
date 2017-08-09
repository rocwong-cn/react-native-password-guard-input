//
//  PassGuardViewController.h
//  webinvokepassgaurd
//
//  Created by apple on 13-11-8.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PassGuardCtrl.h"
/**
 *  分别对应于所弹出文本框的“确定”、“取消”和键盘右下角的“收起”键盘按钮。通过实现这三个委托接口可以实现获取m_tf密文等操作。
 */
@protocol BarDelegate<NSObject>
@optional
- (void) BDoneFun:   (id)sender;
- (void) BCancelFun: (id)sender;
- (void) BHideFun:   (id)sender;
@end

/*!
 *  @brief 键盘收起事件 回调
 */
@protocol WebKeyBoardAlertDelegate <NSObject>
-(void)wkbad;
@end

@interface PassGuardViewController : UIViewController<DoneDelegate, UIGestureRecognizerDelegate>
{
    id <WebKeyBoardAlertDelegate> wkbadDelegate;
}
@property (assign,nonatomic) id<WebKeyBoardAlertDelegate> wkbadDelegate;//web端键盘收起时回调
@property (nonatomic) bool   m_isDispearWithTouchOutside;//设置为true时，当点击文本框和键盘以外区域时，将收起文本框和键盘；
@property (nonatomic,retain) PassGuardTextField *m_tf;//iOS密码控件对象
@property (nonatomic,assign) id <BarDelegate> delegate;
@property (nonatomic) bool   m_bshowtoolbar;//默认 关闭toolBar

////////////// 密码键盘  BarDelegate JS 回调function name 供 PGTigerBrowserWebView 使用//////////////
@property (nonatomic, retain) NSString *jsWillShowKeyBoardFunName;//键盘弹起事件JS方法名
@property (nonatomic, retain) NSString *jsBDoneFunName;//确定JS方法名
@property (nonatomic, retain) NSString *jsBCancelFunName;//取消JS方法名
@property (nonatomic, retain) NSString *jsBHideFunName;//收起JS方法名


- (void) show;   //弹出iOS密码控件文本框及其键盘
- (bool) isShow;
- (void) dismiss;//收起iOS密码控件文本框及其键盘。

@end
