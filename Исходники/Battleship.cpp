int main() {
  // Initialize arduino, serial communication, lcd screen, buttons (and
  // internal pull-up resistors), LED pins, and SD card.
  init();
  Serial.begin(9600);
  Serial3.begin(9600);
  while(Serial3.available()) {Serial3.read();} // Clean the Serial line
  tft.initR(INITR_BLACKTAB);

  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);
  pinMode(Button1, INPUT);
  digitalWrite(Button1, HIGH);
  for (int i = 0; i < 10; ++i) {
    pinMode(i + 22, OUTPUT);
  }
  int click;    // This will be used to continue from the Title Screen

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }
  Serial.println("OK!");

  // do the auto calibration of the cursor (found in Cursor.cpp)
  Initialize_Cursor();


  while(true) {
    // draw the title screen, and set the turn pin to neutral (blue)
    lcd_image_draw(&Images[title], &tft, 0, 0, 0, 0, 128, 160 );
    digitalWrite(bluePin, HIGH);
    while (true) { // leave the title page with a joystick button press.
      click = digitalRead(SEL);
      if (!click) {break;}
    }
    // draw a black screen
    tft.fillScreen(0);
    // draw the border image (note that the numbers (0-9) and
    // letters (A-J) are just for appearance and aren't actually used by
    // the program).
    lcd_image_draw(&Images[border], &tft, 0, 0, 0, 0, 128, 128 );

    // initialize My_Ocean so that each value is 0 (water)
    for( int i=0; i<100; i++ ) {
      My_Ocean[i] = 0;
    }
    // initialize Their_Ocean so that each value is 1 (miss). This needs to
    // be nonzero for the first drawing of the screen (occurs on line 47
    // of Place_Ships.cpp) and will be set to 0 after.
    for( int i=0; i<100; i++ ) {
      Their_Ocean[i] = 1;
    }
    //==================== Initialization complete =================

    // Allows a player to place their ships
    My_Ships = Place_Ships(My_Ocean, Their_Ocean);
    // set Their_Ocean so that each value is 0 (water).
    for( int i=0; i<100; i++ ) {
      Their_Ocean[i] = 0;
    }
    // One arduino should read high, and the other should read low
    // (see wiring instructions for more detail). This determines who
    // gets the first turn.
    bool Turn = digitalRead(13);
    // Initialize the number of ships remaining for each player to 5.
    // can be set to 1 for a "debug" mode to see the victory/reset more
    // quickly.
    int Mine_Alive = 5;
    int Their_Alive = 5;

    // Turn on all the LED's initially (because all 10 ships should be
    // alive).
    for (int i = 0; i < 10; i++) {
      digitalWrite(22+i , HIGH);
    }

    // Connect to opponent. One arduino writes 'R' for ready, then waits
    // to receive a response. The other waits to read 'R' first, then
    // writes it.
    Write_Message("Connecting...");
    if( Turn == 1 ) {
      Serial3.write('R');
      while( Serial3.read() !='R' ) {}
    }
    else {
      while( Serial3.read() !='R' ) {}
      Serial3.write('R');
    }

    //==================== Ready to communicate/play ===============

    // Loop until either player has no ships left.
    while((Mine_Alive != 0) && (Their_Alive != 0)) {

      // My turn
      if( Turn == 1 ) {
        // draw a red square in the top left corner (because we will
        // view what we know of Their_Ocean).
        tft.fillRect(0, 0, 8, 8, 0xF800);
        // Make the LED green because it is our turn.
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
        // Draw Their_Ocean
        Draw_Screen(Their_Ocean, My_Ocean);
        // Indicate our turn at the bottom of the screen
        Write_Message("Your Turn");
        // Call Fire. It will return one (decrementing Their_Alive)
        // if it sinks a ship.
        Their_Alive = Their_Alive - Fire(Their_Ocean);
        // change turns
        Turn = 0;
      }
      else if( Turn == 0 ) {
        // draw a green square in the top left corner (because we will
        // view our own ships (My_Ocean).
        tft.fillRect(0, 0, 8, 8, 0x07E0);
        // Make the LED red because it is their turn.
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        // draw My_Ocean
        Draw_Screen(My_Ocean, Their_Ocean);
        // Indicate their turn at the bottom of the screen
        Write_Message("Opponent's turn");
        // Call Get_Shot_At. It will return one (and will decrement
        // Mine_Alive) if a ship is sunk.
        Mine_Alive = Mine_Alive-Get_Shot_At(My_Ocean, My_Ships);
        // change turns
        Turn = 1;
      }
      // update the LEDs based on the number of ships left alive. The
      // Green LEDS represent the number of ships you have alive while
      // the Red ones do the same for the other players ships.
      for (int i = 5; i > 0; i--) {
        if (Their_Alive >= i) {
          digitalWrite(21 + 2*i , HIGH);
        }
        else {
          digitalWrite(21 + 2*i ,  LOW);
        }
      }
      for (int i = 5; i > 0; i--) {
        if (Mine_Alive >= i) {
          digitalWrite(20 + 2*i , HIGH);
        }
        else {
          digitalWrite(20 + 2*i , LOW);
        }
      }
    }

    // The delays help everything to sync up with the sound effects.
    delay(2000);
    if( Mine_Alive > 0 ) {
      // The number sent to the 'Victory_Cascade()' is to indicate which
      // set of LEDS are to be cascaded based on which player is the
      // winner of the game. The spaces in the message are in place to
      // avoid the word in the messages being cut off
      Write_Message("You won! Please hold joystick button to   play again.");
      Sound_Victory();
      Victory_Cascade(22);
    }
    else {
    delay(3000);
      Write_Message("You lost! Please holdjoystick button to  play again.");
      Victory_Cascade(23);
    }
  }
  Serial3.end();
  Serial.end();
  return 0;           // End of function
}