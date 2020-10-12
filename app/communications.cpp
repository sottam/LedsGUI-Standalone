#include "communications.hpp"

String GET_STTM_VERSION = "GET_STTM_VERSION";

String GET_UNIX_TIME = "GET_UNIX_TIME";
String SET_UNIX_TIME = "SET_UNIX_TIME";
String SET_WIFI_CREDENTIALS = "SET_WIFI_CREDENTIALS";
String PARSE_ERROR = "PARSE_ERROR";

String generateResponse(StaticJsonDocument<1024> doc) {
	String response;
	#ifdef PRETTY_RESPONSE
		serializeJsonPretty(doc, response);
	#else
		serializeJson(doc, response);
	#endif
	return response;
}

void process_SERIAL_data(const char* buffer)
{
	String msg2parse = String(buffer);
	
	StaticJsonDocument<1024> serial_msg;
	DeserializationError error = deserializeJson(serial_msg, msg2parse);

	String CMD;
	String MESSAGE_TYPE;

	if(!error) { 
		CMD = serial_msg["CMD"].as<String>();
		MESSAGE_TYPE = serial_msg["MESSAGE_TYPE"].as<String>();
	} else {
		CMD = PARSE_ERROR;
		MESSAGE_TYPE = PARSE_ERROR;
	}

	String response;
	StaticJsonDocument<1024> jsonResponse;

    if (CMD.equals(GET_STTM_VERSION)) {
		jsonResponse["CMD"] = CMD;
		jsonResponse["MESSAGE_TYPE"] = "RESPONSE";
		jsonResponse["VERSION"] = String(STTM_VERSION);

		response = generateResponse(jsonResponse);
    }
    else if (CMD.equals(GET_UNIX_TIME)) {
    
	}
    else if (CMD.equals(SET_UNIX_TIME)) {

    }
    else if (CMD.equals(SET_WIFI_CREDENTIALS)) {
		Config config = sysCfg.get();

		config.wifi_ssid = serial_msg["SSID"].as<String>();
		config.wifi_pwd = serial_msg["PWD"].as<String>();

		sysCfg.set(config);

		jsonResponse["CMD"] = CMD;
		jsonResponse["MESSAGE_TYPE"] = "RESPONSE";
		jsonResponse["STATUS"] = "OK. REBOTTING...";

		response = generateResponse(jsonResponse);
		ESP.restart();
    }
	else if(CMD.equals(PARSE_ERROR)) {
		jsonResponse["MESSAGE_TYPE"] = "RESPONSE";
		jsonResponse["ERROR"] = "Bad Message. Check if it is a valid JSON.";

		response = generateResponse(jsonResponse);
	}
	else
	{
		jsonResponse["MESSAGE_TYPE"] = "RESPONSE";
		jsonResponse["ERROR"] = "Command not supported.";

		response = generateResponse(jsonResponse);
	}
	
	Serial.println(response);
}

void setup_communications() {
	Serial.begin(115200); 
  	Serial.println("ESP32 has just initialized.");
}

void loop_communications() {
	if (Serial.available()) {
		char c = char(Serial.read());
		processSerialIncomingChar(c);
  	}
}

void processSerialIncomingChar(const char inChar)
{
    const int max_size = 1024;

	static char input_line[max_size];
	static unsigned int input_pos = 0;
	static bool messageStarted = false;

	switch (inChar)
	{
	case MESSAGE_START:
		if (messageStarted) input_pos = 0;
		else {
			messageStarted = true;
		}

		break;
	case MESSAGE_END:   // end of message
		input_line[input_pos++] = '\0';
		process_SERIAL_data(input_line);
		// reset buffer for next time
		messageStarted = false;
		input_pos = 0;
		break;

	default:
		// keep adding if not full ... allow for terminating null byte
		if (messageStarted && input_pos < (max_size - 1))
			input_line[input_pos++] = inChar;
		else if (input_pos == (max_size - 1))
			input_pos = 0;
		break;
	}
}