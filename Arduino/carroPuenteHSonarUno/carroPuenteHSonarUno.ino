/*
This arduino app is to controll a car with 2 DC motors using a
double H-Bridge circuit to control both motors in direction and
speed (forward, reverse) with the use of a bluetooth
connection with your android device (app called BluIno). 
This app uses the PWM (Pulse-width modulation) to control the
power that the motors will use. 

Programer:       Michael Duarte - michael.duarte@hotmail.com
Version:         1.0 for Arduino UNO
Date:            October 2012
*/
#define charComand 5 // characters per comand



///Sonar pin
#define ultraSoundSignal 3
double distance;


//L298N H-Bridge pins
#define motorSpd 9
#define motorIA 10
#define motorIB 11 
//#define motor2Spd 4
#define motor2IA 5
#define motor2IB 6 

////Direction states:
#define forwState 1
#define stopState 0
#define backState -1

int pos = 0;    // variable to store the servo position 
int spd = 0;    // Variable to store the motor speed
int midspd = 255;
int midpos = 255;
int special = 0;
int Direction;
boolean usesSonar;
unsigned long lastCommand,lastSonar;
char signal,car;

void setup() 
{ 
  pinMode(motorSpd,OUTPUT);
  pinMode(motorIA,OUTPUT);
  pinMode(motorIB,OUTPUT);
 // pinMode(motor2Spd,OUTPUT);
  pinMode(motor2IA,OUTPUT);
  pinMode(motor2IB,OUTPUT);
  Serial.begin(115200);
  Serial.println("READY ");
  Direction=0;
  usesSonar=false;
  lastSonar = millis();
  /////////////debug/////
  pinMode(12,OUTPUT); 
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);

} 

void loop() 
{ 
  if(Serial.available()>=charComand){
    lastCommand=millis();
    signal=Serial.read();
    //Serial.print(signal);
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
          
        case 8:
          if((usesSonar=!usesSonar))
            digitalWrite(13,HIGH);
          else
            digitalWrite(13,LOW);
          
          break;
      }
      //Serial.println(special);
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
      //Serial.println(spd);
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
      //Serial.println(pos);
      break;
      
    case 'L': // New Left bar value
       readInt(midspd);
       midspd/=2;
       Stop();
       //Serial.println(midspd);
       break;
    
    case 'R': // New right bar value
      readInt(midpos);
      midpos/=2;
      Stop_turn();
      //Serial.println(midpos);
      break;
    }

    
  }
  if( (millis() - lastCommand) > 1350){/// Check if bluetooth connection is still OK
    Stop_all();
    Serial.flush();
    //Serial.println("Connection Lost");
    lastCommand=millis();
  }
  
  if( (millis() -   lastSonar) > 300){
    if (usesSonar && Direction == forwState){
      distance=sonar();//getMicroseconds
      microsecondsToCentimeters(distance);//then real distance is calculated
      if(distance<50){ //check for blocking object.
        //Serial.print("Distance from obstacle in cm: ");
        Serial.println(distance);
        goBackward(255);
        delay(1);
        Stop();
      }
    }
    lastSonar=millis();
  }
  
  
  
  delay(1);
} 


void readInt(int &num){
  num = 0;
  for(int i=0;i<(charComand-1);i++){
    car=Serial.read();
    num+=(car-48)*(int)(0.5+pow(10,(charComand-2)-i));
   }
}

void goForward(int i){
  digitalWrite(motorIB, LOW);
  digitalWrite(motorIA, HIGH);
  analogWrite(motorSpd,i);
  Direction=forwState;
}

void goBackward(int i){
  digitalWrite(motorIA, LOW);
  digitalWrite(motorIB, HIGH);
  analogWrite(motorSpd,i);
  Direction=backState;
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
  Direction=stopState;
}

void Stop_turn(){
  //digitalWrite(motor2Spd,LOW);
  digitalWrite(motor2IA,LOW);
  digitalWrite(motor2IB,LOW);
}


double sonar(){
  pinMode(ultraSoundSignal, OUTPUT); // Switch signalpin to output
  triggerSignal();
  pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
  //waits to assigned pin to be HIGH, then counts microsecounds until pin is LOW
  return pulseIn(ultraSoundSignal, HIGH,2000);
}


void triggerSignal(){
/* Send low-high-low pulse to activate the trigger pulse of the sensor
 * -------------------------------------------------------------------
 */
digitalWrite(ultraSoundSignal, LOW); // Send low pulse
delayMicroseconds(2); // Wait for 2 microseconds
digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
delayMicroseconds(5); // Wait for 5 microseconds
digitalWrite(ultraSoundSignal, LOW); // Holdoff
}



void microsecondsToInches(double &microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  microseconds/= (74 * 2);
}




void microsecondsToCentimeters(double &microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  microseconds/= (29 * 2);
}
