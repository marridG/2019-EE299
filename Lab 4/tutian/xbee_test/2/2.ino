int led = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  if(Serial.available()>0)
  {
    led++;
    digitalWrite(13, LOW);
  }
}
