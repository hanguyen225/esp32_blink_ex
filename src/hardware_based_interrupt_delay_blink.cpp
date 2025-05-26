#include <Arduino.h>

#define LED_PIN 4

hw_timer_t *timer = NULL;
volatile bool ledState = false;

void IRAM_ATTR onTimer() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  timer = timerBegin(0, 80, true);                // 80MHz / 80 = 1MHz (1us per tick)
  timerAttachInterrupt(timer, &onTimer, true);    // Attach interrupt
  timerAlarmWrite(timer, 500000, true);           // 500000us = 0.5s toggle → 1Hz blink
  timerAlarmEnable(timer);                        // Enable the alarm
}

void loop() {
  // Nothing needed
}
