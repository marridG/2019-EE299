#include <Wire.h>

int board[4][4] = {{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}};
int opponent_board[4][4] = {{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}};

int player_psn[] = {0, 0};
int life = 1;

int bombs[4][2] = {0};
int opponent_status = -99; // 2 for bombs set, -1 for he loses, 99 for he wins

void display_set_board()
{
    for (int j = 0; j < 4; ++j)
    {
        //cout<<"--------------\n";
        Serial.print("           ");
        for (int i = 0; i < 4; ++i)
        {
            switch (opponent_board[j][i])
            {
            case 0: // no mines
                Serial.print("  ");
                break;
            default: // a mine here
                Serial.print("* ");
                break;
            }

            if (3 == i)
                Serial.print("\n");
        }
    }
    //cout<<"--------------\n";
}

void display(bool show_bomb = false)
{
    int flag;
    for (int j = 0; j < 4; ++j)
    {
        //cout<<"--------------\n";
        Serial.print("           ");
        for (int i = 0; i < 4; ++i)
        {
            if (player_psn[0] == j && player_psn[1] == i)
            {
                Serial.print("@ ");
                if (player_psn[1] == 3)
                {
                    Serial.print('\n');
                }
                continue;
            }
            flag = board[j][i];

            switch (flag)
            {
            case 0:
            {
                Serial.print("  ");
                break;
            }
            case 1:
            {
                if (show_bomb)
                {
                    Serial.print("* ");
                }
                else
                {
                    Serial.print("  ");
                }
                break;
            }
            case 2:
            {
                Serial.print("X ");
                break;
            }
            case 5:
            {
                Serial.print(". ");
                break;
            }
            case 9:
            {
                Serial.print("> ");
                break;
            }
            case 10:
            {
                Serial.print("> ");
                break;
            }

            default:
                break;
            }

            if (3 == i)
                Serial.print("\n");
        }
    }
    //cout<<"--------------\n";
    Serial.print("Life: ");
    Serial.println(life);
}

void set_board_print_count(bool row_0_col_1, int num)
{
    if (row_0_col_1)
        Serial.print("Please enter the COLUMN of the");
    else
        Serial.print("Please enter the ROW of the");

    if (1 == num)
        Serial.println(" 1 ST mine:");
    else if (2 == num)
        Serial.println(" 2 ND mine:");
    else if (3 == num)
        Serial.println(" 3 RD mine:");
    else
        Serial.println(" 4 TH mine:");
}

void wait_till_serial_available()
{
    while (Serial.available() <= 0)
        delay(100);
}

bool set_board_get_input(int loc_count)
{
    int loc_row = 0, loc_col = 0;
    bool invalid_input = true;

    // input ROW
    while (1)
    {
        set_board_print_count(false, loc_count);
        wait_till_serial_available();
        loc_row = Serial.read() - '0';

        if (loc_row < 0 || loc_row > 3)
            Serial.println("Wrong Input Index!");
        else
            break;
    }

    // input COLUMN
    while (1)
    {
        set_board_print_count(true, loc_count);
        wait_till_serial_available();
        loc_col = Serial.read() - '0';

        if (loc_col < 0 || loc_col > 3)
            Serial.println("Wrong Input Index!");
        else
            break;
    }

    invalid_input = (0 == loc_row && 0 == loc_col) || (3 == loc_row && 3 == loc_col) || (1 == opponent_board[loc_row][loc_col]);
    if (invalid_input)
    {
        Serial.println("Invalid input location. Please try again.");
        return false;
    }
    else
    {
        opponent_board[loc_row][loc_col] = 1;
        return true;
    }
}

/**
 * 29 Jul
 */
void set_board()
{
    Serial.println("===== Set mines for the other player =====");
    Serial.println("The locations of the 4*4 board starts at (0,0) and ends at (3,3).");
    Serial.println("You can set altogether 4 mines. Please do not set mines at (0,0) or (3,3).\n");

    for (int i = 1; i <= 4; i++)
    {
        while (!set_board_get_input(i))
        {
            delay(100);
        }
    }

    Serial.println("\nYou have set the bombs for the opponent!\n");
}

void init_game()
{
    int i = 0, j = 0, k = 0; // temp variables - for loop control

    // initialize the status of the board
    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++)
            board[i][j] = 0;
    board[0][0] = 9;  // starting position
    board[3][3] = 10; // ending position

    // initialize the status of the player
    life = 2;
    player_psn[0] = 0;
    player_psn[1] = 0;

    // set board
    set_board();

    send_bombs();

    if (2 != opponent_status)
    {
        Serial.println("Waiting for the opponent...");
    }
    while (2 != opponent_status)
    {
        delay(100);
    }
}

/**
 * [judge description]
 * @return [description] return <int> numbers indicating different status
 *     -1:  Step onto a mine and die.                       Game over.
 *     0:   Nothing happens - nothing / discovered mines.   Continue.
 *     1:   Step onto a mine but do not die.                Continue.
 *     99:  Reach the destination.                          Game win.
 */
