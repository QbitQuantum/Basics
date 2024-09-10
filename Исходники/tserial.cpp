/* -------------------------------------------------------------------- */
int  Tserial::connect          (char *port_arg, int rate_arg, serial_parity parity_arg)
{
    int erreur;
    DCB  dcb;
    COMMTIMEOUTS cto = { 0, 0, 0, 0, 0 };

    /* --------------------------------------------- */
    if (serial_handle!=INVALID_HANDLE_VALUE)
        CloseHandle(serial_handle);
    serial_handle = INVALID_HANDLE_VALUE;

    erreur = 0;

    if (port_arg!=0)
    {
        strncpy(port, port_arg, 10);
        rate      = rate_arg;
        parityMode= parity_arg;
        memset(&dcb,0,sizeof(dcb));

        /* -------------------------------------------------------------------- */
        // set DCB to configure the serial port
        dcb.DCBlength       = sizeof(dcb);                   
        
        /* ---------- Serial Port Config ------- */
        dcb.BaudRate        = rate;

        switch(parityMode)
        {
            case spNONE:
                            dcb.Parity      = NOPARITY;
                            dcb.fParity     = 0;
                            break;
            case spEVEN:
                            dcb.Parity      = EVENPARITY;
                            dcb.fParity     = 1;
                            break;
            case spODD:
                            dcb.Parity      = ODDPARITY;
                            dcb.fParity     = 1;
                            break;
        }


        dcb.StopBits        = ONESTOPBIT;
        dcb.ByteSize        = 8;
        
        dcb.fOutxCtsFlow    = 0;
        dcb.fOutxDsrFlow    = 0;
        dcb.fDtrControl     = DTR_CONTROL_DISABLE;
        dcb.fDsrSensitivity = 0;
        dcb.fRtsControl     = RTS_CONTROL_DISABLE;
        dcb.fOutX           = 0;
        dcb.fInX            = 0;
        
        /* ----------------- misc parameters ----- */
        dcb.fErrorChar      = 0;
        dcb.fBinary         = 1;
        dcb.fNull           = 0;
        dcb.fAbortOnError   = 0;
        dcb.wReserved       = 0;
        dcb.XonLim          = 2;
        dcb.XoffLim         = 4;
        dcb.XonChar         = 0x13;
        dcb.XoffChar        = 0x19;
        dcb.EvtChar         = 0;
        
        /* -------------------------------------------------------------------- */
        serial_handle    = CreateFile(port, GENERIC_READ | GENERIC_WRITE,
                               0, NULL, OPEN_EXISTING,NULL,NULL);
                   // opening serial port


        if (serial_handle    != INVALID_HANDLE_VALUE)
        {
            if(!SetCommMask(serial_handle, 0))
                erreur = 1;

            // set timeouts
            if(!SetCommTimeouts(serial_handle,&cto))
                erreur = 2;

            // set DCB
            if(!SetCommState(serial_handle,&dcb))
                erreur = 4;
        }
        else
            erreur = 8;
    }
    else
        erreur = 16;


    /* --------------------------------------------- */
    if (erreur!=0)
    {
        CloseHandle(serial_handle);
        serial_handle = INVALID_HANDLE_VALUE;
    }
    return(erreur);
}