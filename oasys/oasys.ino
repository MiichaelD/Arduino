#include <ArduinoJson.h>
#include <OpenGarden.h>
#include <Wire.h>
#include "/usr/include/floatToString.h"

#define point_1_cond 40000   // Write here your EC calibration value of the solution 1 in µS/cm
#define point_1_cal 40       // Write here your EC value measured in resistance with solution 1
#define point_2_cond 10500   // Write here your EC calibration value of the solution 2 in µS/cm
#define point_2_cal 120      // Write here your EC value measured in resistance with solution 2

#define calibration_point_4 2153  //Write here your measured value in mV of pH 4
#define calibration_point_7 1972  //Write here your measured value in mV of pH 7
#define calibration_point_10 1816 //Write here your measured value in mV of pH 10

int fansPin = A0;
int lightsPin = A1;
int analogPin = 0;
int val = 0;
char buffer[25];

int luminosityInt = 0;
String luminosityString = "";
String airTemperature = "";
String airHumidity = "";
String waterTemperature = "";
String waterPH = "";
String waterMvPh = "";
String ECResistance = "";
String ECValue = "";

int initialize = 8000;
int minute = 30000; //35 seconds
//int minute = 30000; //30 seconds
//int minute = 10000; //10 seconds
void setup() 
{
  pinMode(fansPin, OUTPUT);
  pinMode(lightsPin, OUTPUT);
  Serial.begin(9600);
  OpenGarden.initSensors();
  OpenGarden.calibrateEC(point_1_cond,point_1_cal,point_2_cond,point_2_cal);
  OpenGarden.calibratepH(calibration_point_4,calibration_point_7,calibration_point_10);
}

void loop() 
{
  while (Serial.available()) 
  {
    if (1 == 1 || Serial.readString() == "hello") 
    {
      luminosityInt = 0;
      luminosityString = "";
      airTemperature = "";
      airHumidity = "";
      waterTemperature = "";
      waterPH = "";
      waterMvPh = "";
      ECResistance = "";
      ECValue = "";
      digitalWrite(fansPin, HIGH);
      digitalWrite(lightsPin, HIGH);
      OpenGarden.sensorPowerON();  //Turns on the sensor power supply
      delay(initialize);
      
      luminosityInt = OpenGarden.readLuminosity();  //Read the sensor
      float airtemp = OpenGarden.readAirTemperature();  //Read the sensor
      float airhumidtemp = OpenGarden.readAirHumidity();
      float watertemp = OpenGarden.readSoilTemperature();  //Read the sensor
      float resistanceEC = OpenGarden.readResistanceEC(); //EC Value in resistance
      float EC = OpenGarden.ECConversion(resistanceEC); //EC Value in µS/cm
      int mvpH = OpenGarden.readpH(); //Value in mV of pH
      float pH = OpenGarden.pHConversion(mvpH); //Calculate pH value
      //Serial.println(pH);
      OpenGarden.sensorPowerOFF();  //Turns off the sensor power supply

      luminosityString = String(luminosityInt, DEC);
      airTemperature = floatToString(buffer, airtemp, 5);
      airHumidity = floatToString(buffer, airhumidtemp, 5);
      waterTemperature = floatToString(buffer, watertemp, 5);
      ECResistance = floatToString(buffer, resistanceEC, 5);
      ECValue = floatToString(buffer, EC, 5);
      waterMvPh = String(mvpH, DEC); 
      waterPH = floatToString(buffer, pH, 5);


      if (airtemp < 21) {
        //analogWrite(ledPin, 255);
      } 
      else {
        //analogWrite(ledPin, 0);
      }
      StaticJsonBuffer<400> jsonBuffer;

      JsonObject& root = jsonBuffer.createObject();

      root["integration_token"] = "HP9hkmCnOqATbaRRyA0w7Mo0onmkuSbIX7nVGfkH9FAIXMEQLb5XXpMAIiDN";

      JsonObject& parameters = root.createNestedObject("parameters");

      JsonObject& luminosityObject = parameters.createNestedObject("luminosity");
      luminosityObject["value"] = luminosityInt;
      luminosityObject["mac_address"] = "00:00:00:00:00:00";

      JsonObject& airTempObject = parameters.createNestedObject("air_temp");
      airTempObject["value"] = airTemperature;
      airTempObject["mac_address"] = "00:00:00:00:00:01";

      JsonObject& humidityObject = parameters.createNestedObject("humidity");
      humidityObject["value"] = airHumidity;
      humidityObject["mac_address"] = "00:00:00:00:00:02";

      JsonObject& waterTempObject = parameters.createNestedObject("water_temp");
      waterTempObject["value"] = waterTemperature;
      waterTempObject["mac_address"] = "00:00:00:00:00:03";

      JsonObject& waterEcResistanceObject = parameters.createNestedObject("water_ec_resistance");
      waterEcResistanceObject["value"] = resistanceEC;
      waterEcResistanceObject["mac_address"] = "00:00:00:00:00:04";

      JsonObject& waterEcObject = parameters.createNestedObject("water_ec");
      waterEcObject["value"] = EC;
      waterEcObject["mac_address"] = "00:00:00:00:00:05";

      JsonObject& waterMvPhObject = parameters.createNestedObject("water_mv_ph");
      waterMvPhObject["value"] = mvpH;
      waterMvPhObject["mac_address"] = "00:00:00:00:00:06";

      JsonObject& waterPhObject = parameters.createNestedObject("water_ph");
      waterPhObject["value"] = pH;
      waterPhObject["mac_address"] = "00:00:00:00:00:07";
      //Serial.println();
      //Serial.println(root);
      root.printTo(Serial);
      Serial.println();
      //root.printTo(Serial);
      delay(minute);
    }
    
  }
}



