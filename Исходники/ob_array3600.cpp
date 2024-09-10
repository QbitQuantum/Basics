BOOL ARRAY3600OBJ::SetupComPort(int port)
{	
	connected=FALSE;
	int sav_port;
    DCB dcb = {0};
	char PORTNAME[10];

	sav_port=comport;
    BreakDownComPort();
	comport= port ;

	// set tty structure for the specified port	
	if (!port) goto failed;
	sprintf(PORTNAME,"\\\\.\\COM%d",port);
    comdev = CreateFile( PORTNAME,GENERIC_READ | GENERIC_WRITE, 
                  0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

    if (comdev == INVALID_HANDLE_VALUE) goto failed;  
    if (!GetCommState(comdev, &dcb))      // get current DCB settings
	{ report_error("GetCommState");goto failed; }

    // update DCB rate, byte size, parity, and stop bits size
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = baudrate;
    dcb.ByteSize = 8;
	dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
	dcb.EvtChar = '\0';
    // update flow control settings
    dcb.fDtrControl     =  DTR_CONTROL_ENABLE;
    dcb.fRtsControl     =  RTS_CONTROL_ENABLE;
    dcb.fOutxCtsFlow    = FALSE;
    dcb.fOutxDsrFlow    = FALSE;
    dcb.fDsrSensitivity = FALSE;;
    dcb.fOutX           = FALSE;
    dcb.fInX            = FALSE;
    dcb.fTXContinueOnXoff = FALSE;
    dcb.XonChar         = 0;
    dcb.XoffChar        = 0;
    dcb.XonLim          = 0;
    dcb.XoffLim         = 0;
    dcb.fParity = FALSE; //TRUE;
    if (!SetCommState(comdev, &dcb))     // set new state
	{ report_error("SetCommState failed"); goto failed;}
    if (!SetupComm(comdev, 1024, 1024))  // set comm buffer sizes
	{  report_error("SetupComm failed");goto failed;}
    if (!EscapeCommFunction(comdev, SETDTR))        // raise DTR
	{  report_error("EscapeCommFunction failed");goto failed;}
	SetCommMask (comdev, EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING);

	return(TRUE);

failed:
		{  
			char sztemp[100];
			sprintf(sztemp, "The Port COM%d is not available. Please select another Com-Port.",port);
 	        write_logfile("COMPORT %d open failed.",port);		
			report_error(sztemp);		
			comport=sav_port;
			comdev=INVALID_HANDLE_VALUE;
			connected=FALSE;
			return FALSE;
		}

}