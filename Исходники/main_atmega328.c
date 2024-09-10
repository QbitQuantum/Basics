void setup()
{
  SIM900.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  lcd.setCursor(3,0);
  lcd.print("CAR THEFT");
  lcd.setCursor(1,1);
  lcd.print("DETECTION SYS");
  delay(2000);
  lcd.clear();
}