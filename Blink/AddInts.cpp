#include "AddInts.h" 
#include <Arduino.h>

int AddInts::add2ints(int a, int b) {
  Serial.print("Wasaaa:\t");
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(a + b); 
}
