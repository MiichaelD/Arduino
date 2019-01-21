#include <Servo.h> 
#define charComand 5 // characters per comand
#define servoControlPin 8
#define motorSpd 9
#define motorIA 10
#define motorIB 11 
Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 
int spd = 0;    // Variable to store the motor speed
int midspd = 255;
int midpos = 90;
int special = 0;
unsigned long lastCommand;
char signal,car;



void setup() 
{ 
  myservo.attach(servoControlPin);  // attaches the servo on pin 9 to the servo object 
  pinMode(motorSpd,OUTPUT);
  pinMode(motorIA,OUTPUT);
  pinMode(motorIB,OUTPUT);
  Serial3.begin(9600);
  Serial.begin(9600);
  Serial.println("READY ");
  myservo.write(90);
} 

void loop() 
{ 
  if(Serial3.available()>=charComand){
    lastCommand=millis();
    signal=Serial3.read();
    Serial.print(signal);
    switch(signal){
    
    case 'S':
      readInt(special);
      switch(special){
        case 0:    // Parar todo
          Stop(); 
          myservo.write(midpos);
          break;
        
        case 1:    //continua conectado
          lastCommand=millis();          
          break;
      }
      Serial.println(special);
      break;  
      
    case 'V':                   // Vertical Bar
      readInt(spd);
      if (spd == midspd){
        Stop();
      }
      else if (spd >midspd){
        spd-=midspd;
        goForward(spd);
      }
      else{
        spd=midspd-spd;
        goBackward(spd);
      }
      Serial.println(spd);
      break;

    case 'H':        //Movimiento de barra Horizontal
      readInt(pos);
      if (pos == midpos){
         stop_turn();
      }
      else if(pos > midpos){
        pos-=midpos;
        go_right(pos);
      }
      else{
        pos=midpos-pos;
        go_left(pos);
      }
      Serial.println(pos);          
      pos=0;
      break;
      
    case 'L': // New Left bar value
       readInt(midspd);
       Stop();
       Serial.println(midspd);
       break;
    
    case 'R': // New right bar value
      readInt(midpos);
      myservo.write(midpos);
      Serial.println(midpos);
      break;
    }

    delay(1);
  }
  if( (millis() - lastCommand) > 1350){
    Stop();
    myservo.write(midpos);
    lastCommand=millis();
    Serial.println("Connection Lost");
  }
} 


void readInt(int &num){
  num = 0;
  for(int i=0;i<(charComand-1);i++){
    car=Serial3.read();
    num+=(car-48)*(int)(0.5+pow(10,(charComand-2)-i));
   }
}

void goForward(int i){
  digitalWrite(motorIB, LOW);
  digitalWrite(motorIA, HIGH);
  analogWrite(motorSpd,i);
}

void goBackward(int i){
  digitalWrite(motorIA, LOW);
  digitalWrite(motorIB, HIGH);
  analogWrite(motorSpd,i);
}

void Stop(){
  digitalWrite(motorSpd,LOW);
  digitalWrite(motorIA,LOW);
  digitalWrite(motorIB,LOW);
}
