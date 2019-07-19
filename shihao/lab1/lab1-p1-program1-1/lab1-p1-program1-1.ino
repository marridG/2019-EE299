//-------------------------
//Module name:
//  lab1-part1-program1
//
//Description:
//  Function control the LED light 
//  to realize on for 2 seconds
//  and off for 1 second and repeats.
//
//Author:
//   Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019
//-------------------------


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
//  do loop to realize blink
//
//Method:
//  use pinwrite() to initialize the pin.
// 
//Author:
//  Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019.
//-------------------------------------------
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
  
}
