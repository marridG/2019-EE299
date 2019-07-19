/*
  Module Name:
    i2cm.ino
  
  Description:
    This program sets up a I2C Bus on a MASTER board to send command to a SLVAE.
    A button is attached onto the board and the two board are connected through A4 and A5.
    Serial Port is opend JUST FOR DEBUGGING.

  Author:
    Shihao Piao, Ziliang Guo, Tutian Tang

  Rev. 1 14 July 2019
 */

#include <Wire.h>             // library for I2C Bus

const int BUTTON_PIN = 9;     // define where the button is conncted to
int press_count = 0;          // count the times of the button being pressed

void setup()
{
  Wire.begin();               // join i2c bus (address optional for master)
  Serial.begin(9600);         // start serial for output
  pinMode(BUTTON_PIN, INPUT); // initialize the Button
}

void loop()
{
  if (digitalRead(BUTTON_PIN)) // If the button is pressed
  {
    Wire.beginTransmission(4); // transmit to device #4
    press_count++;             // button pressed, counter ++
    if (press_count % 2)       // if the counter is even, turn on the LED
    {
      Wire.write('O');         // send the command to the SLVAE
      Serial.println("ON");    // FOR DEBUGGING ONLY
    }
    else                       // if the counter is even, turn off the LED
    {
      Wire.write('F');         //send the command to the SLVAE
      Serial.println("OFF");   // FOR DEBUGGING ONLY
    }
    Wire.endTransmission();    // ends the transmission
    delay(200);                // wait for the slave to make the move
  }
  delay(50);                   // wait for a few millionseconds to save power
}
