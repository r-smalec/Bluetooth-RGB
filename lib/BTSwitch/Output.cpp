#include "BTSwitch.h"

BTSwitch::Output::Output(BTSwitch::DeviceStatus* deviceStatus)
                     : _strip(OUTPUT_PIXEL_COUNT, BTSWITCH_OUTPUT, NEO_GRB + NEO_KHZ800)  {
    _deviceStatus = new BTSwitch::DeviceStatus();
    _deviceStatus = deviceStatus;

    digitalWrite(BTSWITCH_OUTPUT_POWER, HIGH);
}

BTSwitch::Output::~Output() {
    delete _deviceStatus;
}

void BTSwitch::Output::checkIfChangeOutput() {
    if(_deviceStatus->getOutputActive()) {
        switch(_deviceStatus->getOutputMode()) {
            case effect::COLOR_WIPE1:
                colorWipe(_strip.Color(  0,   255, 0), 50);    // Green
                break;
            case effect::COLOR_WIPE2:
                colorWipe(_strip.Color(199,  21, 133), 50);    // Pink
                break;
            case effect::COLOR_WIPE3:
                colorWipe(_strip.Color(  0, 255, 255), 50);    // Teal
                break;
            case effect::COLOR_WIPE4:
                colorWipe(_strip.Color(255,   0,   0), 50);    // Red
                break;
            case effect::RAINBOW:
                rainbow(10);
                break;
            default:
                break;
        }
    } else {
        _strip.clear();
        _strip.show();
    }
}

void BTSwitch::Output::colorWipe(uint32_t color, int wait) {
  
    for(int i=0; i<_strip.numPixels(); i++) {
        _strip.setPixelColor(i, color);
        _strip.show();
        delay(wait);
    }
}

void BTSwitch::Output::rainbow(int wait) {

    for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
        
        if(_deviceStatus->getOutputActive() && _deviceStatus->getOutputMode() == effect::RAINBOW) {
            for(int i=0; i<_strip.numPixels(); i++) {

                if(_deviceStatus->getOutputActive() && _deviceStatus->getOutputMode() == effect::RAINBOW) {
                    int pixelHue = firstPixelHue + (i * 65536L / _strip.numPixels());
                    _strip.setPixelColor(i, _strip.gamma32(_strip.ColorHSV(pixelHue)));
                } else {
                    break;
                }
            }
            _strip.show();
            delay(wait);
        } else {
            break;
        }
    }
}
