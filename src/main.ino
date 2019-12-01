#include <Baliza.hpp>


Baliza baliza;

void setup() 
{  
    Serial.begin(115200); 
    while (!Serial){
    }
    
    baliza.setup();  
}

void loop() 
{   
    baliza.loop();
  
}