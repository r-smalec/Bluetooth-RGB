#include "BTSwitch.h"

BTSwitch::DeviceStatus::DeviceStatus() {
    
}

void BTSwitch::DeviceStatus::init() {
    _outputMode = effect::COLOR_WIPE1;
    _outputActive = 1;
    for(int i = 0; i < device_events::EVENTS_NO; i++) {
        _events[i] = event_status::DONE;
    }
}

void BTSwitch::DeviceStatus::setEvent(device_events event, event_status status) {
    if(event < device_events::EVENTS_NO)
        _events[event] = status;
}

event_status BTSwitch::DeviceStatus::getEvent(device_events event) {
    if(event < device_events::EVENTS_NO)
        return _events[event];
    return event_status::UNKNOWN;
}

effect BTSwitch::DeviceStatus::getOutputMode() {
    return _outputMode;
}

void BTSwitch::DeviceStatus::setOutputMode(effect mode) {
    if(mode < effect::EFFECT_NO && mode >= effect::COLOR_WIPE1)
        _outputMode = mode;
    else
        _outputMode = effect::COLOR_WIPE1;
}

bool BTSwitch::DeviceStatus::getOutputActive() {
    return _outputActive;
}

void BTSwitch::DeviceStatus::setOutputActive(bool state) {
    _outputActive = state;
}