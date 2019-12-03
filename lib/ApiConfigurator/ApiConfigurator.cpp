#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ApiConfigurator.hpp>

#define TRAVISHEADER "Travis-API-Version"

ApiConfigurator::ApiConfigurator(){
    httpClient = new HTTPClient();
    previousState = "";
    Serial.println("ACAAAAAAAA");
}

void ApiConfigurator::getTravisInfo(){
    String url = this->getUrl();
    String token = this->getToken();
    Serial.println(url);
    Serial.println(token);


    httpClient->begin(url); //Specify the URL
    httpClient->addHeader(TRAVISHEADER, "3");
    httpClient->setAuthorization(token.c_str());
    
    int httpCode = httpClient->GET();  //Make the request

    if (httpCode == 200) { //Check for the returning code

        String payload = httpClient->getString();
        Serial.print("Status Code: ");
        Serial.println(httpCode);
        //Serial.println(payload);
        // Allocate the JSON document
        // Use arduinojson.org/v6/assistant to compute the capacity.
        const size_t capacity = JSON_ARRAY_SIZE(0) + 2*JSON_ARRAY_SIZE(1) + 4*JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(23) + 1540;
        
        DynamicJsonDocument doc(capacity);

        // Parse JSON object
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            this->setApiResponseError(true);
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }

        JsonObject builds_0 = doc["builds"][0];

        const char* builds_0_state = builds_0["state"]; // "passed"
        // Extract values

        Serial.println(F("Estado del ultimo build:"));
        Serial.println(builds_0_state);

        
        if(previousState.equals("")){
        previousState = String(builds_0_state);
        }
        this->setState(builds_0_state);
    }
    else {
        Serial.println("Error on HTTP request");
    }

    httpClient->end(); //Free the resources
}

String ApiConfigurator::getUrl(){
    return url;
}

void ApiConfigurator::setUrl(String value){
    url = value;
}

String ApiConfigurator::getToken(){
    return token;
}

void ApiConfigurator::setToken(String value){
    token = value;
}

bool ApiConfigurator::getApiResponseError(){
    return apiResponseError;
}

void ApiConfigurator::setApiResponseError(bool value){
    apiResponseError = value;
}

void ApiConfigurator::setState(String value){
    previousState = state;
    state = value;
}

String ApiConfigurator::getState(){
    return state;
}

String ApiConfigurator::getPreviousState(){
    return previousState;
}