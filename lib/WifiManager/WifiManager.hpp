#ifndef WifiManager_HPP
#define WifiManager_HPP

#include <WifiManager.hpp>
#include "Arduino.h"
#include <IotWebConf.h>
#include <HTTPClient.h>


class WifiManager
{
private:
    IotWebConf* iotWebConf;
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
    boolean formValidator();


};
 
#endif