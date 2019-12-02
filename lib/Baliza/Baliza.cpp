#include <Arduino.h>
#include <Baliza.hpp>
#include <WifiManager.hpp>


Baliza::Baliza(){
    lightManager = new LightManager();
    wifiManager = new WifiManager();

}

Baliza::~Baliza(){

}

void Baliza::setup(){
    //Instanciamos todas las clases que vamos a usar, y las que usan las nuestras (ahi las librerias externas)
    wifiManager->setup();
    
}

void Baliza::loop(){
    //Aca ponemos lo mismo que en loop del main y el main solo tiene un baliza->loop

    delay(1000);

}