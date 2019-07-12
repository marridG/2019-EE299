int PIN_1=12;

void setup() {
  // initialize digital pin PIN_! as an output.
  pinMode(PIN_1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for 2 seconds
  digitalWrite(PIN_1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for 1 second
}
