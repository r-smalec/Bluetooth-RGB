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

    if(digitalRead(BTSWITCH_BUTTON))
        _currentButtonState = button_state::OFF;
    else
        _currentButtonState = button_state::ON;
    
    if(_currentButtonState == button_state::ON && _previousButtonState == button_state::OFF) {
        
        this->risingEdgeDetected();
        _previousButtonState = button_state::ON;
    }
        
    if (_currentButtonState == button_state::OFF && _previousButtonState == button_state::ON) {
        
        this->fallingEdgeDetected();
        _previousButtonState = button_state::OFF;
    }
}

void BTSwitch::Button::risingEdgeDetected(void) {

}

void BTSwitch::Button::fallingEdgeDetected(void) {

    _isPressed = false;
    _releaseButtonTime = millis();

    uint32_t buttonPushedTime;

    if(_releaseButtonTime > _pressButtonTime)
        buttonPushedTime = _releaseButtonTime - _pressButtonTime;
    else
        buttonPushedTime = 0xFFFFFFFF - _pressButtonTime + _releaseButtonTime;

    if(buttonPushedTime < LONG_BUTTON_PUSH_MS)
        BTSwitch::Button::shortButtonPush();
    else
        BTSwitch::Button::longButtonPush();
}

void BTSwitch::Button::shortButtonPush(void) {
    
}

void BTSwitch::Button::longButtonPush(void) {
                      
}