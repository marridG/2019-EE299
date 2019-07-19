//-------------------------
//Module name:
//  lab1-part1-program5
//
//Description:
//  Control the LED Brick by the Button Brick
//
//Author:
//   Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019
//-------------------------
// the setup function runs once when you press reset or power the board
int LED_BUILTIN=12;
int button=11;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int state=digitalRead(button);
  if(state==HIGH){
    digitalWrite(LED_BUILTIN,HIGH);}
  
}
