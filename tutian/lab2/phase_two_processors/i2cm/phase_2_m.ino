/*
  Module Name:
    phase_2_m.ino
  
  Description:
    This program sets up a I2C Bus on a MASTER board to send command to a SLVAE.
    This board is attached to the computer and a Serial Port is opened.
    The two board are connected through A4 and A5.
    Serial Port is opend JUST FOR DEBUGGING.

  Author:
    Shihao Piao, Ziliang Guo, Tutian Tang

  Rev. 2 22 July 2019
 */

#include <Wire.h>   // library for I2C Bus
#include <String.h> // To cope with string

char buffer[4] = {0, 0, 0, 0}; // the buffer for Serial port
int length = 0;                // record the length of the buffer
int number1 = 0;               // record number 1
int number2 = 0;               // record number 2
char operation = 0;            // record the operation
short phase = 0;               // record the phase

int get_number()
{
  length = Serial.readBytesUntil('\n', buffer, 3); // Read to '\n' or at most 3 characteristics.
                                                   // Return number of Bytes read. '\n' is dropped.
  Serial.print("Get ");                            // Serial for debug
  Serial.print(length);                            // Serial for debug
  Serial.print(" chars, current buffer: ");        // Serial for debug
  Serial.println(buffer);                          // Serial for debug

  int temp_number = 0;      // the variable to cope with the current input - record the number
  int temp_number_sign = 0; // the variable to cope with the current input - record the sign

  // if there is only one Byte received
  if (1 == length)
  {
    temp_number_sign = 1;          // must be positive
    temp_number = buffer[0] - '0'; // the number is exactly the first char - '0'
  }

  // if there are two Bytes received
  else if (2 == length) // get a number
  {
    // check if it's negative
    if ('-' == buffer[0])
    {
      temp_number_sign = -1;                                    // negative
      temp_number = buffer[1] - '0';                            // only one digit
    }                                                           //
    else                                                        //
    {                                                           //
      temp_number_sign = 1;                                     // positive
      temp_number = (buffer[0] - '0') * 10 + (buffer[1] - '0'); // must have two digits
    }
  }

  else if (3 == length)   // get a number
  {                       //
    temp_number_sign = 1; // the sign of the number, 1 for positive and -1 for negative
    // check if it is negative
    if ('-' == buffer[0])
      temp_number_sign = -1;

    int buffer_cursor = (1 - temp_number_sign) / 2; // where the number start (avoid the sign)
    // calculate the actual number
    temp_number = (buffer[buffer_cursor] - '0') * 10 + (buffer[buffer_cursor + 1] - '0');
  }

  // return the number
  return temp_number * temp_number_sign;
}

void print_number(int to_print, bool bracket = false)
{
  char temp[7];                          // initialize a buffer. Length of 7 should be enough
  String(to_print).toCharArray(temp, 7); // convert the number to print into the bufferf
                                         //
  Wire.beginTransmission(4);             // transmit to device #4

  // check if it's negative
  if (to_print < 0 && bracket)
  {
    Wire.write('('); // print the bracket
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

  // the code talks!

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

    // there are four phases
    phase++;
    switch (phase)
    {
    case 1: // the first two-digit number with one possible sign
    {
      number1 = get_number();                 // get the first number
      print_number(number1, true);            // print the number on screen
      break;                                  // DO NOT FORGET TO BREAK!
    }                                         //
    case 2:                                   // the operator
    {                                         //
      Serial.readBytesUntil('\n', buffer, 3); //
      operation = buffer[0];                  // get the operator
      print_operator(operation);              // print the operator
      break;                                  // DO NOT FORGET TO BREAK!
    }
    case 3: // the second two-digit number with one possible sign
    {
      number2 = get_number();
      print_number(number2, true);            // print the number
      break;                                  // DO NOT FORGET TO BREAK!
    }                                         //
    case 4:                                   //
    {                                         //
      Serial.readBytesUntil('\n', buffer, 3); // read from Serial
      print_operator('=');                    //
      print_number(calculate());              // send the outcome to the slave
      print_operator('.');                    // the flag of clear the screen on next output
      phase = 0;                              // reset the phase
      break;
    }
    }

    delay(100);
  }
}