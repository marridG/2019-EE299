bool debug_mode = true;

// the pins
const int BUTTON = 9;			// D9
const int ROTATION = 1;			// A1
const int TILT = 11;			// D11

// bool button_press = false;

int board[14] = {0};
int message[3] = {0, 0, 0};
int life = 2;
int skill = 2;

// function list
void 	initiate_game();
// void 	button_blink();
bool 	button_pressed();
bool 	rotation_location();
bool 	tilt_changed();

void 	move_board_elements();
void 	skill_launched();

void 	update_board_except_player();
int 	judge();
void 	get_input();

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON, INPUT);
    pinMode(ROTATION, INPUT);
    pinMode(TILT, INPUT);
    initiate_game();
}

void loop()
{
    int game_status = 0;
    get_input();
    update_board_except_player();
    game_status = judge();
    if(debug_mode)
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

    delay(2000);
}


void initiate_game()
{
    int i = 0;
    for(i = 0; i <= 13; i++)
        board[i] = 0;
    for(int i = 0; i <= 3; i++)
        message[i] = 0;
    skill = 2;
    life = 2;
}

// void button_blink()
// {
//     button_press = !button_press;
//     if(debug_mode)
//         Serial.println("Button Pressed.");
// }

/**
 * [button_pressed description]
 *     judge whether the button is pressed or not
 * @return [description]
 *     1:	pressed
 *     0:	not pressed
 */
bool button_pressed()
{
    bool status_change = false;
    if(digitalRead(BUTTON))        // the button is of a high voltage, thus pressed
    {
        status_change = true;
        if(debug_mode)
            Serial.println("Button Pressed.");
    }
    else
        Serial.println("Button NOT pressed.");

    // if a button is pressed, delay
    if(status_change)
        delay(50);

    return status_change;
}

/**
 * [rotation_location description]
 *     Judge the location of the rotation
 * @return [description]
 *     true:	right side
 *     false:	left side
 */
bool rotation_location()
{
    int threshold = 511;
    int value = 0;
    bool status = false;		// false for left and true for right

    value = analogRead(ROTATION);
    if(value > threshold)		// rotated to the right side
        status = true;
    else
        status = false;

    // debugging outputs
    if(debug_mode)
    {
        Serial.print("\tRoatation value = ");
        Serial.println(value);
        Serial.print("Roatation Status = ");
        if(status)
            Serial.println("Right");
        else
            Serial.println("Left");
    }
    delay(50);
    return status;
}

/**
 * [tilt_changed description]
 *     judge whether the tilt is up or down
 * @return [description]
 *     true:	up
 *     false:	down
 */
bool tilt_changed()
{
    bool up_tilt = false;
    if(digitalRead(TILT))
    {
        up_tilt = true;
        if(debug_mode)
            Serial.println("Tilt Up.");
    }
    else
    {
        up_tilt = false;
        if(debug_mode)
            Serial.println("Tile Down.");
    }

    // if the tilt is up, delay
    if(up_tilt)
        delay(50);

    return up_tilt;
}

/**
 * [move_board_elements description]
 *     move the elements on the board
 */
void move_board_elements()
{
    for(int i = 12; i >= 1; i--)
        board[i] = board[i - 1];
}

/**
 * [skill_launched description]
 *     update the status of the board and the skill count when the skill is launched
 */
void skill_launched()
{
    for(int i = 12; i >= 1; i--)
        board[i] = 0;
    skill--;
    if(debug_mode)
        Serial.println("Skill Launched.");
}


void update_board_except_player()
{
    if(message[0])
        skill_launched();
    if(board[12] == board[13])
    {
        life--;
        board[12] = 0;
        if(debug_mode)
            Serial.println("Life --");
    }
    move_board_elements();
    board[1] = board[0];
}

/**
 * [judge description]
 *     judge the status of the game
 * @return [description]
 *     1:	the game is continuing
 *     -1:	the game ends. The plane is shot down.
 */
int judge()
{
    if(life < 0)
        return -1;
    else
        return 1;
}

void get_input()
{
    // the location of the attacker - using button
    if(button_pressed())
        message[0] = !message[0];

    // the location of the hider - using rotation
    message[1] = rotation_location();

    // the status of the skill
    if(tilt_changed())
        message[2] = !message[2];
}
