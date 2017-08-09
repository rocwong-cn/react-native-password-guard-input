/*!
 @header PassGuardCtrl.h
 
 @brief iOS密码安全控件
 
 @author tengzhixiang
 @copyright  microdone 16-03-17 15:03:02
 @version    16.03.17
 */

#import <UIKit/UIKit.h>

/*!
 @definedblock 宏定义
 @define KEY_NONE_CHAOS          表示不乱序（默认）
 @define KEY_CHAOS_SWITCH_VIEW   表示在初始化键盘和切换键盘的时候乱序
 @define KEY_CHAOS_PRESS_KEY     表示按下非功能键后乱序
 @define KEY_NONE_KEY_PRESS      按键动画，表示无效果（默认）
 @define KEY_IPAD_KEY_PRESS      按键动画，表示使用ipad设备才有效果
 @define KEY_IPHONE_KEY_PRESS    按键动画，表示使用iphone设备才有效果
 */

#define KEY_NONE_CHAOS          0x00
#define KEY_CHAOS_SWITCH_VIEW   0x01
#define KEY_CHAOS_PRESS_KEY     0x02
#define SHOW_ANIMATTION         0x04
#define KEY_NONE_KEY_PRESS      KEY_NONE_CHAOS
#define KEY_IPAD_KEY_PRESS      KEY_CHAOS_SWITCH_VIEW
#define KEY_IPHONE_KEY_PRESS    KEY_CHAOS_PRESS_KEY
/*!
 @protocol instertWebviewTextDelegate
 @discussion web回调代理
 */
@protocol instertWebviewTextDelegate <NSObject>
-(void)instertWText;
@end
/*!
 @protocol OnCharDelegate
 @discussion 移动端浏览器回调代理
 */
@protocol OnCharDelegate<NSObject>
-(void)OnChar:(id)sender Char:(NSString*)inchar;
@end
/*!
 @protocol DoneDelegate
 @discussion Done回调代理
 */
@protocol DoneDelegate<NSObject>
-(void)DoneFun:(id)sender;
@end

@interface PassGuardTextField : UITextField < UITextInput>
{
@public
    NSString *m_strInput1;
    NSString *m_strInput2;
    NSString *m_strInput3;
    NSString *m_strInputX;
    NSString *m_strInputY;
    NSString *m_strInputR1;
    NSString *m_strInputR2;
    
    NSString *html5Placehoder;
    BOOL m_mode;
    BOOL m_hasstatus;
    int  m_iMaxLen;
    BOOL m_bMaxLenTips;
    
    int  m_enterpriseID;
    id <instertWebviewTextDelegate> webdelegate;
}

/*!
 *  @brief  企业标识
 *  0 标准1代
 *  1 标准2代 （默认）
 *  更多联系 微通开发人员
 */
@property (nonatomic) int  m_enterpriseID;

/*!
 *  @brief  是否允许复制粘贴
 */
@property (nonatomic) BOOL m_isEnablePaste;
/*!
 *  @brief  密文是否延迟显示
 */
@property (nonatomic) BOOL m_isDotDelay;
/*!
 *  @brief  输入框明密文模式
 */
@property (nonatomic) BOOL m_mode;
/*!
 *  @brief  设置键盘的按键状态，true表示有按键状态，false表示无按键状态。（默认为有状态）
 */
@property (nonatomic) BOOL m_hasstatus;
/*!
 *  @brief  设置随机字符串，用来产生AES密钥（需要与解密端字符串同步）
 */
@property (nonatomic, retain) NSString *m_strInput1;
/*!
 *  @brief  设置RSA加密公钥。
 */
@property (nonatomic, retain) NSString *m_strInput2;
/*!
 *  @brief  保留属性，一般用来设置RSA算法填充。
 */
@property (nonatomic, retain) NSString *m_strInput3;
/*!
 *  @brief  国密sm2  X公钥
 */
@property (nonatomic, retain) NSString *m_strInputX;
/*!
 *  @brief  国密sm2  Y公钥
 */
@property (nonatomic, retain) NSString *m_strInputY;
/*!
 *  @brief  正则规则,输入过程中字符类型限制
 */
@property (nonatomic, retain) NSString *m_strInputR1;
/*!
 *  @brief  设置正则表达式，输入完毕后字符类型判断条件,isMatch()函数使用
 */
@property (nonatomic, retain) NSString *m_strInputR2;
/*!
 *  @brief  控件正常运行所需的license，分为生产版和测试版，此处为appName＋boudleId
 */
@property (nonatomic, retain) NSString *m_license;

/*!
 *  @brief  设置密文最大可输入长度
 */
@property (nonatomic) int  m_iMaxLen;
/*!
 *  @brief  输入超过最大字符弹框提示
 */
