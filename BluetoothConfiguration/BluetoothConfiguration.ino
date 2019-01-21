#include <stdio.h>
/*
Program:       BluetoothConfiguration 
Description:        This program lets you Change your Linvor Bluetooth module parameters:
                BaudRate:9600N81,ID:linvor,Password:1234.
                Commands must be send every second with no connection stabishled between
                your bluetooth module and other device.

Note:          To use on an arduino different than ArduinoMega, remember to change Serial3 to Serial.

More Info:     www.scribd.com/doc/95703428/Bluetooth-HC-06-Datasheet

How to use:         You can simply change the defaultCommand define or thru serial monitorm
               you MUST specify the number of letters the command needs in the first 2 characters.
               
Different baudrates:
(N):      Value:
1---------1200
2---------2400
3---------4800
4---------9600 (Default)
5--------19200
6--------38400
7--------57600
8-------115200
9-------230400
A-------460800
B-------921600
C------1382400

    command:      thru Serial Monitor:                   function:
1     AT              02AT                           Test communication
2   AT+BAUD(N)        08AT+BAUD(N)                   Change BaudRate
3   AT+NAME(newName)                                 Change BluetoothName  - new name must be 20 characters at most.
4   AT+PASS(newPass)  11AT+PASS(newPass)             Change BluetoothPassword     - new pass must be 4 number digits.
5   AT+PN             05AT+PN                        No Parity Check (default);
6   AT+PO             05AT+PO                        Set odd parity check
7   AT+PE             05AT+PE                        Set even parity check

Programer:     Michael Duarte (michael.duarte@hotmail.com)

Board Used:    Arduino Mega2560 

To change the default command, just change AT for the
new command on the next define, LEAVING THE DOUBLE QUOTES.*/
#define defaultCommand "AT"

unsigned long lastCommand;
int received=0;
char command[10];

void setup(){
  Serial3.begin(115200);
  Serial.begin(115200);
  lastCommand=millis();
  received=0;
  Serial.println("Ready to Send");
}

void loop(){
  
  if(Serial3.available()){ //READ RESPONSE
    Serial.print((char)Serial3.read());//comment if diff board than arduino mega
  }
  
  //comment this block if u use a different arduino board.
  if(Serial.available() && received == 0){//WRITE NEW COMMAND
    delay(10);
    received=(Serial.read()-48)*10;
    received+=Serial.read()-48;
    memset(command,'\0',10);
    for(int i=0;i<received;i++){
      command[i]=(char)Serial.read();
    }
  }//////////////////////////////////////////////////////////
  
  if( (millis() - lastCommand) > 1000){//EVERY SECOND SEND LAST COMMAND
    lastCommand=millis();
    if(received != 0){//IF COMMAND RECEIVED
    Serial.println("Command Sent:");
      for(int i=0;i<received;i++){
        Serial3.print(command[i]);
        Serial.print(command[i]);
      }
      Serial.println();
      received=0;
    }
    else
      Serial3.print(defaultCommand);
      Serial.println();////comment if different than arduino mega
  }
  
  delay(2);
}
