#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
char signal,car;
boolean first;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial3.begin(9600);
  Serial.begin(9600);
  Serial.print("READY ");
  first=false;
  myservo.write(90);
} 

void loop() 
{ 
  if(!first){
  Serial.println("GO");
  first=true;
  }
  if(Serial3.available()>3){
   signal=Serial3.read();
    switch(signal){
    case 'V':
    case 'H':
          for(int i=0;i<3;i++){
          car=Serial3.read();
          pos+=(car-48)*pow(10,2-i);
          }
          break;
  }
  Serial.print(signal);
  Serial.println(pos);
  myservo.write(pos);
  delay(1);
    pos=0;
  }
} 
