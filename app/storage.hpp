#ifndef STTM_STORAGE_H
#define STTM_STORAGE_H

#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <EEPROM.h>
#include <float.h>

struct Config {
	String wifi_ssid;
	String wifi_pwd;
};

bool validate();

void hasChanged();

struct SysCfg {
	public:
		void set(Config new_cfg) {
			if (validate()) {
				cfg = new_cfg;

				Serial.println(cfg.wifi_ssid);
				Serial.println(cfg.wifi_pwd);
				// treat new info
				hasChanged();
			}
		}

		// do not return by reference
		Config get() const {
			return cfg;
		}

	private:
    	Config cfg;
};

void loadConfiguration();

void saveConfiguration();

void setup_storage();

void loop_storage();

#endif