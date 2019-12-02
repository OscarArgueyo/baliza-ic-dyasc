#ifndef Baliza_HPP
#define Baliza_HPP

#include "Arduino.h"
#include "LightManager.hpp"
#include "WifiManager.hpp"
//#include "CIManager.hpp"

class Baliza
{
private:
    LightManager* lightManager;
    WifiManager* wifiManager;
    //CIManager ciManager;
    String status_passed = "passed";
    String status_started = "started";
    String status_failed = "failed";
    String status_canceled = "canceled";
    String thingName = "BALIZA";
    String wifiInitialApPassword = "dyasc2019";


public:

    Baliza();
    ~Baliza();
    void setup();
    void loop();
    void getEstadoBuild(String SSID , String PASSWORD);
    void actualizarEstadoBuild();
    void setCIManager();
    void setWifiSettings();

};
 
#endif