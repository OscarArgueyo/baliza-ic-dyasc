#ifndef Baliza_HPP
#define Baliza_HPP

#include "Arduino.h"
#include "LightManager.hpp"
#include "WifiManager.hpp"
#include "ApiConfigurator.hpp"
//#include "CIManager.hpp"

class Baliza
{
private:
    LightManager* lightManager;
    WifiManager* wifiManager;
    ApiConfigurator* apiConfigurator;
    String state;
    String thingName = "BALIZA";
    String wifiInitialApPassword = "dyasc2019";


public:

    Baliza();
    ~Baliza();
    void setup();
    void loop();
    void checkActualState();
    void getEstadoBuild(String SSID , String PASSWORD);
    void actualizarEstadoBuild();
    void setCIManager();
    void setWifiSettings();
    String getBuildState();
    void setBuildState(String value);

};
 
#endif