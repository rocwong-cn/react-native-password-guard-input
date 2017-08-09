/**
 * Created by Roc on 2017/8/7.
 * desc:
 */
import React, { Component } from 'react';
import { requireNativeComponent, TextInput } from 'react-native';
import PropTypes from 'prop-types';

export default class PassGuardInput extends Component {
    static propTypes = {
        isNumberPad: PropTypes.bool,
        isEncrypt: PropTypes.bool,
        hasPressAnim: PropTypes.bool,
        hasPressState: PropTypes.bool,
        maxLength: PropTypes.number,
        reorderType: PropTypes.oneOf([0, 1, 2]),
        inputRegex: PropTypes.string,
        onTextChanged: PropTypes.func,
        ...TextInput.propTypes,
    };

    render() {
        return <XInput {...this.props} onChange={this._onChange.bind(this)}/>;
    }

    _onChange(event) {
        if (typeof this.props[event.nativeEvent.type] === 'function') {
            this.props[event.nativeEvent.type](event.nativeEvent.params);
        }
    }
}
const XInput = requireNativeComponent('RCTPassGuardInput', PassGuardInput, {
    nativeOnly: { onChange: true }
});
