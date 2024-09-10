void loop()
{

  //  New block to identify device count changes
  lastDeviceCount = deviceCount;
  deviceCount = getDeviceCount();
  //end New block
  mycounter++;

  if(lastDeviceCount != deviceCount ) {  //device count changes   this never works
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    oled.setCursor(0,0);
    //oled << "Count " << endl << "changed " << endl <<  lastDeviceCount << " " << deviceCount << endl;
    oled.display();
    delay(5000);     // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
    Serial << " The device Count Changed " << lastDeviceCount << " " <<  deviceCount << endl;

  }
  // only do these things every GETTEMPFEQ loops or before I get to the first GETTEMPFREQ
  if (mycounter % GETTEMPFEQ == 0 ||  mycounter < GETTEMPFEQ ) {
    deviceCount = getDeviceCount();
    if ( deviceCount > 0 ) {
      temperatureJob();  // do the main temprature job
    }
    //  I think this is wrong
    //lastDeviceCount = getDeviceCount();  // used to detect
  }
  buttonvalue =  digitalRead(button);
  if( debug ) {
    Serial << mycounter << " freq: " << freqChecker() << "Hz | enocderPos: ";
    Serial << encoderPos << " | buttonvalue: " << buttonvalue << endl;
  }

  //encoder
  if (prevPos != encoderPos) {
        prevPos = encoderPos;
        Serial << "encoder position: " << encoderPos << endl;
        dispatchEncoder();
  }

  if (encoderPos == 4 )  oPrintInfo();
  if (encoderPos == 5 )  oPrintInfo5();
  if (deviceCount == 0 && encoderPos < 4 && encoderPos > 0 ) oPrintNoDevices() ;

  lastime = thistime;
  delay(mydelay);
  thistime = millis();

}