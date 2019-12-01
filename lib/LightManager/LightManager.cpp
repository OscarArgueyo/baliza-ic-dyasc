#include <LightManager.hpp>
#include <Adafruit_NeoPixel.h>

LightManager::LightManager()
{
    pinMode(PIN, OUTPUT);
    pixels  = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
}

LightManager::~LightManager()
{
}

void LightManager::setLight(int r , int g, int b , int blink_times){

  if(blink_times > 0){
    
    pixels->clear();   
    while(blink_times > 0){
        for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
          pixels->setPixelColor(i, pixels->Color(r, g, b));
          pixels->show();   // Send the updated pixel colors to the hardware.
          delay(10); // Pause before next pass through loop 
        }
      delay(1000);
      blink_times=blink_times-1;
      Serial.println("Parpadee uno"); 
    }    
  }

  delay(1000);
}
