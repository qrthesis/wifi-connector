#include "WiFiConnector.h"

WiFiConnector::WiFiConnector(int esp8266TxPin, int esp8266RxPin) : _esp8266(esp8266TxPin, esp8266RxPin) {
    _esp8266.begin(9600);
}

bool WiFiConnector::connect(const char* ssid, const char* password) {
    _esp8266.println("AT+RST");
    if (!sendCommand("AT", "OK", 1000)) return false;
    if (!sendCommand("AT+CWMODE=1", "OK", 1000)) return false;
    if (!sendCommand("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"", "OK", 10000)) return false;
    return true;
}

bool WiFiConnector::sendCommand(const char* command, const char* expectedResponse, int timeout) {
    _esp8266.println(command);
    unsigned long startTime = millis();
    while (millis() - startTime < timeout) {
        if (_esp8266.find(expectedResponse)) {
            return true;
        }
    }
    return false;
}
