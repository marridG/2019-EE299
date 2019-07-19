/*
Module Name:
  #2 1_name.ino

Description:
  Print the first name of each group member on the LCD display.
  Two names are on the first row, while the remaining one on
  the second.
  Blink the text in an interval of 500ms.

Code source:
  Examples -> LiquidCrystal -> HelloWorld
  LiquidCrystal Library - display() and noDisplay()

With reference to:
  https://www.arduino.cc/en/Reference/LiquidCrystal
  Electronic Bricks Starter Kit Cookbook v1.3

Modifications applied:
  (1) We used BUS 1 to connect the LCD display, so the pin numbers
  are modified to "lcd(2, 3, 4, 5, 6, 7, 8);"
  (2) use setCursor() so as to implement the name-printing function

Public Interface:
  Blink the first name of eahc group member on the LCD display in 
  an interval of 500ms.

Side Effects:
  No

Authors:
  Shihao Piao, Tutian Tang, Ziliang Guo
Rev. 0 - 8 Jul
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7, d8 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7, d8);

/**
 * [setup description]
 *   setup all the hardware pin numbers and initialize the displayed
 *   text of LCD
 * @return {NONE}
 */
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Shihao Tutian");
  lcd.setCursor(0,1);
  lcd.print("Ziliang");
}

/**
 * [loop description]
 *   continuously blink the displayed text.
 * @return {NONE}
 */
void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}
