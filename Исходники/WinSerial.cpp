}	
void    WinSerial::setupLink()
{

        int     ret;
        DCB     dcb = {0};
        COMMTIMEOUTS cto = {10,10,10,10,10};

        dcb.DCBlength = sizeof(DCB);

        cto.ReadIntervalTimeout = 100;

sprintf(logchunk, "opening com port <%s>\n", mDevName);
log(logchunk);
        mPortFh = CreateFile(mDevName, GENERIC_READ | GENERIC_WRITE,
                                         0,
                                         0,
                                         OPEN_EXISTING, 
                                         0,
                                         0
                                         );

   	if (mPortFh == INVALID_HANDLE_VALUE) 
   	{
       		// Handle the error.
       		printf ("CreateFile failed with error %ld.\n", GetLastError());
       		exit(1);
   	}

sprintf(logchunk, " port %d\n", mPortFh);
log(logchunk);
        assert(mPortFh);
        ret = GetCommState(mPortFh, &dcb);

        if (!ret)
        {
                fprintf(stderr, "GetCommState failed %d\n",
                                 GetLastError());
                exit(2);
        } 
 //       dcb.BaudRate = CBR_57600;
        dcb.BaudRate = CBR_256000;
    	dcb.ByteSize    = 8;
    	dcb.StopBits    = ONESTOPBIT;
    	dcb.Parity      = NOPARITY;
    	dcb.fDtrControl = DTR_CONTROL_DISABLE;
    	dcb.fOutX       = FALSE;
    	dcb.fInX        = FALSE;
    	dcb.fNull       = FALSE;
    	dcb.fRtsControl = RTS_CONTROL_DISABLE;

// need to send binary data
	dcb.fBinary = 1;

//    *  fInX, fOutX,fOutXDsrFlow, fOutXCtsFlow are set to FALSE
//    * fDtrControl is set to DTR_CONTROL_ENABLE
//    * fRtsControl is set to RTS_CONTROL_ENABLE

   
  

        ret = SetCommState(mPortFh, &dcb);
        if (!ret)
        {
                fprintf(stderr, "SetCommState failed %d\n",
                                GetLastError());
                exit(3);
        }

        ret = SetCommTimeouts(mPortFh, &cto);
        if (!ret)
        {
                fprintf(stderr, "SetCommTimeouts failed %d\n",
                                GetLastError());
                exit(3);
        }

	log("setup\n");
	mSetup = 1;