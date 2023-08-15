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

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void setup() {

  BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();
  BTSwitch::initGPIO();

  digitalWrite(BTSWITCH_OUTPUT_POWER, HIGH);
}

void loop() {
  if(digitalRead(BTSWITCH_BUTTON)) {
    digitalWrite(BTSWITCH_LED_R, HIGH);
    digitalWrite(BTSWITCH_LED_G, HIGH);
    digitalWrite(BTSWITCH_LED_B, LOW);
  }  else {
    digitalWrite(BTSWITCH_LED_R, LOW);
    digitalWrite(BTSWITCH_LED_G, LOW);
    digitalWrite(BTSWITCH_LED_B, HIGH);
  }
  rainbow(10);
  // strip.fill(0xf000f0, 0, 16);
  // strip.show();
  // delay(100);
  // colorWipe(strip.Color(255,   0,   80), 50);
}
