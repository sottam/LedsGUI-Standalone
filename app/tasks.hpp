#ifndef STTM_TASKS_H
#define STTM_TASKS_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>

#include "rtc.hpp"
#include "storage.hpp"

TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1code( void * parameter) {
  for(;;) {
    //code
	  delay(1000);
  }
}

void Task2code( void * parameter) {
  for(;;) {
    //code
	  delay(2000);
  }
}

void setup_tasks() {
    xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */
	
	xTaskCreatePinnedToCore(
      Task2code, /* Function to implement the task */
      "Task2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task2,  /* Task handle. */
      0); /* Core where the task should run */
}

#endif 