#ifndef WiFiConnector_h
#define WiFiConnector_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WiFiConnector {
public:
    WiFiConnector(HardwareSerial& serial);
    bool connect(String ssid, String password);
    bool isConnected(); // Declaration of the new method

private:
    HardwareSerial& _esp8266;
    bool sendCommand(String command, String expectedResponse, int timeout);
    bool waitForResponse(String expectedResponse, int timeout); // Declaration added here
    bool _connected; // Variable to store connection status
};

#endif
