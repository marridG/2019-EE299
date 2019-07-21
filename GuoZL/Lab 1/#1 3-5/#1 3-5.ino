int LED_1=12;
int BUTTON_1=11;

void setup() {
  // initialize digital pin LED_1 as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(BUTTON_1, INPUT);
}

// the loop function runs over and over again forever
void loop()
{
 if (digitalRead(BUTTON_1))    // if button press
    digitalWrite(LED_1,HIGH);  // light the LED
 else                          // if not press
    digitalWrite(LED_1,LOW);     // turn off the LED
} 
