/*
Module Name:
  #2 0_hello world.ino

Description:
  Print "hello, world!" on the LCD display and blink in an
  interval of 500ms.

Code source:
  Examples -> LiquidCrystal -> HelloWorld
  LiquidCrystal Library - display() and noDisplay()

With reference to:
  https://www.arduino.cc/en/Reference/LiquidCrystal
  Electronic Bricks Starter Kit Cookbook v1.3

Modifications applied:
  We used BUS 1 to connect the LCD display, so the pin numbers
  are modified to "lcd(2, 3, 4, 5, 6, 7, 8);"

Public Interface:
  Show "hello, world!" on the LCD display

Side Effects:
  No

Authors:
  Shihao Piao, Tutian Tang, Ziliang Guo
Rev. 0 - 8 Jul
*/

/*
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 display() and noDisplay() functions to turn on and off
 the display.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay

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
  // set up the LCD's number of columns and rows: 16 cols & 2 rows
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

/**
 * [loop description]
 *   continuously blink to display and hide "hello, world!" on the LCD
 *   display in an interval of 500ms.
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
