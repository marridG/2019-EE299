#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

byte heart[8] = {
  B00000,
  B00110,
  B01111,
  B11110,
  B01111,
  B00110,
  B00000,
  B00000,
};
byte alien[8] = {
  B00000,
  B10111,
  B11101,
  B01111,
  B11101,
  B10111,
  B00000,
  B00000,
};
byte plane[8] = {
  B01000,
  B11100,
  B10000,
  B11111,
  B10000,
  B11100,
  B01000,
  B00000,
};
byte star[8] = {
  B00000,
  B10010,
  B01110,
  B01111,
  B01110,
  B10010,
  B00000,
  B00000,
};
byte bomb[8] = {
  B00000,
  B01000,
  B11100,
  B11110,
  B11101,
  B01001,
  B00000,
  B00000,
};
byte zero[8] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
};
byte one[8] = {
  B00000,
  B00000,
  B10010,
  B11111,
  B10000,
  B00000,
  B00000,
  B00000,
};
byte two[8] = {
  B00000,
  B00000,
  B11010,
  B10101,
  B10010,
  B00000,
  B00000,
  B00000,
};
int board[14]={0,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1};
int life=2;
int skill=1;
int alienp=1;
int planep=-1;

void setup() {
  lcd.clear();
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, heart);
  lcd.createChar(4, alien);
  lcd.createChar(5, plane);
  lcd.createChar(6, star);
  lcd.createChar(7, bomb);
  lcd.begin(16,2);
}
void display()
{
  lcd.clear();
 if(1==alienp)
 {
  lcd.setCursor(15,0);
  lcd.write(byte(4));
  }
  if(-1==alienp)
  {
    lcd.setCursor(15,1);
    lcd.write(byte(4));
    }
    for(int i=0;i<14;++i)
    {
      if(1==board[i])
      {
        lcd.setCursor(15-i,0);
        lcd.write(byte(7));
        }
        if(-1==board[i])
        {
          lcd.setCursor(15-i,1);
          lcd.write(byte(7));
          }
      }
      if(1==planep)
      {
        lcd.setCursor(2,0);
        lcd.write(byte(5));
        }
        if(-1==planep)
        {
          lcd.setCursor(2,1);
          lcd.write(byte(5));
          }
       lcd.setCursor(1,1);
       lcd.write(byte(6));
       lcd.setCursor(1,0);
       lcd.write(byte(3));

       //skill
       lcd.setCursor(0,1);
       if(0==skill)
       {
        lcd.write(byte(0));
        }
        if(1==skill)
       {
        lcd.write(byte(1));
        }
        if(2==skill)
       {
        lcd.write(byte(2));
        }

        //life
        lcd.setCursor(0,0);
       if(0==life)
       {
        lcd.write(byte(0));
        }
        if(1==life)
       {
        lcd.write(byte(1));
        }
        if(2==life)
       {
        lcd.write(byte(2));
        }
  }
void loop() {
  display();
  delay(500);
}
