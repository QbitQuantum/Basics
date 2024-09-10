/*-----------------------------------------------------------------------------

FUNCTION: SetupCommPort( int Port )

PURPOSE: Setup Communication Port with our settings

-----------------------------------------------------------------------------*/
BOOL SetupCommPort(int port)
{
    DWORD dwReadStatId;
    DWORD dwWriteStatId;
	int sav_port,sav_pause;
    DCB dcb = {0};
	char PORTNAME[10];

	if (!port) return(false);

	sav_port=TTY.PORT;
	sav_pause=TTY.read_pause;
    TTY.read_pause=1;
    
	BreakDownCommPort();

	TTY.PORT = port ;

	// set tty structure for the specified port
	
	sprintf(PORTNAME,"\\\\.\\COM%d",port);
	PACKET.readstate=0;
	PACKET.number=0;
	PACKET.old_number=0;
	PACKET.info=0;

    // open communication port handle
//    TTY.COMDEV = CreateFile( PORTNAME,GENERIC_READ | GENERIC_WRITE, 
//                  0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,0);

    TTY.COMDEV = CreateFile( PORTNAME,GENERIC_READ | GENERIC_WRITE, 
                  0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

    if (TTY.COMDEV == INVALID_HANDLE_VALUE) goto failed;
    
    if (!GetCommState(TTY.COMDEV, &dcb))      // get current DCB settings
	{ report_error("GetCommState");goto failed; }

   
    // update DCB rate, byte size, parity, and stop bits size
   
	dcb.DCBlength = sizeof(dcb);
    dcb.BaudRate = TTY.BAUDRATE;
    dcb.ByteSize = 8;
    
	dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
	dcb.EvtChar = '\0';

   
    // update flow control settings
   
    dcb.fDtrControl     =  DTR_CONTROL_ENABLE;
    dcb.fRtsControl     =  RTS_CONTROL_ENABLE;

	if (TTY.FLOW_CONTROL)
	{
      dcb.fOutxCtsFlow    = TRUE;
      dcb.fOutxDsrFlow    = TRUE;
	}
	else
	{
      dcb.fOutxCtsFlow    = FALSE;
      dcb.fOutxDsrFlow    = FALSE;
	}

    dcb.fDsrSensitivity = FALSE;;
    dcb.fOutX           = FALSE;
    dcb.fInX            = FALSE;
    dcb.fTXContinueOnXoff = FALSE;
    dcb.XonChar         = 0;
    dcb.XoffChar        = 0;
    dcb.XonLim          = 0;
    dcb.XoffLim         = 0;
    dcb.fParity = FALSE; //TRUE;

    if (!SetCommState(TTY.COMDEV, &dcb))     // set new state
	{ report_error("SetCommState failed"); goto failed;}
	
	// set comm buffer sizes
    if (!SetupComm(TTY.COMDEV, 1024, 1024))
	{  report_error("SetupComm failed");goto failed;}

    if (!EscapeCommFunction(TTY.COMDEV, SETDTR))        // raise DTR
	{  report_error("EscapeCommFunction failed");goto failed;}

	  SetCommMask (TTY.COMDEV, EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING);

      
    // start the reader and writer threads

	fThreadDone = FALSE;

    TTY.READERTHREAD =  
		CreateThread( NULL, 1000, (LPTHREAD_START_ROUTINE) ReaderProc, 0, 0, &dwReadStatId);
    if (TTY.READERTHREAD == NULL)
	{ report_error("CreateThread failed"); goto failed;}

	TTY.WRITERTHREAD =
		CreateThread( NULL, 1000, (LPTHREAD_START_ROUTINE) WriterProc, 0, 0, &dwWriteStatId);
    if (TTY.WRITERTHREAD == NULL)
	{ report_error("CreateWriterThread failed"); goto failed;}

	write_logfile("COMPORT opened: %s", PORTNAME);
	TTY.amount_to_write=0;	
	TTY.read_pause=sav_pause;

    return TRUE;

failed:
		{  
			char sztemp[100];
 	        write_logfile("COMPORT open failed");
		
			sprintf(sztemp, "The Port COM%d is not available. Please select another Com-Port.",TTY.PORT);
			report_error(sztemp);
		
			TTY.read_pause=sav_pause;
			TTY.PORT=sav_port;
			TTY.COMDEV=INVALID_HANDLE_VALUE;
			TTY.CONNECTED=FALSE;
			TTY.amount_to_write=0;
			return FALSE;
		}
}