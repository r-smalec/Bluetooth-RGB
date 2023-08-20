#include "BTSwitch.h"

BTSwitch::DeviceStatus::DeviceStatus() {
    for(int i = 0; i < device_events::EVENTS_NO; i++) {
        _events[i] = event_status::DONE;
    }
}
