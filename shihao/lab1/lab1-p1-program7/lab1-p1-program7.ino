//-------------------------
//Module name:
//  lab1-part1-program7
//
//Description:
//   Starting with the working C code, hw1.ino 
//   and your working C code forhomework assignment problem 1, 
//   modify the code for hw1.ino to incorporate 
//   your code for homework problem 1.
//
//Author:
//   Tutian Tang, Ziliang Guo, Shihao Piao
//Rev.0 14 July 2019
//-------------------------

float discount=0.05;           //initialize the discount percent
float single_price = 977.50;   //initialize the single price
int number_of_person = 9;      //initialize the persons' number
float sales_tax=0.095;         //initialize the sales tax percent

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
}

void loop()
{
  //initialize the total balance
  float total_balance=0.;
  //compute the total balance
  total_balance=number_of_person*((single_price*(1-discount))*(1+sales_tax));
  //print the price
  Serial.print("Total Balance for 9 persons are:\n");
  Serial.println(total_balance);
  delay(1000);
}
