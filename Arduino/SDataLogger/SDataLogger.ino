/*
  SD card datalogger
 
 This example shows how to log data from three analog sensors 
 to an SD card using the SD library.
 	
 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 - Mega 51
 ** MISO - pin 12 - Mega 50
 ** CLK - pin 13  - Mega 52
 ** CS - pin 4    - Mega 53
 
 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */

#include <SD.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 53;
String output;
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
   while (!Serial);


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(53, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  
  if(!SD.exists("datalog.txt")){
    Serial.println("Introduce informacion que te gustaria guardar en archivo:");  
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
        dataFile.println(output);
        Serial.println("Introduce texto a escribir:");
        while(Serial.available()>2)
          dataFile.print(Serial.read());
         dataFile.println();
         dataFile.close();
      
    }
  }
  else{
     File dataFile = SD.open("datalog.txt", FILE_READ);
     Serial.println("Leyendo archivo datalog.txt");
     while(dataFile.available()>0){
       char c=dataFile.read();
       Serial.print(c);
       output+=String (c);
     }
     dataFile.close();
     Serial.println("\nFIN DE ARCHIVO!\nEscriba algo para añadir al archivo.\n(Empezando con 1 para SobreEscribir)");
     while(Serial.available()<2);
     SD.remove("datalog.txt");
     if(Serial.read() == '1')
       output="";
     while(dataFile.available()>0){
       char c=dataFile.read();
       output+=String (c);
     }
     
  }
  delay(15);
}









