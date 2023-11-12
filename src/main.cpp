#include <BTSwitch.h>

TaskHandle_t Task1;
void Task1code(void * pvParameters);

BTSwitch::DeviceStatus deviceStatus;
BTSwitch::Button button(&deviceStatus);
BTSwitch::Output output(&deviceStatus);

void setup() {
  esp_sleep_enable_ext0_wakeup(BTSWITCH_BUTTON_GPIO_NUM, LOW);

  BTSwitch::initGPIO();
  esp_reset_reason_t resetReason = BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();
  deviceStatus.init();

  if(resetReason == ESP_RST_DEEPSLEEP)
    deviceStatus.setOutputActive(1);

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
}

void Task1code(void * pvParameters) {
  while(1) {
    vTaskDelay(10);
    output.checkIfChangeOutput();
  }
}

void loop() {
  vTaskDelay(10);
  button.checkState();
}