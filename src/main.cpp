#include <BTSwitch.h>

BTSwitch::DeviceStatus* deviceStatus;
BTSwitch::Button button(deviceStatus);
BTSwitch::Led led(deviceStatus);


void setup() {

  BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();
  BTSwitch::initGPIO();

  digitalWrite(BTSWITCH_OUTPUT_POWER, HIGH);
}

void loop() {

}
