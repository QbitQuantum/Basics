void loop() {
    unsigned long t = millis(); // Current elapsed time, milliseconds.
    // millis() comparisons are used rather than delay() so that animation
    // speed is consistent regardless of message length & other factors.

    BTLEserial.pollACI(); // Handle BTLE operations
    aci_evt_opcode_t state = BTLEserial.getState();

    if(state != prevState) { // BTLE state change?
        switch(state) {        // Change LED flashing to show state
            case ACI_EVT_DEVICE_STARTED: LEDperiod = 1000L / 10; break;
            case ACI_EVT_CONNECTED:      LEDperiod = 1000L / 2;  break;
            case ACI_EVT_DISCONNECTED:   LEDperiod = 0L;         break;
        }
        prevState   = state;
        prevLEDtime = t;
        LEDstate    = LOW; // Any state change resets LED
        digitalWrite(LED, LEDstate);
    }

    if(LEDperiod && ((t - prevLEDtime) >= LEDperiod)) { // Handle LED flash
        prevLEDtime = t;
        LEDstate    = !LEDstate;
        digitalWrite(LED, LEDstate);
    }

    // If connected, check for input from BTLE...
    if((state == ACI_EVT_CONNECTED) && BTLEserial.available()) {
        if(BTLEserial.peek() == '#') { // Color commands start with '#'
            char color[7];
            switch(readStr(color, sizeof(color))) {
                case 4:                  // #RGB    4/4/4 RGB
                    matrix.setTextColor(matrix.Color(
                            unhex(color[1]) * 17, // Expand to 8/8/8
                            unhex(color[2]) * 17,
                            unhex(color[3]) * 17));
                    break;
                case 5:                  // #XXXX   5/6/5 RGB
                    matrix.setTextColor(
                            (unhex(color[1]) << 12) +
                            (unhex(color[2]) <<  8) +
                            (unhex(color[3]) <<  4) +
                            unhex(color[4]));
                    break;
                case 7:                  // #RRGGBB 8/8/8 RGB
                    matrix.setTextColor(matrix.Color(
                            (unhex(color[1]) << 4) + unhex(color[2]),
                            (unhex(color[3]) << 4) + unhex(color[4]),
                            (unhex(color[5]) << 4) + unhex(color[6])));
                    break;
            }
        } else { // Not color, must be message string
            msgLen      = readStr(msg, sizeof(msg)-1);
            msg[msgLen] = 0;
            msgX        = matrix.width(); // Reset scrolling
        }
    }

    if((t - prevFrameTime) >= (1000L / FPS)) { // Handle scrolling
        matrix.fillScreen(0);
        matrix.setCursor(msgX, 0);
        matrix.print(msg);
        if(--msgX < (msgLen * -6)) msgX = matrix.width(); // We must repeat!
        matrix.show();
        prevFrameTime = t;
    }
}