#include <Arduino.h>
#include <ArduinoJson.h>
#include <IotWebConf.h>
#include <HTTPClient.h>
#include <WifiManager.hpp>

#include <Adafruit_NeoPixel.h>


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

/**/

//Enter your WiFi SSID and PASSWORD
//const char* ssid = "IplanLiv-181329-2.4GHz";
//const char* ssid = "TeleCentro-81e1";
//const char* password = "37226269";
//const char* password = "RDMWEJNXMWY2";

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "BALIZA";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "dyasc2019";

boolean WIFI_SUCCESSFUL_CONNECTION = false;

#define STRING_LEN 255
#define NUMBER_LEN 32

// -- Configuration specific key. The value should be modified if config structure was changed.
#define CONFIG_VERSION "dem2"

// -- When CONFIG_PIN is pulled to ground on startup, the Thing will use the initial
//      password to buld an AP. (E.g. in case of lost password)
#define CONFIG_PIN 17

// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
#define STATUS_PIN LED_BUILTIN

// -- Callback method declarations.
void configSaved();
boolean formValidator();

DNSServer dnsServer;
WebServer server(80);

char icEndpointParamValue[STRING_LEN];
char iCServerTokenParamValue[STRING_LEN];
char pollingFrequencyParamValue[NUMBER_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
IotWebConfSeparator separator1 = IotWebConfSeparator("Servidor de Integracion Continua");
IotWebConfParameter icEndpointParam = IotWebConfParameter("Endpoint API REST Integracion Continua ", "icEndpointParam", icEndpointParamValue, STRING_LEN);
// -- We can add a legend to the separator
IotWebConfSeparator separator2 = IotWebConfSeparator("Autenticación del Repositorio de IC");
IotWebConfParameter iCServerTokenParam = IotWebConfParameter("Token de Autenticación", "iCServerTokenParam", iCServerTokenParamValue, STRING_LEN);

IotWebConfSeparator separator3 = IotWebConfSeparator("Configuración del Dispositivo");
IotWebConfParameter pollingFrequencyParam = IotWebConfParameter("Periodo de Actualización (en segundos)", "pollingFrequencyParam", pollingFrequencyParamValue, NUMBER_LEN, "number", "1..3600", NULL, "min='1' max='3600' step='1'");


/**
 * Handle web requests to "/" path.
 */
void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }

  // -- HTML page fragments
  String config_page  = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
  config_page += "<styles>.de{background-color:#ffaaaa;} .em{font-size:0.8em;color:#bb0000;padding-bottom:0px;} .c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} fieldset{border-radius:0.3rem;margin: 0px;}</styles>";
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
  */

  server.send(200, "text/html", config_page);
}

void configSaved()
{
  Serial.println("Configuracion del dispositivo actualizada.");
}

void wifiConnected()
{
  Serial.println("Dispositivo conectado a wifi");
  WIFI_SUCCESSFUL_CONNECTION = true;
}

boolean formValidator()
{
  Serial.println("Validating form.");
  boolean valid = true;

  int l = server.arg(icEndpointParam.getId()).length();
  if (l < 3)
  {
    icEndpointParam.errorMessage = "Url invalida!";
    valid = false;
  }

  return valid;
}

void changeLedLight(int r , int g, int b){

   // Set all pixel colors to 'off'
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(10); // Pause before next pass through loop
  }

  delay(1000);
}

void getTravisInfo(){

  String payload;
  HTTPClient http;
  http.begin(icEndpointParamValue); //Specify the URL
  http.addHeader("Travis-API-Version", "3");
  String token_str = "token ";
  token_str += String(iCServerTokenParamValue);
  Serial.println(token_str);
  http.setAuthorization(token_str.c_str());
  
  int httpCode = http.GET();  //Make the request

  if (httpCode == 200) { //Check for the returning code

    payload = http.getString();
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
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    JsonObject builds_0 = doc["builds"][0];
    const char* builds_0_state = builds_0["state"]; // "passed"
    long builds_0_id = builds_0["id"]; // 595914427 
    // Extract values

    Serial.println(F("Estado del ultimo build:"));
    Serial.print(builds_0_id);
    Serial.print(":");
    Serial.println(builds_0_state);
    String status_passed = "passed";
    String status_started = "started";
    String status_failed = "failed";
    String status_canceled = "canceled";
    
    if(status_passed.equals(builds_0_state)){
      changeLedLight(0, 255, 0);
      Serial.println("Esta en passed!");
    }

    if(status_started.equals(builds_0_state)){
      changeLedLight(255,255,0);
      Serial.println("Esta en started!");
    }

    if(status_canceled.equals(builds_0_state)){
      changeLedLight(192,192,192);
      Serial.println("Esta en canceled!");
    }
    
    if(status_failed.equals(builds_0_state)){
      changeLedLight(255,0,0);
      Serial.println("Esta en failed!");
    }
  }
  else {
    Serial.println("Error on HTTP request");
  }

  http.end(); //Free the resources
}



void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

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
  }

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });

  Serial.println("Lista la baliza.");

  pinMode(PIN, OUTPUT);
  pixels.clear(); 
}

void loop() 
{
  // -- doLoop should be called as frequently as possible.

  iotWebConf.doLoop();

  getTravisInfo();
  //changeLedLight();
  String delay_str = String(pollingFrequencyParamValue);
  //iotWebConf.delay(delay_str.toInt()*1000);
  delay(1000);
}