/*
Bluetooth relay 

Programer:       Michael Duarte - michael.duarte@hotmail.com
Version:         1.0 for Arduino UNO
Date:            October 2012
*/

#define relay 10
unsigned long lastOn;
boolean on;

void setup() 
{ 
  pinMode(relay,OUTPUT);
  Serial.begin(115200);
  Serial.println("READY ");
  digitalWrite(relay,HIGH);
  on=false;
} 

void loop() 
{ 
  if(Serial.available()){
    switch(Serial.read()){
    
    case '0':
      Serial.println("Stop"); 
      on=false;
    break;
      
    case '1':
      if( (on = !on))
        lastOn=millis()+3600000;
      Serial.println(on);
      break;
      
    default :
      lastOn=millis();
      Serial.println("Forw"); 
      on=true;
      break;         
    }
  }
  
  if(millis()-lastOn > 250)
    on=false;
  
  digitalWrite(relay,(on)?LOW:HIGH);

  delay(10);

} 
