package cc.rocwang.passguard;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.support.annotation.Nullable;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.annotations.ReactProp;
import com.facebook.react.uimanager.events.RCTEventEmitter;

import cn.passguard.PassGuardEdit;

import static java.security.AccessController.getContext;

/**
 * Created by Roc on 2017/8/8.
 */

public class PassGuardInputManager extends SimpleViewManager<View> {
    private Context mContext;
    private ThemedReactContext mReactContext;

    @Override
    public String getName() {
        return "RCTPassGuardInput";
    }

    private String PGI_LICENSE, PGI_CIPHER_KEY, PGI_PUBLIC_KEY, PGI_ECC_KEY;

    public PassGuardInputManager(Context context) {
        mContext = context;

        ApplicationInfo appInfo;
        try {
            appInfo = mContext.getPackageManager().getApplicationInfo(mContext.getPackageName(), PackageManager.GET_META_DATA);
            if (appInfo == null) {
                throw new Error("meta-data object is null");
            }
            if (!appInfo.metaData.containsKey("PGI_LICENSE")) {
                throw new Error("meta-data PGI_LICENSE not found in AndroidManifest.xml");
            } else {
                this.PGI_LICENSE = appInfo.metaData.get("PGI_LICENSE").toString();
            }

            if (!appInfo.metaData.containsKey("PGI_CIPHER_KEY")) {
                throw new Error("meta-data PGI_CIPHER_KEY not found in AndroidManifest.xml");
            } else {
                PGI_CIPHER_KEY = appInfo.metaData.get("PGI_CIPHER_KEY").toString();
            }
            if (!appInfo.metaData.containsKey("PGI_PUBLIC_KEY")) {
                throw new Error("meta-data PGI_PUBLIC_KEY not found in AndroidManifest.xml");
            } else {
                PGI_PUBLIC_KEY = appInfo.metaData.get("PGI_PUBLIC_KEY").toString();
            }
            if (!appInfo.metaData.containsKey("PGI_ECC_KEY")) {
                throw new Error("meta-data PGI_ECC_KEY not found in AndroidManifest.xml");
            } else {
                PGI_ECC_KEY = appInfo.metaData.get("PGI_ECC_KEY").toString();
            }

            if (isNullOrEmpty(PGI_LICENSE)) {
                throw new Error("PGI_LICENSE can not be empty");
            }
            if (isNullOrEmpty(PGI_CIPHER_KEY) && isNullOrEmpty(PGI_CIPHER_KEY) && isNullOrEmpty(PGI_CIPHER_KEY)) {
                throw new Error("PGI_CIPHER_KEY , PGI_CIPHER_KEY and PGI_CIPHER_KEY one of three should have a value");
            }

        } catch (PackageManager.NameNotFoundException e) {
            throw new Error(e);
        }
    }


    @ReactProp(name = "isNumberPad")
    public void setUseNumberPad(PassGuardEdit passGuardEdit, boolean isNumberPad) {
        Log.e("isNumberPad", isNumberPad + "");
        passGuardEdit.useNumberPad(isNumberPad);
    }

    @ReactProp(name = "isEncrypt")
    public void setEncrypt(PassGuardEdit passGuardEdit, boolean isEncrypt) {
        passGuardEdit.setEncrypt(isEncrypt);
    }

    @ReactProp(name = "hasPressAnim")
    public void setButtonPressAnim(PassGuardEdit passGuardEdit, boolean hasPressAnim) {
        passGuardEdit.setButtonPressAnim(hasPressAnim);
    }

    @ReactProp(name = "hasPressState")
    public void setButtonPress(PassGuardEdit passGuardEdit, boolean hasPressState) {
        passGuardEdit.setButtonPress(hasPressState);
    }

    @ReactProp(name = "maxLength")
    public void setMaxLength(PassGuardEdit passGuardEdit, int length) {
        Log.e("maxLength", length + "");
        passGuardEdit.setMaxLength(length);
    }

    @ReactProp(name = "inputRegex")
    public void setInputRegex(PassGuardEdit passGuardEdit, String regex) {
        passGuardEdit.setInputRegex(regex);
    }

    @ReactProp(name = "reorderType")
    public void setReorder(PassGuardEdit passGuardEdit, int reorder) {
        passGuardEdit.setReorder(reorder);
    }

    @Override
    public View createViewInstance(ThemedReactContext context) {
        mReactContext = context;
        Log.e("TAG", "密码输入框加载中....");

        PassGuardEdit passGuardEdit = new PassGuardEdit(context, null);
        PassGuardEdit.setLicense(PGI_LICENSE);//设置License开发权限。
        passGuardEdit.setCipherKey(PGI_CIPHER_KEY);//设置随机字符串。此串用于AES/SM4等的加密。
        passGuardEdit.setPublicKey(PGI_PUBLIC_KEY);//设置RSA加密公钥。此串用于RSA算法的加密。
        passGuardEdit.setEccKey(PGI_ECC_KEY);//设置SM2加密公钥。此串用于SM2算法的加密。
        passGuardEdit.initPassGuardKeyBoard();
        setListeners(passGuardEdit);
        return passGuardEdit;

    }

    public void setListeners(final PassGuardEdit passGuardEdit) {
        passGuardEdit.addTextChangedListener(new TextWatcher() {

            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                Log.e("beforeTextChanged", charSequence.toString());
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                Log.e("onTextChanged", charSequence.toString());
                int len = passGuardEdit.getLength();
                if (len > 0) {
                    WritableMap writableMap = Arguments.createMap();
                    writableMap.putString("aesCipherText", passGuardEdit.getAESCiphertext());
                    writableMap.putString("rsaAesCipherText", passGuardEdit.getRSAAESCiphertext());
                    writableMap.putString("sm2CipherText", passGuardEdit.getSM2Ciphertext());
                    writableMap.putString("sm3CipherText", passGuardEdit.getSM3Ciphertext());
                    writableMap.putString("sm4CipherText", passGuardEdit.getSM4Ciphertext());
                    writableMap.putString("md5CipherText", passGuardEdit.getMD5());
                    writableMap.putInt("textLength", len);

                    sendEvent(passGuardEdit, "onTextChanged", writableMap);
                }
            }

            @Override
            public void afterTextChanged(Editable editable) {
                Log.e("afterTextChanged", editable.toString());
            }
        });
    }

    /**
     * 向JS端提交事件
     *
     * @param eventName 返回给js的事件名称
     * @param params    参数值
     */
    private void sendEvent(PassGuardEdit passGuardEdit, String eventName, @Nullable WritableMap params) {
        WritableMap event = Arguments.createMap();
        event.putMap("params", params);
        event.putString("type", eventName);
        mReactContext.getJSModule(RCTEventEmitter.class).receiveEvent(passGuardEdit.getId(), "topChange", event);
    }

    private boolean isNullOrEmpty(String str) {
        return str == null || "".equals(str);
    }

}
