#include "BTSwitch.h"
// #include "analogWrite.h"

#define FULL_BRIGHTNESS 20 //procent jasności w trybie pełnej jasności diody RGB
#define PART_BRIGHTNESS 5 //procent jasności w trybie częściowej jasności diody RGB
#define NO_COLOR 255

BTSwitch::Led::Led() {
    
    BTSwitch::Led::setColor(color::BLACK, FULL_BRIGHTNESS);
}

void BTSwitch::Led::setColorRGB(uint8_t R, uint8_t G, uint8_t B) {
    
    this->colorRGB.red =    R;
    this->colorRGB.green =  G;
    this->colorRGB.blue =   B;
}

uint8_t BTSwitch::Led::colorTransform(uint8_t colorParameter, float brightness) {

    return 255 - (uint8_t)((float)(255 - colorParameter) * brightness);
}

struct color_RGB BTSwitch::Led::setColor(enum color ledColor, uint8_t brightnessPercent) {

    float brightness = (float)brightnessPercent / 100.0;
    switch(ledColor) {
        case color::WHITE:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(0, brightness));
            break;
        case color::GREEN:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        BTSwitch::Led::colorTransform(0, brightness),
                                        NO_COLOR);
            break;
        case color::YELLOW:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(100, brightness),
                                        NO_COLOR);
            break;
        case color::RED:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        NO_COLOR,
                                        NO_COLOR);
            break;
        case color::ORANGE:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(90, brightness),
                                        NO_COLOR);
            break;
        case color::BLUE:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        NO_COLOR,
                                        BTSwitch::Led::colorTransform(0, brightness));
            break;
        case color::PURPLE:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        NO_COLOR,
                                        BTSwitch::Led::colorTransform(0, brightness));
            break;
        case color::LIGHTBLUE:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(0, brightness));
            break;
        case color::TEAL:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        BTSwitch::Led::colorTransform(127, brightness),
                                        BTSwitch::Led::colorTransform(127, brightness));
            break;
        case color::PINK:
            BTSwitch::Led::setColorRGB( BTSwitch::Led::colorTransform(0, brightness),
                                        BTSwitch::Led::colorTransform(63, brightness),
                                        BTSwitch::Led::colorTransform(52, brightness));
            break;
        case color::BLACK:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        NO_COLOR,
                                        NO_COLOR);
            break;
        case color::NONE:
            BTSwitch::Led::setColorRGB( NO_COLOR,
                                        NO_COLOR,
                                        NO_COLOR);
            break;
    }

    // analogWrite(this->rLedPin, this->colorRGB.red);
    // analogWrite(this->gLedPin, this->colorRGB.green);
    // analogWrite(this->bLedPin, this->colorRGB.blue);
    
    return this->colorRGB;
}