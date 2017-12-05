#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

String TopLine;
String BottomLine;

void LCDPrint(String line, bool printLine = 0)
{
  if (line != BottomLine)
  {
    BottomLine = line;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(TopLine);
    lcd.setCursor(0, 1);
    lcd.print(BottomLine);

    TopLine = BottomLine;
  }
}

void setup()
{

  Wire.begin();
  Wire.beginTransmission(0x27);

  lcd.begin(16, 2); // initialize the lcd

  lcd.setBacklight(255);

} // setup()

void loop()
{

  LCDPrint("Hello world");

  delay(1000);

  LCDPrint("Yo Mummma");

  delay(1000);

} // loop()
