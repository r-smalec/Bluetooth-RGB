/*
* BTSwitch is a top level class for all devices and services on BTSwitch board,
* which are all communicated with eachother via DeviceStatus class which storages
* statuses for all tasks so as they are accessible for others tasks.
*/

#ifndef BTSWITCH_H
#define BTSWITCH_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define BTSWITCH_BUTTON 35
#define BTSWITCH_BUTTON_GPIO_NUM GPIO_NUM_35

#define BTSWITCH_OUTPUT 21
#define BTSWITCH_OUTPUT_POWER 19

#define BTSWITCH_LED_R 5
#define BTSWITCH_LED_G 14
#define BTSWITCH_LED_B 13

#define BTSWITCH_USB_STAT 18
#define BTSWITCH_BATT_STAT 2
#define BTSWITCH_BATT_U 27

// #define BTSWITCH_IO_0 22
// #define BTSWITCH_IO_1 23
// #define BTSWITCH_IO_2 25
// #define BTSWITCH_IO_3 26
// #define BTSWITCH_IO_4 32
// #define BTSWITCH_IO_5 33
// #define BTSWITCH_IO_6 34

#define LONG_BUTTON_PUSH_MS 500 //czas [ms] naciskania przycisku odczytywany jako "długie naciśnięcie", wykorzystany do kończenia wyszukiwania połączenie oraz kończenia połączenia (mruganie na przemian na biało i na kolor kanału), gdy przycisk zostanie naciśnięty długo 

#define OUTPUT_PIXEL_COUNT 14
#define OUTPUT_MODE_TOP_LIMIT 4
#define OUTPUT_MODE_BOT_LIMIT 0

enum color {
    WHITE =       0x00,
    GREEN =       0x01,
    YELLOW =      0x02,
    RED =         0x03,
    BLUE =        0x04,
    PURPLE =      0x05,
    LIGHTBLUE =   0x06,
    TEAL =        0x07,
    PINK =        0x08,
    ORANGE =      0x09,
    BLACK =       0x0A,
    NONE =        0xFF
};

struct color_RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

enum button_state { 
    ON, 
    OFF 
};

enum device_events {
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    BUTTON_RISING_EDGE,
    BUTTON_FALLING_EDGE,
    BUTTON_SHORT_PUSH,
    BUTTON_LONG_PUSH,
    EVENTS_NO
};

enum event_status {
    IS_PENDING,
    IN_PROGRESS,
    DONE,
    UNKNOWN
};

enum effect {
    COLOR_WIPE1,
    COLOR_WIPE2,
    COLOR_WIPE3,
    COLOR_WIPE4,
    RAINBOW,
    EFFECT_NO
};

namespace BTSwitch {

    esp_reset_reason_t printResetReason();
    esp_sleep_wakeup_cause_t printWakeupReason();
    void initGPIO(void);

    class DeviceStatus {
        public:
            DeviceStatus();
            ~DeviceStatus() {};
            void init();
            void setEvent(device_events event, event_status status);
            event_status getEvent(device_events event);
            effect getOutputMode();
            void setOutputMode(effect mode);
            bool getOutputActive();
            void setOutputActive(bool state);
        private:
            bool _outputActive;
            effect _outputMode;
            event_status _events[device_events::EVENTS_NO];
    };

    class Button {
        public:
            Button(BTSwitch::DeviceStatus* deviceStatus);
            ~Button();
            void checkState();

        private:
            void risingEdgeDetected();
            void fallingEdgeDetected();
            void shortPush();
            void longPush();
            BTSwitch::DeviceStatus* _deviceStatus;
            bool _isPressed;
            uint32_t _howLongIsPressed;
            enum button_state _previousButtonState;
            enum button_state _currentButtonState;
            uint32_t _pressButtonTime;
            uint32_t _releaseButtonTime;
            uint32_t _buttonPushedTime;
    };

    class Led {
        public:
            Led(BTSwitch::DeviceStatus* deviceStatus);
            ~Led();
            void checkIfChangeColor();

        private:
            BTSwitch::DeviceStatus* _deviceStatus;
            struct color_RGB setColor(enum color ledColor, uint8_t brightnessPercent);
            void setColorRGB(uint8_t R, uint8_t G, uint8_t B);
            uint8_t colorTransform(uint8_t colorParameter, float brightness);
            struct color_RGB _colorRGB;
    };

    // class Battery {
    //     public:
    //         Battery(BTSwitch::DeviceStatus* deviceStatus);
    //         ~Battery();
    //         uint16_t getVoltageMeasure(void);
    //         uint16_t getRawAnalogRead(void);
    //         bool isDischarged(void);
    //         bool isDeeplyDischarged(void);
    //         bool isCharged(void);
    //     private:
    //         BTSwitch::DeviceStatus* _deviceStatus;
    //         uint8_t _batteryPin;
    //         uint8_t _chargerStatusPin;
    //         uint8_t _usbStatusPin;
    //         uint16_t _rawAnalogRead;
    //         uint16_t _battVoltage;
    //         bool _isBattCharged;
    //         bool _isBattDischarged;
    //         bool _isBattDeeplyDischarged;
    // };

    class Output {
        public:
            Output(BTSwitch::DeviceStatus* deviceStatus);
            ~Output();
            void checkIfChangeOutput();
        private:
            BTSwitch::DeviceStatus* _deviceStatus;
            Adafruit_NeoPixel _strip;
            void colorWipe(uint32_t color, int wait);
            void rainbow(int wait);
    };

};


#endif
