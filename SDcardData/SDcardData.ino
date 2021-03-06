#include <SD.h>
#include <SPI.h>

Sd2Card card;
SdVolume volume;
SdFile root;

/* LOW LEVEL EXAMPLE TO KNOW SD CARD INFO
 ** MOSI - pin 11 - Mega 51
 ** MISO - pin 12 - Mega 50
 ** CLK - pin 13  - Mega 52
 ** CS - pin 4    - Mega 53
*/

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
//(53 on Mega, 10 on UNO)
const int chipSelect = 53;

void setup()
{
  Serial.begin(115200);
   while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  Serial.print("\nInitializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(53, OUTPUT);     // change this to 53 on a mega


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:\n* is a card is inserted?");
    Serial.println("* Is your wiring correct?\n* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
   Serial.println("Wiring is correct and a card is present."); 
  }

  Serial.print("\nCard type: ");
  switch(card.type()) {// print the type of card
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    Serial.println("\n\nEntering to repeater mode, type 'z' to exit ");
    while(true){
      if(Serial.available()){
        String str = Serial.readString();    
        boolean exit = str == "z";    
        Serial.println(str);
        if(exit) 
          break;
      }
    }
//    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
  
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.print(volumesize);
  Serial.print("\tVolume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.print(volumesize);
   Serial.print("\nVolume size (Gbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
  
   root.ls(LS_R | LS_DATE | LS_SIZE);// list all files in the card with date and size
}



void loop(void) {
  
}
