#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>

#include <WifiManager.hpp>

#include <Adafruit_NeoPixel.h>
  #include "index.h"  //Web page header file

WebServer server(80);
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
const char* ssid = "TeleCentro-81e1";
//const char* password = "37226269";
const char* password = "RDMWEJNXMWY2";

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char web[] = "www.google.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;
HTTPClient httpClient;


//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

//===============================================================
// Setup
//===============================================================

void setup(void){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WifiManager* wifimanager = new WifiManager();
  wifimanager.setup();
  pinMode(14, OUTPUT);
  pixels.clear(); 

//ESP32 As access point IP: 192.168.4.1
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP("BalizaIC_A_B", "12345678");    //Password length minimum 8 char

//Comment below code if you are using Access point only
//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
      delay(1000);
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
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

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://api.travis-ci.org/repo/25849455/builds?limit=1"); //Specify the URL
    http.addHeader("Travis-API-Version", "3");
    http.setAuthorization("token sN-LuhyiLh61-Ya2zK-2Xw");
    
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code

      payload = http.getString();
      Serial.print("Status Code: ");
      Serial.println(httpCode);
      //Serial.println(payload);
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
  
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


//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
  getTravisInfo();
  //changeLedLight();
  delay(300);
}