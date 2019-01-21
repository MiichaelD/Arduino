/*
This arduino app is to controll a car with 2 DC motors using a
double H-Bridge circuit to control both motors in direction and
speed (forward, reverse) with the use of a bluetooth
connection with your android device (app called BluIno). 
This app uses the PWM (Pulse-width modulation) to control the
power that the motors will use. 

Programer:       Michael Duarte - michael.duarte@hotmail.com
Version:         1.0 for Arduino MEGA2560
Date:            October 2012
*/
#define charComand 5 // characters per comand
#define servoControlPin 8
#define motorSpd 9
#define motorIA 10
#define motorIB 11 
//#define motor2Spd 4
#define motor2IA 5
#define motor2IB 6 
// a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 
int spd = 0;    // Variable to store the motor speed
int midspd = 255;
int midpos = 255;
int special = 0;
unsigned long lastCommand;
char signal,car;

void setup() 
{ 
  pinMode(motorSpd,OUTPUT);
  pinMode(motorIA,OUTPUT);
  pinMode(motorIB,OUTPUT);
 // pinMode(motor2Spd,OUTPUT);
  pinMode(motor2IA,OUTPUT);
  pinMode(motor2IB,OUTPUT);
  Serial3.begin(115200);
  Serial.begin(115200);
  Serial.println("READY ");
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
          Stop_all();
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
      else if (spd > midspd){
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
         Stop_turn();
      }
      else if(pos > midpos){
       // pos-=midpos;
       goRight();
      }
      else{
        //pos=midpos-pos;
        goLeft();
      }
      Serial.println(pos);
      break;
      
    case 'L': // New Left bar value
       readInt(midspd);
       midspd/=2;
       Stop();
       Serial.println(midspd);
       break;
    
    case 'R': // New right bar value
      readInt(midpos);
      midpos/=2;
      Stop_turn();
      Serial.println(midpos);
      break;
    }

    delay(1);
  }
  if( (millis() - lastCommand) > 1350){
    Stop_all();
    lastCommand=millis();
    Serial3.flush();
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

void goRight()//(int i)
{
  digitalWrite(motor2IB, LOW);
  digitalWrite(motor2IA, HIGH);
  //analogWrite(motor2Spd,i);
}

void goLeft()//(int i)
{
  digitalWrite(motor2IA, LOW);
  digitalWrite(motor2IB, HIGH);
  //analogWrite(motor2Spd,i);
}

void Stop_all(){
  Stop();
  Stop_turn();
}

void Stop(){
  digitalWrite(motorSpd,LOW);
  digitalWrite(motorIA,LOW);
  digitalWrite(motorIB,LOW);
}

void Stop_turn(){
  //digitalWrite(motor2Spd,LOW);
  digitalWrite(motor2IA,LOW);
  digitalWrite(motor2IB,LOW);
}
