// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

int input_status = 0;			// indicating the input status
								// 0= none, 	1 = number_1, 
								// 2= operator, 3 = number_2,
								// 4= =
int number_1 = -100;        	// the 1ST input number
int number_2 = -100;        	// the 2ND input number
int arithmetic_operator = -1;	// 0=+, 1=-, 2=*, 3=/
int result = 0;             	// the final result

void setup()
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

    // start serial port at 9600 bps and wait for port to open:
    Serial.begin(9600);
    // wait for serial port to connect. Needed for Leonardo only
    while (!Serial) {;}

    // send a byte to establish contact until receiver responds
    establishContact();
}

void loop()
{
	// if we get an invalid byte, return and jump out
    if (Serial.available() > 0)
   {     
    if(0 == input_status)
    {
        get_input(input_status, number_1);
        show(input_status,number_1);
    }
    else if(1 == input_status)
    {
        get_input(input_status, arithmetic_operator);
        show(input_status,arithmetic_operator);
    }
    else if (2 == input_status)
    {
        get_input(input_status, number_2);
        show(input_status,number_2);
    }
    else if(3 == input_status)
    {
    	get_input(input_status, result);
    	switch(arithmetic_operator)
        {
        	case 0:
        		result=number_1+number_2;
        		break;
        	case 1:
        		result=number_1-number_2;
        		break;
        	case 2:
        		result=number_1*number_2;
        		break;
        	default:
        		result=number_1/number_2;
        }
        
        // Test Output to Debug
        Serial.println("Start Calculation!");
        Serial.print(number_1);
        Serial.print(" ");
        Serial.print(arithmetic_operator);
        Serial.print(" ");
        Serial.println(number_2);
        Serial.println(result);
	}
	else
	{
        show(input_status,result);
        input_status = 0;
    }
}
}

void get_input(int & status, int &store_target)
{
    char serial_temp[4] =  "";	// temp to store the text read from Serial
    int length = 0;				// the length of read inputted text

    // if we get an invalid byte, return and jump out
    if (!Serial.available() > 0)
        return;

    //  read up to 4 characters - put them into array temp_serial
    length = Serial.readBytesUntil('\n', serial_temp, 4);

    if(1 == status)					// input operand
    {	
    	Serial.print("input");
    	Serial.print(serial_temp[0]);
        switch(serial_temp[0])
        {
        case '+':
            store_target = 0;
            break;
        case '-':
            store_target = 1;
            break;
        case '*':
            store_target = 2;
            break;
        default:					// '/'
        	store_target = 3;
        }
    }
    {
        if(3 == length)				// negative number
            store_target = (-1) * ((serial_temp[1] - '0') * 10 + (serial_temp[2] - '0'));
        else						// non-negative number
            store_target = (serial_temp[0] - '0') * 10 + (serial_temp[1] - '0');
    }

    status++;

    // Test Output to Debug
    Serial.print("length = ");
    Serial.println(length);
    Serial.print("status = ");
    Serial.println(status);
}

void show(int status, int show_text)
{
	if(4==status)
	{
		lcd.setCursor(0,1);
		lcd.print(show_text);
	}
	else if(2==status)
	{
		switch(show_text)
		{
			case 0:
				lcd.print("+ ");
				break;
			case 1:
				lcd.print("- ");
				break;
			case 2:
				lcd.print("* ");
				break;
			default:
				lcd.print("/ ");
		}
	}
	else
	{
		if(1==status)
		{
			lcd.clear();
			lcd.setCursor(0,1);
			lcd.print("......");
			lcd.setCursor(0,0);
		}
		lcd.print(show_text);
		lcd.print(" ");
	}
}

void establishContact()
{
    while (Serial.available() <= 0)
    {
        // Serial.println("0,0,0");   // send an initial string
        delay(300);
    }
}
