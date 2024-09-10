void setup()/*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(20, 4);        // initialize the lcd for 20 chars 4 lines and turn on backlight
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // --- button setup

  pinMode(RunBtn, INPUT);
  pinMode(ChangeScanBtn, INPUT);

  digitalWrite(RunBtn, HIGH);
  digitalWrite(ChangeScanBtn, HIGH);


  pinMode(clampPin, OUTPUT);      // sets the digital pin as OUTPUT to drive FET clamp)

  pinMode(5, OUTPUT);      // sets the digital pin as output
  pinMode(6, OUTPUT);      // sets the digital pin as output
  pinMode(7, OUTPUT);      // sets the digital pin as output
  pinMode(11, OUTPUT);     // pin11= PWM  output / frequency output //Will Turner - This could go to pin 5 from 11.  CHANGED TO 9 AS IT WOULDNT REACH OTHERS


  // ------- Quick 3 blinks of backlight  -------------
  for (int i = 0; i < 3; i++)
  {
    lcd.backlight();
    delay(20);
    lcd.noBacklight();
    delay(20);
  }
  lcd.backlight(); // finish with backlight on

  //-------- Initialise display ----------------
  // NOTE: Cursor Position: CHAR, LINE) start at 0
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Tension Tester v1.5 "); // sets up the screen for the wire number and layer number being recorded
  lcd.setCursor(0, 2);
  lcd.print("     Press Run      ");

  Setup_timer2();

  // disable interrupts to avoid timing distortion
  cbi (TIMSK0, TOIE0);             // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2, TOIE2);             // enable Timer2 Interrupt

  dfreq = 1000.0;                  // initial output frequency = 1000.o Hz
  tword_m = pow(2, 32) * dfreq / refclk; // calulate DDS new tuning word

  // setup start and end frequencies of sweep

  // setup initial values for loop
  adcflag = false;

  analogval = 0;
  digitalWrite(clampPin, HIGH);    // sets the pin high to short out large signals before amp (using a FET as clamp)
  avgcnt = 0.0;
}