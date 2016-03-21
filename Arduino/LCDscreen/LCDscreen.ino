/*
 LiquidCrystal Display Example
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (<a href="http://www.ladyada.net">http://www.ladyada.net</a>)
 
 This example will write a number of different outputs to the LCD display
 
 Author: David M. Auld
 Date: 16th October 2009
 
 */
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
//8 bits - faster
//LiquidCrystal lcd(12, 11,9,8,7,6, 5, 4, 3, 2);
//4 bits - slower
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int contrastPin=13;
#define scrollDelay 500

void setup()
{
   pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin,128);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Arduino");
  // move to row 1
  lcd.setCursor(0,1);
  lcd.print("LCD Example.");
  delay(3000);
  lcd.clear();
  lcd.print("More coming");
  lcd.setCursor(0,1);
  lcd.print("right up.");
  delay(3000);
  lcd.clear();


}
void loop()
{
  // Print a checker board pattern.
  lcd.clear();
  lcd.print("Checker Board");
  delay(2000);
  lcd.clear();
  for (int c = 0; c<17; c+=2)
  {
    lcd.setCursor(c,0); 
    lcd.print(char(255));
    lcd.setCursor(c+1,1); 
    lcd.print(char(255));
  }
  delay(5000); 
  lcd.clear();
  lcd.print("Next Example");
  lcd.setCursor(0,1);
  lcd.print("Scrolling Board");
  delay(2000);
  delay(2000);
  lcd.clear();
  for (int c = 0; c<40; c+=2)
  {
    lcd.setCursor(c,0); 
    lcd.print(char(255));
    lcd.setCursor(c+1,1); 
    lcd.print(char(255));
  }
  for (int s = 0; s < 50; s++)
  {
    lcd.scrollDisplayLeft();
    delay(scrollDelay);
  }
  lcd.clear();
  lcd.print("Time to make your own examples!");
  delay(10000);
  for (int s = 0; s < 50; s++);
  {
    lcd.scrollDisplayLeft();
    delay(scrollDelay);  
  }
  lcd.clear();
  lcd.print("Going back to the start of the routine!");
  for (int s=0; s < 65; s++)
  {
    lcd.scrollDisplayLeft();
    delay(scrollDelay);  
  }
}
