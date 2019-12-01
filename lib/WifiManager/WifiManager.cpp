#include <Arduino.h>
#include <WifiManager.hpp>

/*
WifiManager::WifiManager(){
    Serial.println("Wifi Manager");
}

void WifiManager::setup(){

    Serial.println("ACA ESTAMOS");
    IotWebConfSeparator separator1 = IotWebConfSeparator("Servidor de Integracion Continua");
    IotWebConfParameter icEndpointParam = IotWebConfParameter("Endpoint API REST Integracion Continua ", "icEndpointParam", icEndpointParamValue, STRING_LEN);
    // -- We can add a legend to the separator
    IotWebConfSeparator separator2 = IotWebConfSeparator("Autenticación del Repositorio de IC");
    IotWebConfParameter iCServerTokenParam = IotWebConfParameter("Token de Autenticación", "iCServerTokenParam", iCServerTokenParamValue, STRING_LEN);

    IotWebConfSeparator separator3 = IotWebConfSeparator("Configuración del Dispositivo");
    IotWebConfParameter pollingFrequencyParam = IotWebConfParameter("Periodo de Actualización (en segundos)", "pollingFrequencyParam", pollingFrequencyParamValue, NUMBER_LEN, "number", "1..3600", NULL, "min='1' max='3600' step='1'");

    iotWebConf.setStatusPin(STATUS_PIN);
    iotWebConf.setConfigPin(CONFIG_PIN);
    iotWebConf.addParameter(&icEndpointParam);
    iotWebConf.addParameter(&separator1);
    iotWebConf.addParameter(&iCServerTokenParam);
    iotWebConf.addParameter(&separator3);
    iotWebConf.addParameter(&pollingFrequencyParam);
    iotWebConf.setConfigSavedCallback(&configSaved);
    iotWebConf.setFormValidator(&formValidator);
    iotWebConf.getApTimeoutParameter()->visible = true;

    // -- Initializing the configuration.
    boolean validConfig = iotWebConf.init();
    if (!validConfig)
    {
        icEndpointParamValue[0] = '\0';
        pollingFrequencyParamValue[0] = '4';
    }

    // -- Set up required URL handlers on the web server.
    server.on("/", handleRoot);
    server.on("/config", []{ iotWebConf.handleConfig(); });
    server.onNotFound([](){ iotWebConf.handleNotFound(); });

    initial_state_light();
    iotWebConf.doLoop();

}

void WifiManager::handleRoot()
{
    // -- Let IotWebConf test and handle captive portal requests.
    if (iotWebConf.handleCaptivePortal())
    {
    // -- Captive portal request were already served.
    return;
    }

    // -- HTML page fragments
    String config_page  = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
    config_page += "<style>.de{background-color:#ffaaaa;} .em{font-size:0.8em;color:#bb0000;padding-bottom:0px;} .c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} fieldset{border-radius:0.3rem;margin: 0px;}</style>";
    config_page += "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
    config_page += "</head><body>";
    config_page += "<div style='text-align:left;display:inline-block;min-width:260px;'>";
    config_page += "<div>Haga click <a href='/config'>aqui</a> para configurar el dispositivo.</div>";
    config_page+= "</div></body></html>";

    /*
    String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
    s += "<title>IotWebConf 03 Custom Parameters</title></head><body>Hello world!";
    s += "<ul>";
    s += "<li>String param value: ";
    s += stringParamValue;
    s += "<li>Int param value: ";
    s += atoi(intParamValue);
    s += "<li>Float param value: ";
    s += atof(floatParamValue);
    s += "</ul>";
    s += "Go to <a href='config'>configure page</a> to change values.";
    s += "</body></html>\n";
    

    server.send(200, "text/html", config_page);
}

void WifiManager::configSaved()
{
    Serial.println("Configuracion del dispositivo actualizada.");
}

void WifiManager::wifiConnected()
{
    Serial.println("Dispositivo conectado a wifi");
    //WIFI_SUCCESSFUL_CONNECTION = true;
}

void WifiManager::loop(){
    iotWebConf.doLoop();
}
*/