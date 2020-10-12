#include "storage.hpp"

SysCfg sysCfg;

void loadConfiguration() {
	EEPROM.begin(2048);

	EepromStream eepromStream(0, 2048);
	StaticJsonDocument<2048> doc;

	Serial.println("Loading these configutations...");
	
	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, eepromStream);
	serializeJsonPretty(doc, Serial);
	Serial.println();

	Config config = sysCfg.get();

	// Copy values from the JsonDocument to the Config
	config.wifi_ssid = doc["wifi_ssid"] | "";
	config.wifi_pwd = doc["wifi_pwd"] | "";

	sysCfg.set(config);

	if (error) {
		Serial.println("Failed to load from EEPROM, using default configuration");
		// Salving the defaults
		serializeJson(doc, eepromStream);
		EEPROM.commit();
	}
		
}

void saveConfiguration() {
	EepromStream eepromStream(0, 2048);
	StaticJsonDocument<2048> doc;

	Config config = sysCfg.get();
	
	// Set the values in the document
	doc["wifi_ssid"] = config.wifi_ssid;
	doc["wifi_pwd"] = config.wifi_pwd;

	Serial.println("Saving these configutations...");
	serializeJsonPretty(doc, Serial);
	Serial.println();
	
	// Serialize JSON to file
	if (serializeJson(doc, eepromStream) == 0) {
		Serial.println("Failed to write to EEPROM");
	}

	EEPROM.commit();
}

void hasChanged(){
	saveConfiguration();
}

bool validate() {

	return true;
}

void setup_storage() {
	loadConfiguration();
}

void loop_storage() {
	
}

//=============================================================================