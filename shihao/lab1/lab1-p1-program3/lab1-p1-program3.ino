//--------------------------------------------
//Module name:
//  lab1-p1-program3.c
//
//Description:
//  this auduino program will realize
//  blink on for 2 seconds
//  and off for 1 second.
//
//Author:
//  Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019.
//-------------------------------------------

int led_pin=11;//we need connect 11port for the LED

//--------------------------------------------
//setup
//
//Purpose:
//  setup and initialize the pin we want to use.
//
//Parameters:
//  int led_pin means connect LED port is 11.
//
//Method:
//  use pinMode() to initialize the pin.
// 
//Author:
//  Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019.
//-------------------------------------------
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
}
//--------------------------------------------
//loop
//
//Purpose:
//  do loops to realize blink forever
//
//Method:
//  use digitalWrite() to let LED on and off
//  use delay() to blink.
// 
//Author:
//  Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019.
//-------------------------------------------
void loop() {
  digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);
   digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
  
}
