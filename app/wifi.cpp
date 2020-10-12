#include "wifi.hpp"

void setup_wifi() {

    Config cfg = sysCfg.get();

    WiFi.mode(WIFI_STA);
    WiFi.begin(cfg.wifi_ssid.c_str(), cfg.wifi_pwd.c_str());

    Serial.println("Trying to connect...");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed!");
        delay(5000);
        return;
        // ESP.restart(); // TODO: REMOVER ISSO DAQUI, QUANDO TIVER OBTENDO A CONFIG DA ENTRADA
    }
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop_wifi() {

}