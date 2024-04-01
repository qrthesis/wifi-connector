#ifndef WiFiConnector_h
#define WiFiConnector_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WiFiConnector {
public:
    WiFiConnector(int esp8266TxPin, int esp8266RxPin);
    bool connect(const char* ssid, const char* password);

private:
    SoftwareSerial _esp8266;
    bool sendCommand(const char* command, const char* expectedResponse, int timeout);
    bool waitForResponse(const char* expectedResponse, int timeout); // Declaration added here
};

#endif
