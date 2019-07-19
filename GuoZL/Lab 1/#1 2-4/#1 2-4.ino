int PIN_1=12;

void setup() {
  // initialize digital pin PIN_1 as an output.
  pinMode(PIN_1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // 1ST One-second blink
  digitalWrite(PIN_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PIN_1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  // 2ND One-second blink
  digitalWrite(PIN_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PIN_1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                        // wait for a second
  
  // 1ST Two-second blink
  digitalWrite(PIN_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for 2 seconds
  digitalWrite(PIN_1, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for 2 seconds

  // 2ND Two-second blink
  digitalWrite(PIN_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for 2 seconds
  digitalWrite(PIN_1, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for 2 seconds
}
