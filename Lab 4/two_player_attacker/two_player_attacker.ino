#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

// ---------  [START] global variables  ---------
bool debug_mode = true;

// the pins
const int BUTTON = 10;  // D10
const int ROTATION = 1; // A1
const int TILT = 11;    // D11

// bool button_press = false;
int board[14] = {0};
int message[3] = {0, 0, 0}; // {attacker, hider, skill}
int life = 2;
int skill = 2;
// Custom Icons
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
// ---------  [END] global variables  ---------

// ---------  [START] function prototypes  ---------
void initiate_game();
// void 	button_blink();
bool button_pressed();
int rotation_location();
bool tilt_changed();

void move_board_elements();
void skill_launched();

void update_board_except_player();
void update_psn();

int judge();
void get_input();

void display();
// ---------  [END] function prototypes  ---------


void send_message()
{
  // attacker just need to send his position
  Serial.write(message[0]);
}

void read_message()
{
  while (Serial.available<=1)
  {
    delay(10);
  }
  message[1] = Serial.read();
  message[2] = Serial.read();
}

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(ROTATION, INPUT);
  pinMode(TILT, INPUT);

  lcd.clear();
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, heart);
  lcd.createChar(4, alien);
  lcd.createChar(5, plane);
  lcd.createChar(6, star);
  lcd.createChar(7, bomb);
  lcd.begin(16, 2);

  initiate_game();
}

void loop()
{
  static int count = 0;
  int game_status = 0;

  count++;
  get_input();

  static int data_received = 0;
  // for attacker
  // first send and then read
  send_message();
  read_message();

  update_psn();
  if (count % 8 == 0)
    update_board_except_player();

  display();

  game_status = judge();
  if (-1 == game_status)
  {
    delay(5000);
    setup();
    return;
  }

  delay(100);

  if (debug_mode)
  {
    Serial.print("Status: ");
    Serial.println(game_status);
    Serial.print("Message: ");
    Serial.print(message[0]);
    Serial.print(" ");
    Serial.print(message[1]);
    Serial.print(" ");
    Serial.print(message[2]);
    Serial.println("\n");
  }
}

// ============ Function Implementations ============
void initiate_game()
{
  int i = 0;
  for (i = 0; i <= 13; i++)
    board[i] = 0;

  skill = 2;
  life = 2;

  board[0] = 1;
  board[13] = 1;

  message[0] = board[0];
  message[1] = board[13];
  message[2] = 0;
}

// void button_blink()
// {
//     button_press = !button_press;
//     if(debug_mode)
//         Serial.println("Button Pressed.");
// }

/**
   [button_pressed description]
       judge whether the button is pressed or not
   @return [description]
       1:	pressed
       0:	not pressed
*/
bool button_pressed()
{
  bool status_change = false;
  if (digitalRead(BUTTON)) // the button is of a high voltage, thus pressed
  {
    status_change = true;
    if (debug_mode)
      Serial.println("Button Pressed.");
  }
  else
    Serial.println("Button NOT pressed.");
  return status_change;
}

/**
   [rotation_location description]
       Judge the location of the rotation
   @return [description]
       1:	right side
       -1:	left side
*/
int rotation_location()
{
  int threshold = 511;
  int value = 0;
  int status = -1; // -1 for left and 1 for right

  value = analogRead(ROTATION);
  if (value < threshold) // rotated to the right side
    status = 1;
  else
    status = -1;

  // debugging outputs
  if (debug_mode)
  {
    Serial.print("\tRoatation value = ");
    Serial.println(value);
    Serial.print("Roatation Status = ");
    if (status)
      Serial.println("Right");
    else
      Serial.println("Left");
  }
  return status;
}

/**
   [tilt_changed description]
       judge whether the tilt is up or down
   @return [description]
       true:	up
       false:	down
*/
bool tilt_changed()
{
  static bool up_tilt = false;
  if (digitalRead(TILT) != up_tilt)
  {
    up_tilt = !up_tilt;
    if (debug_mode)
      Serial.println("Tile Enabled");
    return true;
  }

  return false;
}

/**
   [move_board_elements description]
       move the elements on the board
*/
void move_board_elements()
{
  for (int i = 12; i >= 1; i--)
    board[i] = board[i - 1];
}

/**
   [skill_launched description]
       update the status of the board and the skill count when the skill is launched
*/
void skill_launched()
{
  for (int i = 12; i >= 1; i--)
    board[i] = 0;
  skill--;
  if (debug_mode)
    Serial.println("Skill Launched.");
}

void update_board_except_player()
{
  if (message[2] && skill > 0)
    skill_launched();
  if (board[12] == board[13])
  {
    life--;
    board[12] = 0;
    if (debug_mode)
      Serial.println("Life --");
  }
  move_board_elements();
  board[1] = board[0];
}

void update_psn()
{
  board[0] = message[0];
  board[13] = message[1]; // hider
}

/**
   [judge description]
       judge the status of the game
   @return [description]
       1:	the game is continuing
       -1:	the game ends. The plane is shot down.
*/
int judge()
{
  if (life < 0)
    return -1;
  else
    return 1;
}

void get_input()
{
  // the location of the attacker - using button
  if (button_pressed())
    message[0] = (-1) * message[0];

  // the location of the hider - using rotation
  message[1] = rotation_location();

  // the status of the skill
  if (tilt_changed())
    message[2] = 1;
  else
    message[2] = 0;
}

void display()
{
  lcd.clear();
  if (1 == board[0]) // attacker
  {
    lcd.setCursor(15, 0);
    lcd.write(byte(4));
  }
  if (-1 == board[0])
  {
    lcd.setCursor(15, 1);
    lcd.write(byte(4));
  }
  for (int i = 1; i <= 12; ++i)
  {
    if (1 == board[i])
    {
      lcd.setCursor(15 - i, 0);
      lcd.write(byte(7));
    }
    if (-1 == board[i])
    {
      lcd.setCursor(15 - i, 1);
      lcd.write(byte(7));
    }
    // Serial.print("FUCK  ");
    // Serial.println(board[i]);
  }
  if (1 == board[13]) // hider
  {
    lcd.setCursor(2, 0);
    lcd.write(byte(5));
  }
  if (-1 == board[13])
  {
    lcd.setCursor(2, 1);
    lcd.write(byte(5));
  }
  lcd.setCursor(1, 1);
  lcd.write(byte(6));
  lcd.setCursor(1, 0);
  lcd.write(byte(3));

  // Serial.print("FUCK  ");
  // Serial.println(board[13]);

  //skill
  lcd.setCursor(0, 1);
  if (0 == skill)
  {
    lcd.write(byte(0));
  }
  if (1 == skill)
  {
    lcd.write(byte(1));
  }
  if (2 == skill)
  {
    lcd.write(byte(2));
  }

  //life
  lcd.setCursor(0, 0);
  if (0 == life)
  {
    lcd.write(byte(0));
  }
  if (1 == life)
  {
    lcd.write(byte(1));
  }
  if (2 == life)
  {
    lcd.write(byte(2));
  }
}
