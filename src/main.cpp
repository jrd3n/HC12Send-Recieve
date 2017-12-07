#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

#include <SoftwareSerial.h>

SoftwareSerial HC12(D6, D7); //RX, TX

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

String TopLine;
String BottomLine;

// Functions XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
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

    //delay(2000);
  }
}
void Set_HC12(int SetPin = D0)
{
  pinMode(SetPin, OUTPUT);

  digitalWrite(SetPin, LOW); // set pin to low

  LCDPrint("D0 set to low");
  delay(200);

  String Input = "";

  for (int i = 0; i <= 7; i++)
  {

    int baud[] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}; // Available baud rates: 1200 bps, 2400 bps, 4800 bps, 9600 bps, 19200 bps, 38400 bps, 57600 bps, and 115200 bps. Default: 9600 bps.

    HC12.begin(baud[i]);

    //HC12.begin(2400);

    String displayString = String(baud[i]);
    displayString += " = ";

    HC12.write("AT"); // Send that data to HC-12

    while (HC12.available())
    {
      //LCDPrint("HC12 avalible");

      Input = HC12.readString();
    }

    if (Input.indexOf("OK") != -1)
    {
      Input = "OK";
    }

    displayString += Input;

    LCDPrint(displayString);
    Serial.println(displayString);
    delay(500);

    HC12.end();

    displayString = "";
  }

  /*
    For example, if we type “AT+B38400” the baud rate of the module will be set to 38400.

    1. AT – Test command.
    Example: Send “AT” to module, and the module returns “OK”.
    2. AT+Bxxxx – Change the serial port baud rate.
    Available baud rates: 1200 bps, 2400 bps, 4800 bps, 9600 bps, 19200 bps, 38400 bps, 57600 bps, and 115200 bps. Default: 9600 bps.
    Example: Send “AT+B38400” to module, and the module returns “OK+B19200”.
    3. AT+Cxxxx – Change wireless communication channel, from 001 to 100.
    Default: Channel 001, with working frequency of 433.4MHz. Each next channel is 400KHz higher.
    Example: If we want to set the module to channel 006, we need to send “AT+C006” command to the module, and the module will return “OK+C006”. The new working frequency will be 435.4MHz.
  */

  digitalWrite(SetPin, HIGH); // set pin to low
  LCDPrint("D0 set to HIGH");
}
// Functions XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void setup()
{

  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);

  Serial.begin(115200);

  // Set_HC12();

  HC12.begin(9600);

} // setup()

void loop()
{
  LCDPrint("Reading from Air:");
  while (HC12.available())
  {
    LCDPrint(HC12.readString());
  }

} // loop()