#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
bool to_clear = false;

void receiveEvent(int howMany)
{
  if (to_clear)
  {
    lcd.clear();         // clear the lcd display for the next calculation
    lcd.setCursor(0, 0); // set the cursor to top-left
    to_clear = false;
  }
  for (int i = 0; i < howMany; i++)
  {
    char c = Wire.read(); // receive byte as a character
    if ('.' == c)
    {
      to_clear = true;
      break;
    }
    lcd.write(c);
    if ('=' == c)
    {
      lcd.setCursor(0, 1);
    }
  }
}

void setup()
{
  Serial.begin(9600);           // Start a Serial with 9600 bit rate
  lcd.begin(16, 2);             // initialize the LCD pannel with 16 columns and 2 rows
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  delay(100);
}