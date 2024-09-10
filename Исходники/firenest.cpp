    void setupold() {
      
      //mySerial.begin(4800);
      //mySerial.println("Hello world");
      
      for (int i= 0; i<CHANNELS; i++) {
        pinMode(channels[i].button_pin,INPUT);
        digitalWrite(channels[i].button_pin,HIGH); //enable internal 20K pullup
        
        pinMode(channels[i].led_pin,OUTPUT);
        //blink leds a bit
        digitalWrite(channels[i].led_pin,HIGH);
        delay(200);
        digitalWrite(channels[i].led_pin,LOW);
      }
      
      //debug led
      //pinMode(13,OUTPUT);
      //digitalWrite(13,HIGH);
      //delay(500);
      //digitalWrite(13,LOW);
      
      xbee.begin(XBEE_BAUD);

      //discover the other XBEE's address
      discover();
      zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
      
      //send a no-op packet so that the xbees can do their magic and find each other
      payload[0] = 254;
      xbee.send(zbTx);
      
      //Flash all leds once so the user knows
      flashAll(500);

      //mySerial.println("Discovered address");
      //mySerial.print("MSB: ");
      //mySerial.println(addr64.getMsb());
      //mySerial.println(addr64.getMsb()==0x0013a200?"Yes!":"NO");
      //mySerial.print("LSB: ");
      //mySerial.println(addr64.getLsb());
      //mySerial.println(addr64.getLsb()==0x403141DA?"Yes!":"NO");
    }