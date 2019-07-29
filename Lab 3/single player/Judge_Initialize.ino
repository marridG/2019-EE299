// int board[4][4] = {};
// int player_psn[2] = {};
// int life = 0;


// initialize all the status of the game
void init_game();

// judge the status of the game
// 		-1:	Step onto a mine and die.						Game over.
// 		0:	Nothing happens - nothing / discovered mines.	Continue.
// 		1:	Step onto a mine but do not die.				Continue.
// 		99:	Reach the destination.							Game win.
int judge();


/**
 * [init_game description]
 */
void init_game()
{
    int i = 0, j = 0, k = 0;				// temp variables - for loop control

    // initialize the status of the board
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
            board[i][j] = 0;
    board[0][0] = 9;						// starting position
    board[3][3] = 10;						// ending position

    // initialize the status of the player
    life = 2;
    player_psn[0] = 0;
    player_psn[1] = 0;

    // randomly set mines on the board, except for the starting and ending positions
    k = 0;									// number of already set mines
    while(k <= 3)
    {
        i = random(4);						// get a random row number: 0-3
        j = random(4);						// get a randon column number: 0-3

        // judge whether a mine can be placed on the randomly generated position
        if(board[i][j] != 1 && board[i][j] != 9 && board[i][j] != 10)
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
    switch(board[player_psn[0]][player_psn[1]])
    {
    case 1:								// step onto a undicovered mine
        board[player_psn[0]][player_psn[1]] = 2;
        life--;
        if(life < 0)					// no extra opportunities, die!
            return -1;
        else							// opportunities remain, continue game
            return 1;
    case 10:							// get to the destination
        return 99;
    case 0:								// step onto a undiscovered nothing position
        board[player_psn[0]][player_psn[1]] = 5;
    case 5:								// step onto a discovered nothing position
    default:							// step onto a discovered mine
        return 0;
    }
}