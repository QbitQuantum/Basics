int CSeries::SerOpen(int PortNo, char * param)
{
	DCB			dcb;
	BOOL		fRetVal ;
	BYTE		i,bSet;
	DWORD		dwError;
	COMMTIMEOUTS  to;
	char baudr[128] = {0};

	TCHAR DevName[10];
	wsprintf(DevName,"\\\\.\\COM%01d",(int)PortNo);

	SerClose();
	if ((m_CommPort=CreateFile(DevName , GENERIC_READ | GENERIC_WRITE  , 0  , 
		NULL , OPEN_EXISTING , NULL , NULL )) == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	// set up DCB
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb) ;

	strcpy(baudr, (char *)param);

	if(!BuildCommDCBA(baudr, &dcb))
  	{
  		SerClose();
    		return -1;
  	}

  	if(!SetCommState(m_CommPort, &dcb))
  	{
    		SerClose();
    		return(-1);
  	}

	to.ReadIntervalTimeout         = MAXDWORD;
  	to.ReadTotalTimeoutMultiplier  = 0;
  	to.ReadTotalTimeoutConstant    = 0;
  	to.WriteTotalTimeoutMultiplier = 0;
 	to.WriteTotalTimeoutConstant   = 0;

	if(!SetCommTimeouts(m_CommPort, &to) )
  	{
    		SerClose();
    		return(-1);
  	}
	
	return 0;
}