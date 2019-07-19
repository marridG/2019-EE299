/*
  Module Name:
    i2cs.ino
  
  Description:
    This program sets up a I2C Bus on a SLAVE board to receive the command from MASTER.
    A LED is attached onto the board and the two board are connected through A4 and A5.
    Serial Port is opend JUST FOR DEBUGGING.

  Author:
    Shihao Piao, Ziliang Guo, Tutian Tang

  Rev. 1 14 July 2019
 */

#include <Wire.h>

const int LED_PIN = 9;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for DEBUG ONLY
  pinMode(LED_PIN, OUTPUT);     // initialize the LED
}

void loop()
{
  delay(50); // Save power
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  char c = Wire.read();          // receive byte as a character
  if ('O' == c)                  // 'O' for ON and otherwise OFF
  {
    digitalWrite(LED_PIN, HIGH); // TURN ON the LED
    Serial.println("ON");        // FOR DEBUGGING
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // TURN OFF the LED
    Serial.println("OFF");      // FOR DEBUGGING
  }
}
