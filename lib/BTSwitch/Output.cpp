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
    switch(_deviceStatus->getOutputMode()) {
        case 0:
            colorWipe(_strip.Color(  0,   0,   0), 50);    // Black/off
            break;
        case 1:
            colorWipe(_strip.Color(199,  21, 133), 50);    // Pink
            break;
        case 2:
            colorWipe(_strip.Color(  0, 255, 255), 50);    // Teal
            break;
        case 3:
            colorWipe(_strip.Color(255,   0,   0), 50);    // Red
            break;
        case 4:
            rainbow(10);
            break;
        default:
            break;
    }

    if(_deviceStatus->eventRead(device_events::BUTTON_LONG_PUSH) == event_status::IS_PENDING) {
        
        _deviceStatus->eventWrite(device_events::BUTTON_LONG_PUSH, event_status::DONE);
        _deviceStatus->setOutputMode(_deviceStatus->getOutputMode() + 1);
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
        
        for(int i=0; i<_strip.numPixels(); i++) {
            int pixelHue = firstPixelHue + (i * 65536L / _strip.numPixels());
            _strip.setPixelColor(i, _strip.gamma32(_strip.ColorHSV(pixelHue)));
        }
        _strip.show();
        delay(wait);
    }
}
