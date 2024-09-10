int main()
{
    unsigned int userInputLength = 0;
    int readflags = O_RDWR | O_NONBLOCK | O_NOCTTY;
    int readFile = 0;
    char userInput [64];

    setCapture(0,1);
    setADCParams(adcOffsetLeft, adcOffsetRight, adcGainLeft, adcGainRight);
    
    // Do this one again, because it doesn't seem to reliably go through.
    setADCParams(adcOffsetLeft, adcOffsetRight, adcGainLeft, adcGainRight);
    printHelp();
    
    
    while(1)
    {
        // Check if any user input from terminal...
        readFile = open("/dev/jtag_uart", readflags);
        userInputLength = read(readFile,userInput,64);
        readFile = close(readFile);

        if(userInputLength > 0 && userInput[userInputLength-1] == '\n')
        {
                userInput[userInputLength-1] = 0;
                //userInput[userInputLength-2] = 0;
                processCommand(userInput, userInputLength);
            userInputLength = 0;
            userInput[0] = 0;
            
        }
    }// end while(1)

}