#ifndef STTM_WIFI_H
#define STTM_WIFI_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>

#include "storage.hpp"

extern SysCfg sysCfg;

void setup_wifi();

void loop_wifi();

#endif