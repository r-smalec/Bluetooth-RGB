#include "BTSwitch.h"

BTSwitch::Button::Button(BTSwitch::DeviceStatus* deviceStatus) {

    _deviceStatus = new BTSwitch::DeviceStatus();
    _deviceStatus = deviceStatus;
    _isPressed = false;

    if(digitalRead(BTSWITCH_BUTTON)) {
        _currentButtonState = button_state::OFF;
        _previousButtonState = button_state::OFF;
    }
    else {
        _currentButtonState = button_state::ON;
        _previousButtonState = button_state::ON;
    }
}

BTSwitch::Button::~Button() {
    delete _deviceStatus;
}

void BTSwitch::Button::checkState(void) {
    // check actual button state
    if(digitalRead(BTSWITCH_BUTTON)) {
        _deviceStatus->_events[device_events::BUTTON_RELEASED] = event_status::IS_PENDING;
        _currentButtonState = button_state::OFF;
    } else {
        _deviceStatus->_events[device_events::BUTTON_PRESSED] = event_status::IS_PENDING;
        _currentButtonState = button_state::ON;
    }
    // rising edge detection
    if(_currentButtonState == button_state::ON && _previousButtonState == button_state::OFF) {
        
        this->risingEdgeDetected();
        _previousButtonState = button_state::ON;
    }
    // falling edge detection        
    if (_currentButtonState == button_state::OFF && _previousButtonState == button_state::ON) {
        
        this->fallingEdgeDetected();
        _previousButtonState = button_state::OFF;
    }
}

void BTSwitch::Button::risingEdgeDetected(void) {
    _deviceStatus->_events[device_events::BUTTON_RISING_EDGE] = event_status::IS_PENDING;
}

void BTSwitch::Button::fallingEdgeDetected(void) {
    _deviceStatus->_events[device_events::BUTTON_FALLING_EDGE] = event_status::IS_PENDING;

    _isPressed = false;
    _releaseButtonTime = millis();

    uint32_t buttonPushedTime;

    if(_releaseButtonTime > _pressButtonTime)
        buttonPushedTime = _releaseButtonTime - _pressButtonTime;
    else
        buttonPushedTime = 0xFFFFFFFF - _pressButtonTime + _releaseButtonTime;

    if(buttonPushedTime < LONG_BUTTON_PUSH_MS)
        BTSwitch::Button::shortPush();
    else
        BTSwitch::Button::longPush();
}

void BTSwitch::Button::shortPush(void) {
    _deviceStatus->_events[device_events::BUTTON_SHORT_PUSH] = event_status::IS_PENDING;
}

void BTSwitch::Button::longPush(void) {
    _deviceStatus->_events[device_events::BUTTON_LONG_PUSH] = event_status::IS_PENDING;
}