# react-native-password-guard-input
密码卫士

## Install 安装
```
npm i react-native-password-guard-input --S
react-native link react-native-password-guard-input
```
## Configuration 配置
### android
在项目的`android/app/src/AndroidManifest.xml`文件中加入：

```
<meta-data android:name="PGI_LICENSE" android:value="${PGI_LICENSE}" />
<meta-data android:name="PGI_CIPHER_KEY" android:value="${PGI_CIPHER_KEY}" />
<meta-data android:name="PGI_PUBLIC_KEY" android:value="${PGI_PUBLIC_KEY}" />
<meta-data android:name="PGI_ECC_KEY" android:value="${PGI_ECC_KEY}" />
```
在项目的`android/app/build.gradle`文件的`defaultConfig`节点内增加：

```
 manifestPlaceholders = [
       PGI_LICENSE   : [YOUR-LICENSE],
       PGI_CIPHER_KEY: [YOUR-CIPHER_KEY],
       PGI_PUBLIC_KEY: [YOUR-PUBLIC_KEY],
       PGI_ECC_KEY   : [YOUR-ECC_KEY],
  ]
```

## Props属性


| Name                    | Type  | Default  | Note
| ----------------------- |:-----:| :-------:| -------
| isNumberPad     | bool  | false     | 是否显示为数字键盘
| isEncrypt     | bool  | true     | 是否对输入的文字进行加密
| hasPressAnim     | bool  | false     | 是否有按键的动画效果
| hasPressState     | bool  | false     | 是否有按键的按下状态
| maxLength     | number  | 100     | 最大输入长度
| reorderType     | number  | 0     | 键盘是否乱序；可选值：0:默认不乱序；1:初始化后只乱序一次；2:每次点击键盘都重新排序。
| inputRegex     | string  |     | 键盘输入正则规则，默认为无限制。
| onTextChanged     | func  |     | 输入框内文本发生变化的回调；返回的值为object。具体见下面;

### onTextChanged 事件的返回值枚举
| Name                    | Type  | Default  | Note
| ----------------------- |:-----:| :-------:| -------
| textLength     | number  | 0     | 用户输入数据的长度
| aesCipherText     | string  | null     | AES加密密文，Base64编码
| md5CipherText     | string  | null     | MD5哈希值
| rsaAesCipherText     | string  | null     | RSA+AES加密密文，Base64编码
| sm2CipherText     | string  | null     | SM2加密密文，Base64编码
| sm3CipherText     | string  | null     | SM3加密密文，十六进制编码
| sm4CipherText     | string  | null     | SM4加密密文，Base64编码

## Usage 使用
```
.....
import PassGuardInput from 'react-native-password-guard-input';

export default class PasswordInputExample extends Component {
    render() {
        return (
            <View style={styles.container}>
            	<PassGuardInput hasPressState={true} isNumberPad={true} 
            		maxLength={6}  onTextChanged={this._onChange.bind(this)}
            		style={{ width: 100, height: 40 }}/>
            </View>
        );
    }

    _onChange(t) {
        console.log(t);
    }
}
.....
```
