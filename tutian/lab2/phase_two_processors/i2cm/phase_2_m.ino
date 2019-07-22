#include <Wire.h> // library for I2C Bus
#include <String.h>

char buffer[4] = {0, 0, 0, 0};
int length = 0;
int number1 = 0;
int number2 = 0;
char operation = 0;
short phase = 0;

int get_number()
{
  length = Serial.readBytesUntil('\n', buffer, 3); // Read to '\n' or at most 3 characteristics.
                                                   // Return the number of read. '\n' is dropped.
  Serial.print("Get ");
  Serial.print(length);
  Serial.print(" chars, current buffer: ");
  Serial.println(buffer); // Serial for debug

  int temp_number = 0;
  int temp_number_sign = 0;

  if (1 == length) // get a number
  {
    temp_number_sign = 1;
    temp_number = buffer[0] - '0';
  }

  else if (2 == length) // get a number
  {
    if ('-' == buffer[0])
    {
      temp_number_sign = -1;
      temp_number = buffer[1] - '0';
    }
    else
    {
      temp_number_sign = 1;
      temp_number = (buffer[0] - '0') * 10 + (buffer[1] - '0');
    }
  }

  else if (3 == length) // get a number
  {
    temp_number_sign = 1; // the sign of the number, 1 for positive and -1 for negative
    if ('-' == buffer[0])
      temp_number_sign = -1;

    int buffer_cursor = (1 - temp_number_sign) / 2; // where the number start (avoid the sign)
    // calculate the actual number
    temp_number = (buffer[buffer_cursor] - '0') * 10 + (buffer[buffer_cursor + 1] - '0');
  }

  return temp_number * temp_number_sign;
}

void print_number(int to_print, bool bracket = false)
{
  char temp[7];
  String(to_print).toCharArray(temp, 7);

  Wire.beginTransmission(4); // transmit to device #4
  if (to_print < 0 && bracket)
  {
    Wire.write('(');
  }

  Wire.write(temp); // send the command to the SLVAE
  if (to_print < 0 && bracket)
  {
    Wire.write(')');
  }
  Wire.endTransmission(); // ends the transmission
}

void print_operator(char to_print)
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(to_print);      // send the command to the SLVAE
  Wire.endTransmission();    // ends the transmission
}

int calculate()
{
  int outcome = 0;

  switch (operation)
  {
  case '+':
  {
    outcome = number1 + number2;
    break;
  }
  case '-':
  {
    outcome = number1 - number2;
    break;
  }
  case '*':
  {
    outcome = number1 * number2;
    break;
  }
  case '/':
  {
    outcome = number1 / number2;
    break;
  }
  }

  return outcome;
}

void setup()
{
  Serial.begin(9600); // Start a Serial with 9600 bit rate
  Wire.begin();       // join i2c bus (address optional for master)
}

void loop()
{
  if (Serial.available() > 0) // Check if there is something new from Serial
  {

    phase++;
    switch (phase)
    {
    case 1: // the first two-digit number with one possible sign
    {
      // lcd.clear();         // clear the lcd display for the next calculation
      // lcd.setCursor(0, 0); // set the cursor to top-left

      number1 = get_number();      // get the first number
      print_number(number1, true); // print the number on screen
      break;                       // DO NOT FORGET TO BREAK!
    }
    case 2: // the operator
    {
      Serial.readBytesUntil('\n', buffer, 3);
      operation = buffer[0];     // get the operator
      print_operator(operation); // print the operator
      break;                     // DO NOT FORGET TO BREAK!
    }
    case 3: // the second two-digit number with one possible sign
    {
      number2 = get_number();
      print_number(number2, true); // print the number
      break;                       // DO NOT FORGET TO BREAK!
    }
    case 4:
    {
      Serial.readBytesUntil('\n', buffer, 3);
      print_operator('=');
      print_number(calculate());
      print_operator('.');
      phase = 0; // reset the phase
      break;
    }
    }

    delay(100);
  }
}