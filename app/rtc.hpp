#ifndef STTM_RTC_H
#define STTM_RTC_H
#include <Arduino.h>

#include <esp_system.h>
#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>
/*
    Com o Unix time, podemos facilmente controlar acoes do MCU por data, visto que utilizaremos os segundos
    e sao faceis de usar em IFs
    Voce pode criar uma estrutura com a data desejada e depois converter para segundos (inverso do que foi feito acima)
    caso deseje trabalhar para atuar em certas datas e horarios
    No exemplo abaixo, o MCU ira printar o texto **APENAS** na data e horario (28/02/2019 12:00:05) ate (28/02/2019 12:00:07)
*/

//1551355200
String setTime(String unix_time_str);
tm getTime();
time_t getTimeinSeconds();
String getFTime(tm data);

void setup_RTC();
void loop_RTC();

#endif