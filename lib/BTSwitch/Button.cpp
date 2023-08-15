#include "BTSwitch.h"

BTSwitch::Button::Button() {

    this->isPressed = false;

    if(digitalRead(BTSWITCH_BUTTON)) {
        this->currentButtonState = button_state::OFF;
        this->previousButtonState = button_state::OFF;
    }
    else {
        this->currentButtonState = button_state::ON;
        this->previousButtonState = button_state::ON;
    }
}

void BTSwitch::Button::checkState(void) {

    if(digitalRead(BTSWITCH_BUTTON))
        this->currentButtonState = button_state::OFF;
    else
        this->currentButtonState = button_state::ON;
    
    if(this->currentButtonState == button_state::ON && this->previousButtonState == button_state::OFF) {
        
        this->risingEdgeDetected();
        this->previousButtonState = button_state::ON;
    }
        
    if (this->currentButtonState == button_state::OFF && this->previousButtonState == button_state::ON) {
        
        this->fallingEdgeDetected();
        this->previousButtonState = button_state::OFF;
    }
}

void BTSwitch::Button::risingEdgeDetected(void) {

}

void BTSwitch::Button::fallingEdgeDetected(void) {

    this->isPressed = false;
    this->releaseButtonTime = millis();

    uint32_t buttonPushedTime;

    if(this->releaseButtonTime > this->pressButtonTime)
        buttonPushedTime = this->releaseButtonTime - this->pressButtonTime;
    else
        buttonPushedTime = 0xFFFFFFFF - this->pressButtonTime + this->releaseButtonTime;

    if(buttonPushedTime < LONG_BUTTON_PUSH_MS)
        BTSwitch::Button::shortButtonPush();
    else
        BTSwitch::Button::longButtonPush();
}

void BTSwitch::Button::shortButtonPush(void) {
    
}

void BTSwitch::Button::longButtonPush(void) {
                      
}