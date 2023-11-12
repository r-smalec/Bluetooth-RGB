#include "BTSwitch.h"

void BTSwitch::initGPIO() {

  Serial.begin(9600);

  pinMode(BTSWITCH_BUTTON,        INPUT);

  pinMode(BTSWITCH_OUTPUT,         OUTPUT);
  pinMode(BTSWITCH_OUTPUT_POWER,   OUTPUT);

  pinMode(BTSWITCH_LED_R,         OUTPUT);
  pinMode(BTSWITCH_LED_G,         OUTPUT);
  pinMode(BTSWITCH_LED_B,         OUTPUT);
  
  pinMode(BTSWITCH_USB_STAT,      INPUT);
  pinMode(BTSWITCH_BATT_STAT,     INPUT_PULLUP);
  pinMode(BTSWITCH_BATT_U,        INPUT);

  // pinMode(BTSWITCH_IO_0, );
  // pinMode(BTSWITCH_IO_1, );
  // pinMode(BTSWITCH_IO_2, );
  // pinMode(BTSWITCH_IO_3, );
  // pinMode(BTSWITCH_IO_4, );
  // pinMode(BTSWITCH_IO_5, );
  // pinMode(BTSWITCH_IO_6, );

  digitalWrite(BTSWITCH_OUTPUT_POWER, HIGH);
}

esp_reset_reason_t BTSwitch::printResetReason(void){
  
    esp_reset_reason_t reset_reason;
    reset_reason = esp_reset_reason();

    switch(reset_reason) {
      case ESP_RST_UNKNOWN:           Serial.println("ESP_RST_UNKNOWN");                          break;
      case ESP_RST_POWERON:           Serial.println("ESP_RST_POWERON");                          break;
      case ESP_RST_EXT:               Serial.println("ESP_RST_EXT");                              break;
      case ESP_RST_SW:                Serial.println("ESP_RST_SW");                               break;
      case ESP_RST_PANIC:             Serial.println("ESP_RST_PANIC");                            break;
      case ESP_RST_INT_WDT:           Serial.println("ESP_RST_INT_WDT");                          break;
      case ESP_RST_TASK_WDT:          Serial.println("ESP_RST_TASK_WDT");                         break;
      case ESP_RST_WDT:               Serial.println("ESP_RST_WDT");                              break;
      case ESP_RST_DEEPSLEEP:         Serial.println("ESP_RST_DEEPSLEEP");                        break;
      case ESP_RST_BROWNOUT:          Serial.println("ESP_RST_BROWNOUT");                         break;
      case ESP_RST_SDIO:              Serial.println("ESP_RST_SDIO");                             break;
      default:                        Serial.printf("Different reset reason: %d\n",reset_reason); break;
    }

    return reset_reason;
}

esp_sleep_wakeup_cause_t BTSwitch::printWakeupReason(void){
  
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch(wakeup_reason) {
      case ESP_SLEEP_WAKEUP_EXT0:      Serial.println("ESP_SLEEP_WAKEUP_EXT0");                         break;
      case ESP_SLEEP_WAKEUP_EXT1:      Serial.println("ESP_SLEEP_WAKEUP_EXT1");                         break;
      case ESP_SLEEP_WAKEUP_TIMER:     Serial.println("ESP_SLEEP_WAKEUP_TIMER");                        break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD:  Serial.println("ESP_SLEEP_WAKEUP_TOUCHPAD");                     break;
      case ESP_SLEEP_WAKEUP_ULP:       Serial.println("ESP_SLEEP_WAKEUP_ULP");                          break;
      default:                         Serial.printf("Waked up not by deep sleep: %d\n",wakeup_reason); break;
    }

    return wakeup_reason;
}
