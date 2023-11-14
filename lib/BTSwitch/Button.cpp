#include "BTSwitch.h"

#define DEBUG

BTSwitch::Button::Button(BTSwitch::DeviceStatus* deviceStatus) {

    _deviceStatus = new BTSwitch::DeviceStatus();
    _deviceStatus = deviceStatus;
    _isPressed = false;
    _releaseButtonTime = 0;
    _buttonPushedTime = 0;
    _pressButtonTime = millis();

    if(digitalRead(BTSWITCH_BUTTON)) {
        _currentButtonState = button_state::ON;
        _previousButtonState = button_state::ON;
    } else {
        _currentButtonState = button_state::OFF;
        _previousButtonState = button_state::OFF;
    }
}

BTSwitch::Button::~Button() {
    delete _deviceStatus;
}

void BTSwitch::Button::checkState(void) {
    // check actual button state
    if(digitalRead(BTSWITCH_BUTTON)) {
        _deviceStatus->setEvent(device_events::BUTTON_RELEASED, event_status::IS_PENDING);
        _currentButtonState = button_state::OFF;
    } else {
        _deviceStatus->setEvent(device_events::BUTTON_PRESSED, event_status::IS_PENDING);
        _currentButtonState = button_state::ON;

    }
    // rising edge detection
    if(_currentButtonState == button_state::ON && _previousButtonState == button_state::OFF) {
        #ifdef DEBUG
            Serial.println("Button rising edge");
        #endif
        this->risingEdgeDetected();
        _previousButtonState = button_state::ON;
    }
    // falling edge detection        
    if (_currentButtonState == button_state::OFF && _previousButtonState == button_state::ON) {
        #ifdef DEBUG
            Serial.println("Button falling edge");
        #endif
        this->fallingEdgeDetected();
        _previousButtonState = button_state::OFF;
    }
    /////////////// long button push reaction ///////////////
    if(_deviceStatus->getEvent(device_events::BUTTON_LONG_PUSH) == event_status::IS_PENDING) {

        _deviceStatus->setEvent(device_events::BUTTON_LONG_PUSH, event_status::DONE);
        _deviceStatus->setOutputActive(!_deviceStatus->getOutputActive());
        if(!_deviceStatus->getOutputActive()) {
            delay(1000); // wait until led stripe clears
            esp_deep_sleep_start();
        }
    }
    /////////////// short button push reaction ///////////////
    if(_deviceStatus->getOutputActive()) {
        if(_deviceStatus->getEvent(device_events::BUTTON_SHORT_PUSH) == event_status::IS_PENDING) {
            
            _deviceStatus->setEvent(device_events::BUTTON_SHORT_PUSH, event_status::DONE);
            _deviceStatus->setOutputMode((effect)(_deviceStatus->getOutputMode() + 1));
        }
    }
}

void BTSwitch::Button::risingEdgeDetected(void) {
    _pressButtonTime = millis();
    _deviceStatus->setEvent(device_events::BUTTON_RISING_EDGE, event_status::IS_PENDING);
}

void BTSwitch::Button::fallingEdgeDetected(void) {
    _deviceStatus->setEvent(device_events::BUTTON_FALLING_EDGE, event_status::IS_PENDING);

    _isPressed = false;
    _releaseButtonTime = millis();

    if(_releaseButtonTime > _pressButtonTime)
        _buttonPushedTime = _releaseButtonTime - _pressButtonTime;
    else
        _buttonPushedTime = 0xFFFFFFFF - _pressButtonTime + _releaseButtonTime;

    if(_buttonPushedTime < LONG_BUTTON_PUSH_MS)
        BTSwitch::Button::shortPush();
    else
        BTSwitch::Button::longPush();
}

void BTSwitch::Button::shortPush(void) {
    #ifdef DEBUG
        Serial.println("Button short push");
    #endif
    _deviceStatus->setEvent(device_events::BUTTON_SHORT_PUSH, event_status::IS_PENDING);
}

void BTSwitch::Button::longPush(void) {
    #ifdef DEBUG
        Serial.println("Button long push");
    #endif
    _deviceStatus->setEvent(device_events::BUTTON_LONG_PUSH, event_status::IS_PENDING);
}