#include <Arduino.h>
#include <Baliza.hpp>
#include <DeviceConfigurator.hpp>
#include <LightManager.hpp>
#include <ApiConfigurator.hpp>


Baliza::Baliza(){
    lightManager = new LightManager();
    deviceConfigurator = new DeviceConfigurator();
    apiConfigurator = new ApiConfigurator();
}

Baliza::~Baliza(){

}

void Baliza::setup(){
    deviceConfigurator->setup();
    
    String token = deviceConfigurator->getICToken();
    String url = deviceConfigurator->getURLEndpoint();

    if(!(url.equals("") && token.equals(""))){
        apiConfigurator->setUrl(url);
        apiConfigurator->setToken(token);
    }
    //apiConfigurator->getTravisInfo();
    
}

void Baliza::loop(){
    //Aca ponemos lo mismo que en loop del main y el main solo tiene un baliza->loop
    delay(1000);
    if(deviceConfigurator->isConnected()){
        apiConfigurator->getTravisInfo();
        this->checkActualState();
    }
    
    // Serial.print("url api config");
    // Serial.print(apiConfigurator->getUrl());
    // Serial.print("url api config");
    // Serial.print(deviceConfigurator->getURLEndpoint());

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
    Serial.print("ACA VA EL STATE");
    Serial.print(actualState);
    if(!actualState.equals(apiConfigurator->getPreviousState())){
        blink = 3;
    }
    if (actualState.equals("passed")){
        lightManager->setLight(0, 255, 0, blink);
    }
    else if (actualState.equals("started")){
        lightManager->setLight(255, 255, 0, blink);
    }
    else if(actualState.equals("failed")){
        lightManager->setLight(255, 0, 0, blink);
    }
    else if(actualState.equals("canceled")){
        lightManager->setLight(192, 192, 192, blink);
    } 
    else{
        // DEFINIR CUAL SERIA ESTE ESTADO CUANDO NO ES NINGUO DE LOS ANTERIORES
        lightManager->setLight(19, 19, 19, 2);
    }
}