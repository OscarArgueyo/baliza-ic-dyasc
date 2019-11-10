#ifndef WifiManager_HPP
#define WifiManager_HPP

#include "Arduino.h"

class WifiManager
{
private:
    int m_year;
    int m_month;
    int m_day;
 
public:
    WifiManager();
 
    void setup();
    void setConnectionCredentials(String SSID , String PASSWORD);
    int getStateConnection();
    int getSSID();

};
 
#endif