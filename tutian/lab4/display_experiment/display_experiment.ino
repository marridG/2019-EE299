int PIN_SPEAKER = 9;
int length = 25;
char notes[] = "ggagCbggagDCggGECbaffECDC";
int beats[] = {1,1,2,2,2,4, 1,1,2,2,2,4, 1,1,2,2,2,2,2, 1,1,2,2,2,4,1};
int tempo = 300;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PIN_SPEAKER, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIN_SPEAKER, LOW);
    delayMicroseconds(tone);
  }
}
 
void playNote(char note, int duration) {
  char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G'};
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 853, 759, 716, 637, 568};
 
  for (int i = 0; i < 12; i++) {
    if (names[i] == note) {
      Serial.print("value:");
      Serial.println(note);
      playTone(tones[i]*2, duration);
    }
  }
}
 
void setup() {
  pinMode(PIN_SPEAKER, OUTPUT);
}
 
void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); 
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2); 
  }
}
