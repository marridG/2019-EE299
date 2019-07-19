//--------------------------------------------
//Module name:
//  lab1-p1-program2.c
//
//Description:
//  this auduino program will realize
//  blink 1 second for 2 times 
//  and blink 2seconds for 2times.
//
//Author:
//  Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019.
//-------------------------------------------


//--------------------------------------------
//setup
//
//Purpose:
//  setup and initialize the pin we want to use.
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
  pinMode(LED_BUILTIN, OUTPUT);
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
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000); 
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
  digitalWrite(LED_BUILTIN,HIGH);    // turn the LED off by making the voltage LOW
  delay(2000);
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);   // wait for two seconds
  digitalWrite(LED_BUILTIN,HIGH);    // turn the LED off by making the voltage LOW
  delay(2000);
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);   // wait for two seconds
}
