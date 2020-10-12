#ifndef STTM_COMMUNICATIONS_H
#define STTM_COMMUNICATIONS_H

#define PRETTY_RESPONSE

#include <Arduino.h>
#include <ArduinoJson.h>

#include "rtc.hpp"
#include "storage.hpp"
#include "version.hpp"

//=============== PROTOCOL DEFINES ====================
#define MESSAGE_START			'\x02' //STX
#define MESSAGE_END				'\x03' //ETX

extern String header_text;
extern SysCfg sysCfg;


void setup_communications();
void loop_communications();

void process_SERIAL_data(const char* buffer);
void processSerialIncomingChar(const char inChar);


#endif