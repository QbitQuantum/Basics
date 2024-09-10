void main(void)
{
    //***************** BEGINNING OF ETHERNET SETUP [DONT EDIT] *****************//
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n", eth.getIPAddress());

    UDPSocket server;
    server.bind(ECHO_SERVER_PORT);

    Endpoint client;
    char buffer[256];

    //***************** END OF ETHERNET SETUP **********************************//

    //***************** BEGINNING OF WIRELESS SETUP [DONT EDIT] *****************//

    uint8_t channel = 6;
    //Set the Channel. 0 is default, 15 is max
    mrf.SetChannel(channel);
    //Start the timer
    timer.start();

    //***************** END OF WIRELESS SETUP **********************************//
    raiseAllPins();
    dropAllPins();


    speedChecker.attach(&speedLogic,0.005); //sets ticker for interrupts
    dcOUT=0; // turns DC motor off initially

    int cycles = 0;
    int flush = 0;
    int startChar =0;
    while(1) {
        dcPWM.write(dutyCycle);
        cycles = cycles-1;

        if(needsInput==true) {
            //What MBED is receiving from client?
            if(flush) {
                int lengthBuffer = strlen(buffer);
                for(int i = 0; i <lengthBuffer; i++) {
                    buffer[i]='\0';
                }
            }
            printf("\nWait for packet...\n\r");
            lightShow.drawChar('@'); //this should draw the character on the screen
            int n = server.receiveFrom(client, buffer, sizeof(buffer));
            printf("\nReceived packet...\n\r");
            printf("\nReceived integer n...%i\n\r",n);
            buffer[n]='\0';
            printf("\nyour word is: %s\n\r",buffer);
            server.sendTo(client, buffer, n); //echo protocol
            needsInput=false;
            cycles=n;
            /*revive code*/
            sendDelay = slowSpeed; //pins
            dutyCycle = slowMotor; //motor
            dcOUT = 1; //turn on motor
            off=false;
            slow = true;
            startChar=0;

        }
        if(cycles<=0) {
            needsInput= true;
            slow = false;
            off=true;
            dcOUT = 0; //turn motor off
            sendDelay = slowSpeed; //pins
            dutyCycle = slowMotor; //for whenever it turns on after you turned it off using REDUCE
        }

        if(!off) {
            char character = getNextCharacter(startChar, buffer);
            startChar=1;
            printf("\nchar: %c\n\r",character);
            int pinBinary = braille.matchCharacter(character);

            if(braille.isNumber(character)) {
                handleNumberCase(character);
            }
            led1=1;
            lightShow.drawChar(character); //this should draw the character on the screen
            led1=0;
            wait_ms(sendDelay);

            sendNumber(pinBinary);
            printf("Pinbinary: %i\n\r",pinBinary);

            //***** ACKNOWLEDGE CODE ******//

            int recLength = rf_receive(rxbuffer,128);
            while(recLength<=0) {
                led2=1;
                recLength = rf_receive(rxbuffer,128);
            }
            led2=0;
            //***** END ACKNOWLEDGE CODE ******//

        }//end if motor stopped code
        dropAllPins();
    }//end while loop
}//end all code