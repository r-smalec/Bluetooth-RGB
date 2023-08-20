#include <BTSwitch.h>

BTSwitch::DeviceStatus* deviceStatus;
BTSwitch::Button button(deviceStatus);
BTSwitch::Led led(deviceStatus);


void setup() {

  BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();
  BTSwitch::initGPIO();
  
}

void loop() {

}
