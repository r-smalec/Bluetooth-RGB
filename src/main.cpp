#include <BTSwitch.h>
// #include "esp_pthread.h"
// #include "esp_task_wdt.h"

RTC_DATA_ATTR uint16_t numberOfBoots = 0;

BTSwitch::DeviceStatus deviceStatus;
BTSwitch::Button button(&deviceStatus);
BTSwitch::Led led(&deviceStatus);
BTSwitch::Output output(&deviceStatus);

// pthread_t buttonLoopThread;
// static void* buttonLoop(void* arg);

void setup() {
  numberOfBoots++;

  BTSwitch::initGPIO();
  deviceStatus.init();
  Serial.print("\nBoot no: ");
  Serial.println(numberOfBoots);
  BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();

  // esp_pthread_cfg_t cfg;
  // cfg = esp_pthread_get_default_config();
  // cfg.stack_size = 16384;
  // cfg.inherit_cfg = true;
  // cfg.prio = 3;
  // esp_pthread_set_cfg(&cfg);
  // pthread_create(&buttonLoopThread, NULL, buttonLoop, NULL);
  //deviceStatus.setButtonLoopActive(true);
}

void loop() {
  button.checkState();
  led.checkIfChangeColor();
  output.checkIfChangeOutput();
}

// static void* buttonLoop(void* arg) {
//   while(1) {
//   }
//   return NULL;
// }