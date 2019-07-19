// include the library code:
#include <LiquidCrystal.h>

const int MAX_WIDTH=16;
const int DELAY_INTERVAL=50;
int button_left=9;
int button_right=11;
int character_loc=0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7, d8 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7, d8);

void setup()
{
  pinMode(button_left, INPUT);
  pinMode(button_right, INPUT);
  // set up the LC  D's number of columns and rows:
  lcd.begin(MAX_WIDTH, 2);
  lcd.setCursor(0,0);
  lcd.print("x");
  // Serial.begin(9600);
}

void loop()
{
//  lcd.display();
//  delay(500);
  bool status_change=false;
  // if(digitalRead(button_left))
  // {
  //     delay(DELAY_INTERVAL);
  //     if(!digitalRead(button_left))
  //     {
  //       character_loc+=1;
  //     }
  //     status_change=true;
  // }
  // if(digitalRead(button_right))
  // {
  //     delay(DELAY_INTERVAL);
  //     if(!digitalRead(button_right))
  //     {
  //       character_loc-=1;
  //     }
  //     status_change=true;
  // }
  if(digitalRead(button_left))
  {
    character_loc++;
    status_change=true;
    // Serial.println("left");
  }
  else if (digitalRead(button_right))
  {
    character_loc--;
    status_change=true;
    // Serial.println("right");
  }

  if(status_change)
  {
    if(character_loc>=MAX_WIDTH)
      character_loc-=16;
    else if(character_loc<0)
      character_loc+=16;

    lcd.clear();
    lcd.setCursor(character_loc,0);
    lcd.print("x");
    delay(500);
    status_change=false;
  }

}