int judge()
{
    // judge the status of the current location
    switch (board[player_psn[0]][player_psn[1]])
    {
    case 1: // step onto a undicovered mine
        board[player_psn[0]][player_psn[1]] = 2;
        life--;
        if (life < 0) // no extra opportunities, die!
            return -1;
        else // opportunities remain, continue game
            return 1;
    case 10: // get to the destination
        return 99;
    case 0: // step onto a undiscovered nothing position
        board[player_psn[0]][player_psn[1]] = 5;
    case 5:  // step onto a discovered nothing position
    default: // step onto a discovered mine
        return 0;
    }
}

void invalid_input()
{
    Serial.println("Invalid input. Please retry.");
    get_input();
}

void get_input()
{
    Serial.println("\n\n=== Waiting for input ===");
    while (Serial.available() <= 0)
    {
        delay(100);
    }

    char input_char = Serial.read();

    int psn_temp[2] = {0, 0}; // int psn_temp[2] = {player_psn[0], player_psn[1]}; leads to an error
    psn_temp[0] = player_psn[0];
    psn_temp[1] = player_psn[1];

    switch (input_char)
    {
    case 'W':
    case 'w':
    {
        psn_temp[0]--;
        break;
    }
    case 'S':
    case 's':
    {
        psn_temp[0]++;
        break;
    }
    case 'A':
    case 'a':
    {
        psn_temp[1]--;
        break;
    }
    case 'D':
    case 'd':
    {
        psn_temp[1]++;
        break;
    }
    default:
    {
        invalid_input();
        break;
    }
    }
    // Switch end

    // check if the position is valid.
    if (!(psn_temp[0] <= 3 && psn_temp[0] >= 0 && psn_temp[1] <= 3 && psn_temp[1] >= 0))
    {
        invalid_input();
        return;
    }
    // valid
    Serial.print("\nPlayer moved from (");
    Serial.print(player_psn[0]);
    Serial.print(",");
    Serial.print(player_psn[1]);
    Serial.print(") to (");
    Serial.print(psn_temp[0]);
    Serial.print(",");
    Serial.print(psn_temp[1]);
    Serial.print(").\n");

    player_psn[0] = psn_temp[0];
    player_psn[1] = psn_temp[1];
}

void new_game()
{

    init_game();
    delay(1000);
    Serial.println("\n\n--------------- NEW GAME ---------------\n\n");
    display();
}

void receiveEvent(int howMany)
{
    Serial.print(howMany);
    Serial.print(" Bytes received.\n");
    if (8 == howMany)
    {
        Serial.print("\nReceiving the board from master...");
        for (int i = 0; i < 4; i++)
        {
            int x = Wire.read();
            int y = Wire.read();
            board[x][y] = 1;
        }
        Serial.print("OK.\n");
        opponent_status = 2;
    }

    else if (1 == howMany)
    {
        Serial.print("Your opponent has ");
        int status = Wire.read();
        if (-1 == status)
        {
            Serial.println("lost the game!");
            opponent_status = -1;
        }
        else if (99 == status)
        {
            Serial.println("won the game!");
            opponent_status = 99;
        }
        else
        {
            Serial.print("\nBAD MESSAGE RECEIVED: ");
            Serial.print(status);
            Serial.print("\n");
        }
    }
}

void send_bombs()
{
    Wire.begin(); // Become Master
    Serial.println("Sending the bombs...");

    Wire.beginTransmission(4); // transmit to device #4

    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 1; j++)
            Wire.write(bombs[i][j]);

    int temp = Wire.endTransmission(); // ends the transmission

    Serial.print("Over. Return value ");
    Serial.print(temp);
    Serial.print("\n");

    // Convert back to slave
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
}

void end_message(int my_state)
{
    Wire.begin(); // Become Master
    Serial.println("Sending the result...");

    Wire.beginTransmission(4); // transmit to device #4

    Wire.write(my_state);

    int temp = Wire.endTransmission(); // ends the transmission

    Serial.print("Over. Return value ");
    Serial.print(temp);
    Serial.print("\n");


    if (-2 == opponent_status)
    {
        Serial.println("Waiting for your opponent...")
    }
    while (-2 == opponent_status)
    {
        delay(100);
    }

    delay(3000);

}

void setup()
{
    Serial.begin(9600);
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
    randomSeed(analogRead(0));
    new_game();
}

void loop()
{
    get_input();
    int judge_state = judge();
    if (-1 == judge_state)
    {
        display(true);
        Serial.println("BOOOOOOOOOOOM");
        Serial.println("BOOOOOOOOOOOM");
        Serial.println("BOOOOOOOOOOOM");

        end_message(judge_state);

        clean_up();
    }
    else if (99 == judge_state)
    {
        display(true);
        Serial.println("Congratulations!!!!!!!!");
        Serial.println("Congratulations!!!!!!!!");
        Serial.println("Congratulations!!!!!!!!");

        end_message(judge_state);

        clean_up();
    }
    else
    {
        display();
    }
}