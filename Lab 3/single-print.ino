int board[4][4] = {{0, 0, 0, 0},
				   {0, 0, 0, 0},
				   {0, 0, 0, 0},
				   {0, 0, 0, 0}};

int player_psn[] = {0, 0};

void invalid_input()
{
	Serial.println("Invalid input. Please retry.");
	get_input();
}

void get_input()
{
	Serial.println("Waiting for input.");
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
	Serial.print("Player moved from ");
	Serial.print(player_psn[0]);
	Serial.print(",");
	Serial.print(player_psn[1]);
	Serial.print(" to ");
	Serial.print(psn_temp[0]);
	Serial.print(",");
	Serial.print(psn_temp[1]);
	Serial.print("\n");

	player_psn[0] = psn_temp[0];
	player_psn[1] = psn_temp[1];
}

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// Serial.println("One Loop STARTED.");
	get_input();
	// Serial.println("One Loop Completed.");
}