#ifndef LightManager_HPP
#define LightManager_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 14
#define NUMPIXELS 16 

class LightManager
{
private:
    Adafruit_NeoPixel* pixels;
    String color;
public:
    LightManager(/* args */);
    ~LightManager();
    void setLight(int r, int g, int b , int blink_times);
    void setColor(String value);
    String getColor();
};




#endif