int board[4][4] = {{0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

int player_psn[] = {0, 0};
int life = 1;

void display_set_board()
{
    for (int j = 0; j < 4; ++j)
    {
        //cout<<"--------------\n";
        Serial.print("           ");
        for (int i = 0; i < 4; ++i)
        {
            switch (board[j][i])
            {
            case 0:						// no mines
                Serial.print("  ");
                break;
            default:					// a mine here
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

/**
 * 29 Jul
 */
void set_board()
{
    int opponent_board[4][4] = {{0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int input_row = -1;
    int input_col = -1;

    while (Serial.available() <= 0)
    {
        delay(100);
    }

    Serial.println("===== Set mines for the other player =====");
    Serial.println("The locations of the 4*4 board starts at (0,0) and ends at (3,3).");
    Serial.println("You can set altogether 4 mines. Please do not set mines at (0,0) or (3,3).\n");

    // set the 1 st mine
    while(1)
    {
        Serial.println("Please enter the ROW of the 1 ST mine:");
        input_row = Serial.read() - '0';
        Serial.println("Please enter the COLUMN of the 1 ST mine:");
        input_col = Serial.read() - '0';
        if(1 != opponent_board[input_row][input_col] || (input_row + input_col != 0))
        {
            pponent_board[input_row][input_col] = 1;
            display_set_board();
            break;
        }
        else
            Serial.println("Invalid mine location. Please try again!\n");
    }

    // set the 2 nd mine
    while(2)
    {
        Serial.println("Please enter the ROW of the 2 ND mine:");
        input_row = Serial.read() - '0';
        Serial.println("Please enter the COLUMN of the 2 ND mine:");
        input_col = Serial.read() - '0';
        if(1 != opponent_board[input_row][input_col] || (input_row + input_col != 0))
        {
            pponent_board[input_row][input_col] = 1;
            display_set_board();
            break;
        }
        else
            Serial.println("Invalid mine location. Please try again!\n");
    }

    // set the 3 rd mine
    while(3)
    {
        Serial.println("Please enter the ROW of the 3 RD mine:");
        input_row = Serial.read() - '0';
        Serial.println("Please enter the COLUMN of the 3 RD mine:");
        input_col = Serial.read() - '0';
        if(1 != opponent_board[input_row][input_col] || (input_row + input_col != 0))
        {
            pponent_board[input_row][input_col] = 1;
            display_set_board();
            break;
        }
        else
            Serial.println("Invalid mine location. Please try again!\n");
    }

    // set the 4 th mine
    while(4)
    {
        Serial.println("Please enter the ROW of the 4 TH mine:");
        input_row = Serial.read() - '0';
        Serial.println("Please enter the COLUMN of the 4 TH mine:");
        input_col = Serial.read() - '0';
        if(1 != opponent_board[input_row][input_col] || (input_row + input_col != 0))
        {
            pponent_board[input_row][input_col] = 1;
            display_set_board();
            break;
        }
        else
            Serial.println("Invalid mine location. Please try again!\n");
    }

    Serial.println("\nOpponent Board Set!\n");

    // transmit
    Serial.println("--- Transmitting ---");
    //..........
    // transimit end
    Seiral.println("===== [END] Set mines =====\n");
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

    // get the locations of the mines from I2C and set the board
    k = 0; // number of already set mines
    //........
    board[i][j] = 1;
}

/**
 * [judge description]
 * @return [description] return <int> numbers indicating different status
 *     -1:	Step onto a mine and die.						Game over.
 *     0:	Nothing happens - nothing / discovered mines.	Continue.
 *     1:	Step onto a mine but do not die.				Continue.
 *     99:	Reach the destination.							Game win.
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

void clean_up()
{
    init_game();
    delay(3000);
    Serial.println("\n\n--------------- NEW GAME ---------------\n\n");
    display();
}

void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));
    clean_up();
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
        clean_up();
    }
    else if (99 == judge_state)
    {
        display(true);
        Serial.println("Congratulations!!!!!!!!");
        Serial.println("Congratulations!!!!!!!!");
        Serial.println("Congratulations!!!!!!!!");
        clean_up();
    }
    else
    {
        display();
    }
}