#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include "SPIFFS.h"
#include <Arduino.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <WiFi.h>          

//needed for library
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>


#ifndef DeviceConfigurator_HPP
#define DeviceConfigurator_HPP

class DeviceConfigurator
{
private:
public:
    DeviceConfigurator();
    void setAPCredentials(String ssid , String password);
    void setCICredentials(String url , String token);
    void setup();
    void loop();
    void cleanFileSystem();
    bool isConnected();
    String getURLEndpoint();
    String getICToken();
};
 
#endif