@property (nonatomic) BOOL m_bMaxLenTips;

/*!
 *    @brief  控制键盘乱序功能：
 //KEY_NONE_CHAOS，表示不乱序（默认）；
 //KEY_CHAOS_SWITCH_VIEW，表示在初始化键盘和切换键盘的时候乱序；
 //KEY_CHAOS_PRESS_KEY，表示按下非功能键后乱序；
 //可组合使用。
 */
@property (nonatomic) int m_ikeyordertype;
/*!
 *    @brief  控制按下键后的效果（该键放大并上浮，松开后恢复原状）：
 //KEY_NONE_KEY_PRESS，表示无效果（默认）；
 //KEY_IPAD_KEY_PRESS，表示使用ipad设备才有效果
 //KEY_IPHONE_KEY_PRESS，表示使用iphone设备才有效果；
 //可组合使用
 */
@property (nonatomic) int m_ikeypresstype;

/*!
 @var webdelegate
 @abstract 委托
 @discussion web端/dutrust，输入框返回字符*方法，用于网页js回调
 */
@property (assign,nonatomic) id<instertWebviewTextDelegate> webdelegate;
/*!
 *  @brief  dutrust专用接口
 */
@property(nonatomic,assign)  id <OnCharDelegate> _onchardelegate;
/*!
 *  @brief  键盘推出时候的事件委托实现
 */

@property (assign,nonatomic) id<DoneDelegate> _DoneDelegate;
/*!
 *  @brief  设置该属性为当前应用实例对象即可，即[UIApplication sharedApplication]。
 */
@property (retain,nonatomic) id m_uiapp;
/*!
 *  @brief  html5端使用。
 */
@property (nonatomic,retain) NSString *html5Placehoder;

/**
 *  静态初始化接口，首先调用以对控件资源进行初始化。
 */
+ (void)initPassGuardCtrl;

/*!
 *  @brief  定义文本框内内容的显示方式 明文-密文
 *
 *  @param bmode  为true时按明文显示，false时按密码（星号）显示
 *
 *  @return 返回控件对象
 */
- (id)initWithMode:(BOOL)bmode;

/*!
 *  @brief  获取AES加密密文
 *
 *  @return 返回AES加密密文
 */
- (NSString *)      getOutput1;
/*!
 *  @brief  获取MD5加密密文
 *
 *  @return 返回md5加密密文
 */
- (NSString *)      getOutput2;
/*!
 *  @brief  获取输入密文长度
 *
 *  @return 返回密文长度
 */
