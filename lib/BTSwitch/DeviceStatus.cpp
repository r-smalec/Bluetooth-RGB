#include "BTSwitch.h"

BTSwitch::DeviceStatus::DeviceStatus() {
    
}

void BTSwitch::DeviceStatus::init() {
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