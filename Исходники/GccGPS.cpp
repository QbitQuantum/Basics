extern "C" __declspec(dllexport) int GccOpenGps(int com_port, int rate)
{
	wchar_t comport[10];
	if(com_port >= 100)
	{
		logRawNmea = true;
		com_port -= 100;
	}
	else { logRawNmea = false; }
	if(com_port == 13)
	{
		wcscpy(comport, L"\\nmea.txt");
		filemode = true;
	}
	else
	{
		swprintf(comport, L"COM%i:", com_port);
		filemode = false;
	}
	__hGpsPort = CreateFile(comport, GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
/*
// for some reason sprintf did not work to write all these in one line ...
if     (com_port == 1)  __hGpsPort = CreateFile(L"COM1:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 2)  __hGpsPort = CreateFile(L"COM2:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 3)  __hGpsPort = CreateFile(L"COM3:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 4)  __hGpsPort = CreateFile(L"COM4:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 5)  __hGpsPort = CreateFile(L"COM5:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 6)  __hGpsPort = CreateFile(L"COM6:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 7)  __hGpsPort = CreateFile(L"COM7:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 8)  __hGpsPort = CreateFile(L"COM8:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 9)  __hGpsPort = CreateFile(L"COM9:", GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 10) __hGpsPort = CreateFile(L"COM10:",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 11) __hGpsPort = CreateFile(L"COM11:",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 12) __hGpsPort = CreateFile(L"COM12:",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 13) __hGpsPort = CreateFile(L"COM13:",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
else if(com_port == 14) __hGpsPort = CreateFile(L"COM14:",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
*/
    if(__hGpsPort == INVALID_HANDLE_VALUE)
    {
        DWORD dwLastError = GetLastError();

        switch(dwLastError)
        {
          case ERROR_ACCESS_DENIED:
            return -1;
            break;
          case ERROR_FILE_NOT_FOUND:
            return -2;
            break;
          default:
            return -3;
            break;
        }
    }

	if(!filemode)
	{
		// COM port setting
		DCB dcb;

		if (GetCommState(__hGpsPort,&dcb))	//fails on some devices with internal GPS - in these cases it's not necessarry anyway
		{
			// Set baud rate and other params
			dcb.BaudRate = (DWORD)rate;
			dcb.Parity   = NOPARITY;
			dcb.StopBits = ONESTOPBIT;
			dcb.ByteSize = 8;

			// use defaults for other fields (found on web)
			dcb.fBinary         = TRUE;	
			dcb.fParity         = FALSE;
			dcb.fOutxCtsFlow    = FALSE;	      
			dcb.fOutxDsrFlow    = FALSE;	      
			dcb.fDtrControl     = DTR_CONTROL_ENABLE; 
			dcb.fDsrSensitivity = FALSE;	      
			dcb.fOutX           = FALSE;	      
			dcb.fInX            = FALSE;	      
			dcb.fNull           = FALSE;	      
			dcb.fRtsControl     = RTS_CONTROL_ENABLE; 
			dcb.fAbortOnError   = FALSE;	      

			if (SetCommState(__hGpsPort,&dcb) == 0)
				{ return -5; }
		}

		// set mask which events to monitor 
		SetCommMask(__hGpsPort, EV_RXCHAR);

		// set buffer sizes (defaults in Windows)
		SetupComm( __hGpsPort, 4096, 2048);

		// Clear all chars from COM
		PurgeComm(__hGpsPort,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

		// Setup the comm timeouts. This is important: MAXDWORD for ReadIntervalTimeout means return immediately.
		COMMTIMEOUTS CommTimeOuts;
		CommTimeOuts.ReadIntervalTimeout            = 10;
		CommTimeOuts.ReadTotalTimeoutMultiplier     = 0;
		CommTimeOuts.ReadTotalTimeoutConstant       = 300;
		CommTimeOuts.WriteTotalTimeoutMultiplier    = 0;
		CommTimeOuts.WriteTotalTimeoutConstant      = 10;
		if (SetCommTimeouts( __hGpsPort, &CommTimeOuts ) == 0)
			{ return -6; }

		DWORD dwErrors;
		COMSTAT ComStat;
		ClearCommError(__hGpsPort,&dwErrors, &ComStat);
	}
    // reset read buffer
    __save_str = "";
    __read_lock = false;

	if (logRawNmea)
	{
		FILE *file = fopen("\\tmp.txt", "w");
		fprintf(file, "");
		fclose(file);
	}

	//FILE *filex = fopen("\\debug.txt", "w");
	//fprintf(filex, "debugfile\n");
	HANDLE initfile = CreateFile(L"\\GccInitGps.txt", GENERIC_READ,FILE_SHARE_READ, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(initfile != INVALID_HANDLE_VALUE)			//file exists -> send init data to GPS device
	{
		char c; unsigned long r,w; BOOL a;
		while(1)
		{
			if(!ReadFile(initfile, &c, 1, &r, NULL) || r==0)
				break;
			for(int i=0; i<1000; i++)
			{
				a=WriteFile(__hGpsPort, &c, 1, &w, NULL);		//w==0 if buffer full?
				//fprintf(filex, "read=%i  char=%c  written=%i  ret=%i\n",r,c,w,a);
				if(w == 1) break;
			}
		}
		CloseHandle(initfile);
	}
	//fclose(filex);
    return 1;
}