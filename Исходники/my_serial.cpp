void Serial_Port::close_serial()
{
	printf("CLOSE SERIAL PORT\n");

	// Enable all events in serial port FALSE 
    SetCommMask(hComm, 0) ;

    EscapeCommFunction( hComm, CLRDTR ) ;
 
    PurgeComm( hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
    CloseHandle( hComm );
    hComm = NULL;
	
	status = false;

	printf("\n");
}