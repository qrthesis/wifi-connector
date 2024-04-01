#ifndef WiFiConnector_h
#define WiFiConnector_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WiFiConnector {
public:
    WiFiConnector(HardwareSerial& serial);
    bool connect(const char* ssid, const char* password);
    bool isConnected(); // Declaration of the new method

private:
    SoftwareSerial _esp8266;
    bool sendCommand(const char* command, const char* expectedResponse, int timeout);
    bool waitForResponse(const char* expectedResponse, int timeout); // Declaration added here
    bool _connected; // Variable to store connection status
};

#endif
