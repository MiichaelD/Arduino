#define charComand 5 // characters per comand
#define forward 12
#define backward 11
#define left 10
#define right 9
int pos = 0;    // variable to store the servo position 
int spd = 0;    // Variable to store the motor speed
int midspd = 255;
int midpos = 255;
int special = 0;
unsigned long lastCommand;

char signal,car;

void setup() 
{ 
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  Serial3.begin(9600);
  Serial.begin(9600);
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
          stop_all(); 
          break;
        
        case 1:    //continua conectado
          lastCommand=millis();          
          break;
      }
      Serial.println(special);
      special=0;
      break;  
      
    case 'V': // Vertical Bar
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
      spd=0;
      break;

    case 'H': // Horizontal Bar
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
      stop_turn();
      Serial.println(midpos);
      break;
        
    }
    delay(1);
  }
  
  if( (millis() - lastCommand) > 1350){
    stop_all();
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
  digitalWrite(backward, LOW);
  analogWrite(forward,i);
}

void goBackward(int i){
  digitalWrite(forward, LOW);
  analogWrite(backward,i);
}

void stop_all(){
 Stop();
 stop_turn();
}

void Stop(){
  digitalWrite(forward,LOW);
  digitalWrite(backward,LOW);
}

void go_left(int i) {
  digitalWrite(right, LOW);
  analogWrite(left, i);
}

void go_right(int i) {
  digitalWrite(left, LOW);
  analogWrite(right, i);
}

void stop_turn() {
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
}
