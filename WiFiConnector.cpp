#include "WiFiConnector.h"

WiFiConnector::WiFiConnector(HardwareSerial& serial) : _esp8266() {
    _esp8266.begin(9600);
}

bool WiFiConnector::connect(String ssid, String password) {
    _esp8266.println("AT+RST");
    if (!waitForResponse("OK", 1000)) return false;
    
    if (!sendCommand("AT+CWMODE=1", "OK", 1000)) return false;
    
    if (!sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", "OK", 2000)) return false; // Increased timeout to 10 seconds, adjust if necessary
    
    return true;
}

bool WiFiConnector::sendCommand(String command, String expectedResponse, int timeout) {
    _esp8266.println(command);
    return waitForResponse(expectedResponse, timeout);
}

bool WiFiConnector::waitForResponse(String expectedResponse, int timeout) {
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

bool WiFiConnector::isConnected() {
    // Check if the ESP8266 is connected to the WiFi network
    _esp8266.println("AT+CWJAP?");
    return waitForResponse("OK", 1000); // Assuming "OK" means connected in the response
}
