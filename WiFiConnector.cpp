#include "WiFiConnector.h"

WiFiConnector::WiFiConnector(int esp8266TxPin, int esp8266RxPin) : _esp8266(esp8266TxPin, esp8266RxPin) {
    _esp8266.begin(9600);
}

bool WiFiConnector::connect(const char* ssid, const char* password) {
    _esp8266.println("AT+RST");
    if (!waitForResponse("OK", 1000)) return false;
    
    if (!sendCommand("AT+CWMODE=1", "OK", 1000)) return false;
    
    char cmd[100]; // Adjust the size according to your requirement
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"", ssid, password);
    if (!sendCommand(cmd, "OK", 10000)) return false; // Increased timeout to 10 seconds, adjust if necessary
    
    return true;
}

bool WiFiConnector::sendCommand(const char* command, const char* expectedResponse, int timeout) {
    _esp8266.println(command);
    return waitForResponse(expectedResponse, timeout);
}

bool WiFiConnector::waitForResponse(const char* expectedResponse, int timeout) {
    unsigned long startTime = millis();
    char responseBuffer[100]; // Adjust the size according to your requirement
    int responseLength = strlen(expectedResponse);

    while (millis() - startTime < timeout) {
        if (_esp8266.available() > 0) {
            // Read response from ESP8266
            _esp8266.readBytes(responseBuffer, responseLength);
            responseBuffer[responseLength] = '\0'; // Null-terminate the string
            
            if (strcmp(responseBuffer, expectedResponse) == 0) {
                return true; // Response matches
            }
        }
    }
    return false; // Timeout occurred
}
