    // ---------------------
void serialParse(void)
{
    char charCh;
    byte hexRead, oldHexRead;
  
    charCh = getChar();
    if (!charCh) return;

    if (sysStat & ST_DEBUG_MODE)        // Super commands for Monitor
    {
        rs485TransmitEna();
        putChar(charCh);

        switch(charCh)
        {
            case 'd':
                putStr("\tNode ID switch test.\n\r");
                putStr("\tHit any key to quit.\n\r");
                rs485TransmitDisa();
                while(1)
                {                  
                    charCh = getChar();
                    if (charCh) break;
                    hexRead = readNodeSw();
                    if (hexRead != oldHexRead)
                    {
                        rs485TransmitEna();
                        sprintf(ioBfr, "\n\r Node ID: %02Xh", hexRead);
                        putStr(ioBfr);
                        oldHexRead = hexRead;
                        rs485TransmitDisa();
                    }
                }
                break;

            case 'f':
                putStr("\tFlood sensor test: ");
                adcFloodSensor(ADC_LOQUACIOUS);
                break;

            case 'h':
                adcRHumid(ADC_LOQUACIOUS);
                break;

            case 'r':
                reportInfo();             
                break;

            case 't':
                adcTemper(ADC_LOQUACIOUS);
                break;

            case 'T':
                adcTemperSecondary(ADC_LOQUACIOUS);
                break;


            case '1':
                RELAY1 ^= 1;
                if (RELAY1) putStr("\tRelay 1 on");
                else putStr("\tRelay 1 off");
                break;

            case '2':
                RELAY2 ^= 1;
                if (RELAY2) putStr("\tRelay 2 on");
                else putStr("\tRelay 2 off");
                break;

            case '3':
                SwiPwr1 ^= 1;
                if (SwiPwr1) putStr("\tSwi Pwr1 on");
                else putStr("\tSwi Pwr1 off");
                break;

            case '4':
                SwiPwr2 ^= 1;
                if (SwiPwr2) putStr("\tSwi Pwr2 on");
                else putStr("\tSwi Pwr2 off");
                break;

            case '?':
                menuDisplay();                
                break;
        }                       // EO switch
        putPrompt();
        rs485TransmitDisa();
    }       // EO if debug
    else
    {
        childStateMach(charCh);
    }
}