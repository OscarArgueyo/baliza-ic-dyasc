#ifndef WifiManager_HPP
#define WifiManager_HPP

#include "Arduino.h"
#include <IotWebConf.h>
#include <HTTPClient.h>
#include <WifiManager.hpp>

class WifiManager
{
private:

public:
    WifiManager();
 
    void setup();
    void loop();
    void setConnectionCredentials(String SSID , String PASSWORD);
    int getStateConnection();
    int getSSID();
    void handleRoot();
    void configSaved();
    void wifiConnected();

};
 
#endif