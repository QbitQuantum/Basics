char closeserial(portstream_fd portstream)
{   if (portstream != NULL) {                         
   		// disable event notification
   		SetCommMask( portstream, 0 ) ;
   	    // drop DTR
   		EscapeCommFunction( portstream, CLRDTR ) ;	 
   		// purge any outstanding reads/writes and close device handle
        PurgeComm( portstream, PURGE_TXABORT | PURGE_RXABORT | 
			                   PURGE_TXCLEAR | PURGE_RXCLEAR );
		// close the device   
		err = CloseHandle( portstream ) ;
        portstream = (HANDLE) -1;                
		if (err < 0)
			return -1;
	 }
     return 0;
}