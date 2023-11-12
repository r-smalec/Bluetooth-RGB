#include <BTSwitch.h>

RTC_DATA_ATTR uint16_t numberOfBoots = 0;

TaskHandle_t Task1;
void Task1code(void * pvParameters);

BTSwitch::DeviceStatus deviceStatus;
BTSwitch::Button button(&deviceStatus);
BTSwitch::Led led(&deviceStatus);
BTSwitch::Output output(&deviceStatus);

void setup() {
  numberOfBoots++;

  BTSwitch::initGPIO();
  deviceStatus.init();
  Serial.print("\nBoot no: ");
  Serial.println(numberOfBoots);
  BTSwitch::printResetReason();
  BTSwitch::printWakeupReason();

  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 
}

void Task1code(void * pvParameters) {
  while(1) {
    vTaskDelay(10);
    output.checkIfChangeOutput();
  }
}

void loop() {
  button.checkState();
  led.checkIfChangeColor();
  vTaskDelay(10);
}