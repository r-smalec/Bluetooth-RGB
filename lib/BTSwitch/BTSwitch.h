#ifndef BTSWITCH_H
#define BTSWITCH_H

#include <Arduino.h>

#define BTSWITCH_BUTTON 35

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

namespace BTSwitch {

    esp_reset_reason_t printResetReason(void);
    esp_sleep_wakeup_cause_t printWakeupReason(void);
    void initGPIO(void);

    class Button {
        public:
            Button();
            ~Button() {};
            void checkState(void);
            void risingEdgeDetected(void);
            void fallingEdgeDetected(void);
            void shortButtonPush(void);
            void longButtonPush(void);
            bool isPressed;
            uint32_t howLongIsPressed;

        private:
            enum button_state previousButtonState;
            enum button_state currentButtonState;
            uint32_t pressButtonTime;
            uint32_t releaseButtonTime;
    };

    class Led {
        public:
            Led();
            ~Led() {};
            struct color_RGB setColor(enum color ledColor, uint8_t brightnessPercent);

        private:
            void setColorRGB(uint8_t R, uint8_t G, uint8_t B);
            uint8_t colorTransform(uint8_t colorParameter, float brightness);
            uint8_t rLedPin;
            uint8_t gLedPin;
            uint8_t bLedPin;
            struct color_RGB colorRGB;
    };

    class Battery {
        public:
            Battery();
            ~Battery() {};
            uint16_t getVoltageMeasure(void);
            uint16_t getRawAnalogRead(void);
            bool isDischarged(void);
            bool isDeeplyDischarged(void);
            bool isCharged(void);
        private:
            uint8_t batteryPin;
            uint8_t chargerStatusPin;
            uint8_t usbStatusPin;
            uint16_t rawAnalogRead;
            uint16_t battVoltage;
            bool isBattCharged;
            bool isBattDischarged;
            bool isBattDeeplyDischarged;
    };

    class Output {
        public:

        private:
    };

};


#endif
