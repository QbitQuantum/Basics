void setup() {
  Serial.begin(9600);
  pinMode(SOILSENSOR, INPUT);
  pinMode(PUMPPIN, OUTPUT);
  
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  dht.begin();
}