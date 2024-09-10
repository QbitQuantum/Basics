void setup(){
  // Voltage sensors

  for (int i; i < countVoltagePins; i++) {
    pinMode(voltagePins[i], INPUT);
  }
  
  // Heartbeat LED
  pinMode(LEDpin, OUTPUT);
  
  // Serial port is used for debug
  Serial.begin(9600);
  
  // LCD
  lcd.begin(LCDcols, LCDlines);
  
  // Welcome
  lcd.setCursor(0, 0);
  lcd.print("Paleo 2011  2012");
  
  // Relays
  initRelays();
  
  // Init watchdog
  wdt_enable(WDTO_8S);
}