#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

char buffer[4] = {0, 0, 0, 0};
int length = 0;
int temp_number = 0;
int temp_number_sign = 0;
int number1 = 0;
short number1_sign = 0;
int number2 = 0;
short number2_sign = 0;
int outcome = 0;
char operation = 0;
short phase = 0;
const int MAX_COL = 16;
const int MAX_ROW = 2; // set up the maximum number of rows / columns in case of overflow

void setup()
{
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(MAX_COL, MAX_ROW);
}

void loop()
{
  if (Serial.available() > 0)
  {
    // Make sure the array is clean.
    for (int i = 0; i < 4; i++)
    {
      buffer[i] = 0;
    }
    length = Serial.readBytesUntil('\n', buffer, 3);
    // the '\n' is dropped then. Will return the number of characters.

    Serial.print("The messgae in the buffer is: ");
    Serial.println(buffer);
    lcd.write(buffer);

    if (1 != length)
    {
      temp_number_sign = 1;
      if ('-' == buffer[0])
        temp_number_sign = -1;

      int buffer_cursor = (1 - temp_number_sign) / 2;
      temp_number = (buffer[buffer_cursor] - '0') * 10 + (buffer[buffer_cursor + 1] - '0');
    }

    phase++;
    if (1 == phase)
    {
      number1 = temp_number;
      number1_sign = temp_number_sign;
    }
    if (2 == phase)
    {
      operation = buffer[0];
    }
    if (4 == phase)
    {
      switch (operation)
      {
      case '+':
      {
        outcome = number1 * number1_sign + temp_number * temp_number_sign;
        break;
      }
      case '-':
      {
        outcome = number1 * number1_sign - temp_number * temp_number_sign;
        break;
      }
      case '*':
      {
        outcome = number1 * number1_sign * temp_number * temp_number_sign;
        break;
      }
      case '/':
      {
        outcome = number1 * number1_sign / temp_number * temp_number_sign;
        break;
      }
      default:
        lcd.print('ERROR!');
      }
      lcd.setCursor(0, 1);
      lcd.print(outcome);
      phase = 0;
    }

    delay(100);
  }
}