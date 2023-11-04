#include "BTSwitch.h"

BTSwitch::DeviceStatus::DeviceStatus() {
    
}

void BTSwitch::DeviceStatus::init() {
    _outputMode = 0;
    _buttonLoopActive = false;
    for(int i = 0; i < device_events::EVENTS_NO; i++) {
        _events[i] = event_status::DONE;
    }
}

void BTSwitch::DeviceStatus::eventWrite(device_events event, event_status status) {
    if(event < device_events::EVENTS_NO)
        _events[event] = status;
}

event_status BTSwitch::DeviceStatus::eventRead(device_events event) {
    if(event < device_events::EVENTS_NO)
        return _events[event];
    return event_status::UNKNOWN;
}

uint8_t BTSwitch::DeviceStatus::getOutputMode() {
    return _outputMode;
}

void BTSwitch::DeviceStatus::setOutputMode(uint8_t mode) {
    if(mode <= OUTPUT_MODE_TOP_LIMIT && mode >= OUTPUT_MODE_BOT_LIMIT)
        _outputMode = mode;
    else
        _outputMode = OUTPUT_MODE_BOT_LIMIT;
}

bool BTSwitch::DeviceStatus::getButtonLoopActive() {
    return _buttonLoopActive;
}

void BTSwitch::DeviceStatus::setButtonLoopActive(bool state) {
    _buttonLoopActive = state;
}