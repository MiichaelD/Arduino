#define input 8
#define output 7

void setup(){
  pinMode(input,INPUT);
  pinMode(output,OUTPUT);
  Serial.begin(115200);
}

void loop(){
  digitalWrite(output,((digitalRead(input) == LOW)?LOW:HIGH));
  Serial.println(digitalRead(input));
  delay(20);
}
