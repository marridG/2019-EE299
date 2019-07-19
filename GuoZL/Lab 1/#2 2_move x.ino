/*
Module Name:
  #2 2_move x.ino

Description:
  Show a "x" on the LCD display. There are two buttons connecting
  to the board, called the "left" and the "right". After pressing
  the left one, the "x" will be moved to the left by one column;
  to the right by one column for the right, respectively.
  If the "x" moves to the right from the very right side, it will
  return to the very left side and viceversa.

Code source:
  Examples -> LiquidCrystal -> HelloWorld
  LiquidCrystal Library - display() and noDisplay()

With reference to:
  https://www.arduino.cc/en/Reference/LiquidCrystal
  Electronic Bricks Starter Kit Cookbook v1.3

Modifications applied:
  (1) We used BUS 1 to connect the LCD display, so the pin numbers
  are modified to "lcd(2, 3, 4, 5, 6, 7, 8);"
  (2) use setCursor() so as to implement the location changes of "x"

Public Interface:
  Show "x" on the LCD display.
  Respond to user's pressing different buttons.

Side Effects:
  No. The locations of "x" change quite fast and smoothly!

Authors:
  Shihao Piao, Tutian Tang, Ziliang Guo
Rev. 0 - 8 Jul
*/

// include the library code:
#include <LiquidCrystal.h>

const int MAX_WIDTH=16;         // the width of the LCD display
// const int DELAY_INTERVAL=50;    // delay to wait for status change
int button_left=9;              // the pin number of the left button
int button_right=11;            // the pin number of the right button
int character_loc=0;            // the number of column where "x" locates

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7, d8 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7, d8);

void setup()
{
  // setup the pin numbers of the two buttons
  pinMode(button_left, INPUT);
  pinMode(button_right, INPUT);
  // set up the LC  D's number of columns and rows
  lcd.begin(MAX_WIDTH, 2);
  // initialize the cursor location and the output "x"
  lcd.setCursor(0,0);
  lcd.print("x");
  // Serial.begin(9600);
}

void loop()
{
/* Approach One
  lcd.display();
  delay(500);
*/
  // to indicate whether a button is pressed. True for yes; false for not.
  bool status_change=false;
/*if(digitalRead(button_left))
  {
    delay(DELAY_INTERVAL);
    if(!digitalRead(button_left))
    {
      character_loc+=1;
    }
    status_change=true;
  }
  if(digitalRead(button_right))
  {
    delay(DELAY_INTERVAL);
    if(!digitalRead(button_right))
    {
      character_loc-=1;
    }
    status_change=true;
  }
*/
  if(digitalRead(button_left))        // the left button is of a high voltage, thus pressed
  {
    character_loc++;
    status_change=true;
    // Serial.println("left");
  }
  else if (digitalRead(button_right)) // the right button is of a high voltage, thus pressed
  {
    character_loc--;
    status_change=true;
    // Serial.println("right");
  }

  // if a button is pressed, change the output location of the "x"
  if(status_change)
  {
    // check whether the location overflows
    // if larger than maximum, set to 0; if less than minimum, set to maximum
    if(character_loc>=MAX_WIDTH)
      character_loc-=16;
    else if(character_loc<0)
      character_loc+=16;

    // clear the previously printed "x"
    lcd.clear();

    // set the cursor to the new location and print "x"
    lcd.setCursor(character_loc,0);
    lcd.print("x");

    delay(500);
    // set the status back to that indicating no button is pressed
    status_change=false;
  }

}
