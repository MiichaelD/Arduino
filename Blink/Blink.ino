/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 #include "AddInts.h" 
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define led 13

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  AddInts addInts;
  addInts.add2ints(5, 5);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Encendido\t- 1");
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("Apagado \t- 0");
  delay(1000);               // wait for a second
}
