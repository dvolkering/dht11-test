#include <dht.h>

// The temperature sensor
#define dht_dpin A0

dht DHT;

// Set debug
bool debug = false;

// Variables
const int onOffSwitch =  12; // relay
int start = 0;
int temphigh = 38; // Temperature to switch on
int templow = temphigh - 3; // Temperature to switch off

void setup(){
  pinMode(onOffSwitch, OUTPUT);
  
  Serial.begin(9600);
  delay(300);//Let system settle
  delay(1000);//Wait rest of 1000ms recommended delay before accessing sensor

  if(debug == true) {
    // Use reasonable debug temperatures
    temphigh = 18;
    templow = temphigh - 3;
  }
}

void loop(){
    DHT.read11(dht_dpin);
    
    // Print the temperature to the console for debugging
    if(debug == true) {
      Serial.print("temperature = ");
      Serial.print(DHT.temperature); 
      Serial.println("C  ");
    }

    // Put the fans on when the temperature is reached
    if(DHT.temperature >= temphigh & start == 0) {
      digitalWrite(onOffSwitch, LOW);
      Serial.println("ON");
      start = 1;
    }

    // Put the fans off when the (low) temperature is reached
    if(DHT.temperature < templow) {
      digitalWrite(onOffSwitch, HIGH);
      Serial.println("OFF");
      start = 0;
    }
    
    delay(5500); //Minimum time is 2500ms for accessing sensor
}
