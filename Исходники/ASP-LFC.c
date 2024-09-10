void ParseCommand(char *string)
{
  char Command;
  char Command2 = 0;
  unsigned int Params[MAX_COMMAND_PARAMS];
  unsigned int NumParams=0;

/*  UsartWriteString("Command Received: ");
  UsartWriteString(string);
  UsartWriteString("\n\r");
*/
  // assume commands are single character followed by numerical parameters sep by spaces
  // e.g. "s 1 5", "b 7", "b 100 120 001 212 123"
  Command = string[0];
  if(IsAlpha(string[1])) // multi-char command (e.g. pa, oa, ia, etc)
	  Command2 = string[1];

  if(Command != 0)
  {
    NumParams=GetParams(string,Params); // read any optional parameters after command

/*
    UsartWriteString("CommandID: ");
    UsartWriteChar(Command);
    if(Command2 != 0)
      UsartWriteChar(Command2);
    UsartWriteString(" #Params: ");
    UsartWriteChar(48+NumParams);
    UsartWriteString("\n\r");
*/
  }
  else
  {
  UsartWriteString("No Command\n\r");
  };

  unsigned short lcdDataIn;
  static char buffer[10];

  switch(Command)
  {


    case 'a': // ADC do immediate conversion
	    PORTQ.OUTCLR = PIN0_bm | PIN2_bm; //ENCODE pins
		_delay_ms(1);
		PORTQ.OUTSET = PIN0_bm | PIN2_bm;
		_delay_ms(1);
		char value = PORTD.IN;
		
		
		
		IntToString(value,&buffer[0]);
		UsartWriteLine(buffer);
	  break;

	case 'b': // read imager flag
		PORTA.DIR &= ~0x01;
		char bb6 = PORTA.IN & 0x01;
		
		IntToString(bb6,&buffer[0]);
		UsartWriteLine(buffer);
	  break;

	case 'y': // Start Image
		frame = 0;
		start_interrupts();
	break;

	case 'z': // Stop Image
		stop_interrupts();
	break;

    case 'l':
		lcdDataIn = TSLCDInDat();
		IntToString(lcdDataIn,&buffer[0]);
		UsartWriteLine(buffer);
      break;

	case 'x':
		IntToString(4,&buffer[0]);
		UsartWriteLine(buffer);
      break;

    case 'T': // Usart TX test
	  DoUsartTx(Command2,Params[0],"0123456789");
	  break;

    case 'S': // Config SPI port
	  DoSpiConfig(Command2,Params[0]);
	  break;

    case 'X': // SPI TX test
	  DoSpiTx(Command2,"0123456789");
	  break;

    case 's': // Sleep CPU
	  DoSleep(Params[0]); // this will not return 
	  break;

    case 'O': // Set oscillator source
	  DoOscillator(Params[0]); // this will not return 
	  break;

    case 'h': // Usage
	  break;

  };	  


return;
};