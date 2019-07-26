/*
  Module Name:
    phase_2_s.ino
  
  Description:
    This program sets up a I2C Bus on a SLAVE board to receive the command from MASTER.
    A LCD panel is attached and the two board are connected through A4 and A5.

  Author:
    Shihao Piao, Ziliang Guo, Tutian Tang

  Rev. 2 22 July 2019
 */

#include <LiquidCrystal.h> // to drive the LCD panel
#include <Wire.h>          // to set up the I2C bus

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
bool to_clear = false; // initialize a flag to decide wether to clear the display

void receiveEvent(int howMany)
{
  // decide whether to clear the display
  if (to_clear)
  {
    lcd.clear();         // clear the lcd display for the next calculation
    lcd.setCursor(0, 0); // set the cursor to top-left
    to_clear = false;    // once cleared, initialize the flag
  }

  // cope with the byte from the I2C Bus one by one
  for (int i = 0; i < howMany; i++)
  {
    char c = Wire.read(); // receive byte as a character
    // '.' is a flag to clear the display
    if ('.' == c)
    {
      to_clear = true; // set up the flag
      break;           // waiting for the master for the next message
    }

    // other wise, print whatever the master sends
    lcd.write(c);

    // if there is an '='
    if ('=' == c)
    {
      lcd.setCursor(0, 1); // set the cursor to the second line
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
  delay(100); // the board should have a theoretical refresh rate of 10 Hz
}