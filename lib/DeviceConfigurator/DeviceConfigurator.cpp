#include <DeviceConfigurator.hpp>


//define your default values here, if there are different values in config.json, they are overwritten.
String ci_url;
String token;

char static_url[255] = "";
char static_token[255] = "";

String AP_SSID = "BALIZA_AP";
String AP_PASSWORD = "untref2019";

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


DeviceConfigurator::DeviceConfigurator(){
    Serial.println("Wifi Manager");
    
}

void DeviceConfigurator::setup(){
    Serial.println("ACA ESTAMOS");
    StaticJsonDocument<200> json;

    //read configuration from FS json
    Serial.println("mounting FS...");

    if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
        //file exists, reading and loading
        Serial.println("reading config file");
        File configFile = SPIFFS.open("/config.json", "r");
        if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DeserializationError error = deserializeJson(json, buf.get());
            // Test if parsing succeeds.
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }else{
            Serial.println("\nparsed json");
            ci_url = json["ci_url"].as<String>();
            token = json["token"].as<String>();
        }
        configFile.close();
        }
    }
    } else {
    Serial.println("failed to mount FS");
    }
    //end read



    // The extra parameters to be configured (can be either global or just in the setup)
    // After connecting, parameter.getValue() will get you the configured value
    // id/name placeholder/prompt default length
    WiFiManagerParameter custom_ci_url("ic_endpoint", "IC Endpoint", static_url, 255);
    WiFiManagerParameter custom_ci_token("ic_token", "Token", static_token, 255);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    //set config save notify callback
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    //set static ip
    //wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //add all your parameters here
    wifiManager.addParameter(&custom_ci_url);
    wifiManager.addParameter(&custom_ci_token);

    //reset settings - for testing
    //wifiManager.resetSettings();

    //set minimu quality of signal so it ignores AP's under that quality
    //defaults to 8%
    //wifiManager.setMinimumSignalQuality();

    //sets timeout until configuration portal gets turned off
    //useful to make it all retry or go to sleep
    //in seconds
    //wifiManager.setTimeout(120);

    //fetches ssid and pass and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    if(!wifiManager.autoConnect(AP_SSID.c_str(), AP_PASSWORD.c_str())) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    //read updated parameters
    ci_url = String(custom_ci_url.getValue());
    token = String(custom_ci_token.getValue());
    
    //save the custom parameters to FS
    if (shouldSaveConfig) {
    Serial.println("saving config");
    StaticJsonDocument<200> json;
    json["ci_url"] = ci_url.c_str();
    json["token"] = token.c_str();
    
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("failed to open config file for writing");
    }

    serializeJson(json, Serial);
    serializeJson(json, configFile);

    configFile.close();
    //end save

    }

    Serial.println("local ip");
    Serial.println(WiFi.localIP());
  
}


void DeviceConfigurator::loop(){ 
    Serial.print("El token es:");
    Serial.println(this->getICToken().c_str());
    
    Serial.print("LA url es:");
    Serial.println(this->getURLEndpoint().c_str());
    delay(100);
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
    delay(1000);
}


bool DeviceConfigurator::isConnected(){
    return (WiFi.status() == WL_CONNECTED);
}


String DeviceConfigurator::getURLEndpoint(){
    return ci_url;
}

String DeviceConfigurator::getICToken(){

    return String(token);
}


void DeviceConfigurator::setAPCredentials(String ssid , String password){
    AP_SSID = String(ssid.c_str());
    AP_PASSWORD = String(password.c_str());

}

void DeviceConfigurator::setCICredentials(String url , String c_token){
    ci_url = url;
    token = c_token;
}

void DeviceConfigurator::cleanFileSystem(){
    SPIFFS.format();
}