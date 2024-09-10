/* device control settings */
unsigned int term_set_control ( unsigned int baud, unsigned char databits, unsigned char stopbits, unsigned char parity, unsigned char handshake )
{
    /*
        todo:
            - error checking
            - handshake
            - parity
            - stopbits
            - let the user configure timeouts ?
    */

    COMMCONFIG lpCC;
    COMMTIMEOUTS timeouts;

    if ( !hCom )
    {
        printf ( "%s: COM port was not open!\n", __FUNCTION__ );
        return RXE_FAIL;
    }

    GetCommTimeouts ( hCom, &timeouts );
    
	// TODO
	timeouts.ReadIntervalTimeout = 1;
    timeouts.ReadTotalTimeoutMultiplier = 0; 
    timeouts.ReadTotalTimeoutConstant = 10;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 10;

	if ( !SetCommTimeouts ( hCom, &timeouts ) )
    {
        printf ( "%s: setting timeouts didn't work!\n", __FUNCTION__ );
        return RXE_FAIL;
    }


	GetCommState ( hCom, &lpCC.dcb );

	lpCC.dcb.BaudRate = baud ? baud: CBR_115200;
    lpCC.dcb.ByteSize = databits;
    lpCC.dcb.StopBits = ONESTOPBIT;
    lpCC.dcb.Parity = NOPARITY;

    lpCC.dcb.fDtrControl = DTR_CONTROL_DISABLE;
    lpCC.dcb.fRtsControl = RTS_CONTROL_DISABLE;
    
	SetCommState ( hCom, &lpCC.dcb );

	return RXE_OK;
}