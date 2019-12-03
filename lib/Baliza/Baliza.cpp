#include <Arduino.h>
#include <Baliza.hpp>
#include <WifiManager.hpp>
#include <LightManager.hpp>
#include <ApiConfigurator.hpp>


Baliza::Baliza(){
    lightManager = new LightManager();
    //wifiManager = new WifiManager();
    apiConfigurator = new ApiConfigurator();
}

Baliza::~Baliza(){

}

void Baliza::setup(){
    //Instanciamos todas las clases que vamos a usar, y las que usan las nuestras (ahi las librerias externas)
    //wifiManager->setup();
    
    apiConfigurator->setUrl(String("https://api.travis-ci.org/repo/25849455/builds?limit=1"));
    apiConfigurator->setToken(String("token sN-LuhyiLh61-Ya2zK-2Xw"));
    apiConfigurator->getTravisInfo();
    
}

void Baliza::loop(){
    //Aca ponemos lo mismo que en loop del main y el main solo tiene un baliza->loop
    delay(1000);
    apiConfigurator->getTravisInfo();
}


void Baliza::setBuildState(String value){
    state = apiConfigurator->getState();
}

String Baliza::getBuildState(){
    return state;
}

void Baliza::checkActualState(){
    int blink = 0;
    String actualState = apiConfigurator->getState();
    if(!actualState.equals(apiConfigurator->getPreviousState())){
        blink = 3;
    }

    if (state.equals("passed")){
        lightManager->setLight(0, 255, 0, blink);
    }
    else if (state.equals("started")){
        lightManager->setLight(255, 255, 0, blink);
    }
    else if(state.equals("failed")){
        lightManager->setLight(255, 0, 0, blink);
    }
    else if(state.equals("canceled")){
        lightManager->setLight(192, 192, 192, blink);
    }
}