- (NSInteger)       getOutput3;
/*!
 *  @brief  获取AES(RSA)加密密文
 *
 *  @param certype certype 分别为0、1、2；
 0：pem p1格式 参考:
 
 "MIIBCgKCAQEAvKg1r8u0Vh+y5ashicuNoPNgBeUTmO1y6GWBsgC3qzqtew3NqGPsNy3e3mWDp8XssMxD9TgPkD9vm6qWDSLi8wPmLlxXyAM0i3XyKPEN8IRjwOEsyR6HqcQvv9/c56qRTZ33idrDwuPokafkXusidw64QfK5JlF+hQRykFH3F2vSt9L5P7Ml2Vrrp9OHVFnLvdU9toVb6bK9LR0HTKYI7VwPJhw+F/flAtsJiQ2LzESnhopr7kob71fqdPtpXkCdRIQmNb+zjZ+47nupKqWjqKLhNLvNicMXSH9TwUcCxeUPgjhAkwRdcQaaRCL0s6kKvHIxQ38Kg4Os/8vB+s9dMQIDAQAB
 1：p1格式公钥 参考:
 "3081890281810092d9d8d04fb5f8ef9b8374f21690fd46fdbf49b40eeccdf416b4e2ac2044b0cfe3bd67eb4416b26fd18c9d3833770a526fd1ab66a83ed969af74238d6c900403fc498154ec74eaf420e7338675cad7f19332b4a56be4ff946b662a3c2d217efbe4dc646fb742b8c62bfe8e25fd5dc59e7540695fa8b9cd5bfd9f92dfad009d230203010001"
 2：pem 证书 参考:
 "MIIDsDCCAxmgAwIBAgIQeJ0/mrqG2CVi8D61fznnkzANBgkqhkiG9w0BAQUFADAkMQswCQYDVQQGEwJDTjEVMBMGA1UEChMMQ0ZDQSBURVNUIENBMB4XDTExMDYwMjA4MTU0M1oXDTExMDcwMjA4MTU0M1owdjELMAkGA1UEBhMCQ04xFTATBgNVBAoTDENGQ0EgVEVTVCBDQTEOMAwGA1UECxMFREdSQ0MxFDASBgNVBAsTC0VudGVycHJpc2VzMSowKAYDVQQDFCEwNDFAM1dUUHdkVGVzdEBXVFB3ZFRlc3RAMDAwMDAwMDEwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAJLZ2NBPtfjvm4N08haQ/Ub9v0m0DuzN9Ba04qwgRLDP471n60QWsm/RjJ04M3cKUm/Rq2aoPtlpr3QjjWyQBAP8SYFU7HTq9CDnM4Z1ytfxkzK0pWvk/5RrZio8LSF+++TcZG+3QrjGK/6OJf1dxZ51QGlfqLnNW/2fkt+tAJ0jAgMBAAGjggGPMIIBizAfBgNVHSMEGDAWgBRGctwlcp8CTlWDtYD5 C9vpk7P0RTAdBgNVHQ4EFgQUBqh+5IwL3tg/OSysLyQnEFVtKBowCwYDVR0PBAQDAgTwMAwGA1UdEwQFMAMBAQAwOwYDVR0lBDQwMgYIKwYBBQUHAwEGCCsGAQUFBwMCBggrBgEFBQcDAwYIKwYBBQUHAwQGCCsGAQUFBwMIMIHwBgNVHR8EgegwgeUwT6BNoEukSTBHMQswCQYDVQQGEwJDTjEVMBMGA1UEChMMQ0ZDQSBURVNUIENBMQwwCgYDVQQLEwNDUkwxEzARBgNVBAMTCmNybDEyN18xMzUwgZGggY6ggYuGgYhsZGFwOi8vdGVzdGxkYXAuY2ZjYS5jb20uY246Mzg5L0NOPWNybDEyN18xMzUsT1U9Q1JMLE89 Q0ZDQSBURVNUIENBLEM9Q04/Y2VydGlmaWNhdGVSZXZvY2F0aW9uTGlzdD9iYXNlP29iamVjdGNsYXNzPWNSTERpc3RyaWJ1dGlvblBvaW50MA0GCSqGSIb3DQEBBQUAA4GBAMbp6tCu4xIiyVaBfTeWzRKX32rt8awuj+CozwkM9lvwLppclM1YnT3Jc2gL7wZPzme8LXGu0NMsqAQ6RQNyNKj4O2nD8eeCmZ3AtRRUyd4boG6x5SE5oRX8Ms2m/8EPxSVbSndg6hGr3lMPv5cqURM5YlSPLhzZdyVMdf06npBm"
 
 *
 *  @return AES(RSA)加密密文
 */
- (NSString *)      getOutput4:(int)certype;
/*!
 *  @brief  获取国密sm2加密密文
 *
 *  @return 返回sm2加密密文
 */
- (NSString *)      getOutput5;
/*!
 *  @brief 获取国密sm3加密密文
 *
 *  @return 返回sm3加密密文
 */
- (NSString *)      getOutput6;
/*!
 *  @brief 获取国密sm4加密密文
 *
 *  @return 返回sm4加密密文
 */
- (NSString *)      getOutput7;
/*!
 *  @brief 获取国密sm4(sm2)加密密文
 *
 *  @return 返回sm4(sm2)加密密文
 */
- (NSString *)      getOutput8;

/*!
 @function
 @abstract   get version of current app
 @result     [NSString] number of current app
 */
+ (NSString *)getVersion;

///*!
// * @brief 返回一个包含两个int的数组。int[0]返回当前输入框内容的字符架构：完全为空，返回0。
// 仅有数字，字符或特殊符号为1。例：”1234” ”abcd” “%#@!”
// 有两种组合返回2。例:”12bd” “12@#” “ab@#”
// 有三种组合返回3。例：”1@b” “1@2ab3”
// int[1]返回当前输入框内容是否符合预设的简单密码规则：
// *
// *  @return 密码强度,简单密码，返回1。
// 否则，返回0。
// */
- (NSArray*)getInputLevel;
/*!
 *  @brief  返回当前输入框内容是否符合m_strInput2所设置的正则规则
 *
 *  @return true 或者 false
 */
- (bool)            isMatch;

/*!
 *  @author tengzhixiang, 16-03-17 15:03:01
 *
 *  @brief  清空输入密文
 *
 *  @return 无
 */
- (void)            Clean;
/*!
 *  @brief 收起键盘,调用此方法 可以触发 _DoneDelegate DoneFun:sender
 *
 *  @param sender 控件对象
 */
- (void)DoneExecute:(id)sender;
/*!
 *  @brief  获取键盘高度，dutrust专用接口
 *
 *  @return 返回键盘高度
 */
- (float)getKeyboardHeight;

@end
