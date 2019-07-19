int number_of_person = 9;
float single_price = 977.50;
float discount=0.05;
float sales_tax=0.095;

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
}

void loop()
{
  float total_balance=0.0;
  
  total_balance=number_of_person*((single_price*(1-discount))*(1+sales_tax));
  
  Serial.print("Total Balance for 9 persons:\n");
  Serial.println(total_balance);
  delay(1000);
}
