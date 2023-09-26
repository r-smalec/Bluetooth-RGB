#include <BTSwitch.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(16, BTSWITCH_OUTPUT, NEO_GRB + NEO_KHZ800);

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show();
    delay(wait);
  }
}

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
  
  //button.checkState();
  //led.changeColor();
  rainbow(10);
}
