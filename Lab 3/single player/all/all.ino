int board[4][4] = {{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}};

int player_psn[] = {0, 0};//player position
int life = 1;
//prepare for the display
char board_char[] = {' ', '*', 'X', '!', '!', '.', '!', '!', '!', '>', '>'};

//--------------------------------------------
//display
//
//Purpose:
//  display the result and games on the monitor
//parameters:
//  player position and show_bomb
//
//Method:
//  judge the position and the mine position and use 
//  char array to choose the punctuation we want to use.
// 
//-------------------------------------------

void display(bool show_bomb = false)
{
    Serial.print("           +---+---+---+---+\n");
    //use for loop print the board
    for (int j = 0; j < 4; ++j)
    {
        Serial.print("           |");
        for (int i = 0; i < 4; ++i)
        {
            Serial.print(" ");
            if (player_psn[0] == j && player_psn[1] == i)
            {
                Serial.print("@ |");
                continue;
            }

            if (1 == board[j][i])
            {
                if (show_bomb)
                {
                    Serial.print("* |");
                    continue;
                }
                // else
                Serial.print("  |");
                continue;
            }
            // else
            Serial.print(board_char[board[j][i]]);
            Serial.print(" |");
        }
        Serial.print("\n           +---+---+---+---+\n");
    }
    Serial.print("Life: ");
    Serial.println(life);
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

    // randomly set mines on the board, except for the starting and ending positions
    k = 0; // number of already set mines
    while (k <= 3)
    {
        i = random(4); // get a random row number: 0-3
        j = random(4); // get a randon column number: 0-3

        // judge whether a mine can be placed on the randomly generated position
        if (board[i][j] != 1 && board[i][j] != 9 && board[i][j] != 10)
        {
            board[i][j] = 1;
            k++;
        }
    }
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
