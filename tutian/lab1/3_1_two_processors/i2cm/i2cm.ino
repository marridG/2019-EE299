#include <Wire.h>

void setup()
{
  Wire.begin();       // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial for output
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("x is ");       // sends five bytes
  Wire.write(x);             // sends one byte

  Wire.endTransmission(); // stop transmitting

  Serial.print("x is ");
  Serial.println(x);
  x++;
  delay(500);
}
