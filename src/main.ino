#include "WiFi.h"
#include "Baliza.hpp"
 
const char* ssid = "IplanLiv-181329-2.4GHz";
const char* password =  "37226269";

Baliza baliza = Baliza();
void setup() {

  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  baliza.setup();
}
 
void loop() {
    baliza.loop();
}