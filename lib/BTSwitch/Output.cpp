#include "BTSwitch.h"
#include <Adafruit_NeoPixel.h>

BTSwitch::Output::Output(BTSwitch::DeviceStatus* deviceStatus) {
    _deviceStatus = new BTSwitch::DeviceStatus();
    _deviceStatus = deviceStatus;

    digitalWrite(BTSWITCH_OUTPUT_POWER, HIGH);
}

BTSwitch::Output::~Output() {
    delete _deviceStatus;
}