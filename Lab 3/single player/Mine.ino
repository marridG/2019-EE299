
void setup()
{
    // start serial port at 9600 bps and wait for port to open:
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

void loop()
{
    // if we get an invalid byte, return and jump out
    if (Serial.available() > 0)
    {
        // .........
    }
}
