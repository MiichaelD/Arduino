
int led=13,numBytes;
char var;
char cadena[256];
char* string[]={"Apagado","Prendido"};
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Ready");
}

void loop() {
  delay(50);
  if(!(numBytes=Serial.available()))
    return;
  var=Serial.read();
  if (var=='0'){
    digitalWrite(led,LOW);
    Serial.print(string[0]);
    Serial.print(" - ");
    Serial.println(var);
  }
  else{
    analogWrite(led,255);
    Serial.print(string[1]);
    Serial.print(" - ");
    Serial.println(var);
  }  
}
