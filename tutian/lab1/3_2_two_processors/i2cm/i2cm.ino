#include <Wire.h>

const int BUTTON_PIN = 9;
int press_count = 0;

void setup()
{
  Wire.begin();       // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial for output
  pinMode(BUTTON_PIN, INPUT);
}

byte x = 0;

void loop()
{
  if (digitalRead(BUTTON_PIN))
  {
    Wire.beginTransmission(4); // transmit to device #4
    press_count++;
    if (press_count % 2)
    {
      Wire.write('O');
      Serial.println("ON");
    }
    else
    {
      Wire.write('F');
      Serial.println("OFF");
    }
    Wire.endTransmission;
  }
  delay(500);
}
