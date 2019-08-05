
// the pins
const int BUTTON = 9;			// D9
const int ROTATION = 1;			// A1
const int TILT = 11;			// D11

bool button_press = false;

int board[14] = {0};
int life = 2;
int skill = 2;

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON, INPUT);
    pinMode(ROTATION, INPUT);
    pinMode(TILT, INPUT);
    attachInterrupt(BUTTON, button_blink, RISING);
    // attachInterrupt(BUTTON, tilt_blink, RISING);
    initiate_game();
}

void loop()
{
    Serial.println(button_pressed);
    Serial.println(rotation_location);
    Serial.println(tilt_changed);
    delay(500);
}


void initiate_game()
{
    for(int i = 0; i <= 13; i++)
        board[i] = 0;
    skill = 2;
    life = 2;
}


void button_blink()
{
    button_press = !button_pressed;
    Serial.println("Button Pressed.");
}

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
        Serial.println("Button Pressed.");
    }

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
    Serial.print("\tRoatation value = ");
    Serial.println(value);
    Serial.print("Roatation Status = ");
    if(status)
        Serial.println("Right");
    else
        Serial.println("Left");

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
        Serial.println("Tilt Up.");
    }
    else
    {
        up_tilt = false;
        Serial.println("Tile Down.");
    }

    // if the tilt is up, delay and change skill count
    if(up_tilt)
        delay(50);

    return up_tilt;
}

int judge()
{
	if 


}

