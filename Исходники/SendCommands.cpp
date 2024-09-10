int16_t SendCommands::Init() {
    int16_t failcode=0;

    int err;
    DCB dcb= {0};
    dcb.DCBlength=sizeof(dcb);
    uint8_t portNum=6;
    char port_name[10] = "COMx"; // this is a 5 char string with [4]=null terminator)
    if ( portNum < 10 )
    {   // one digit
        port_name[3] = 48 + portNum; // ascii number
    }
    else
    {   // two digit port number
        memcpy(port_name,"\\\\.\\COMxx",10); // this is a 10 char string (\\.\COMxx with [9]=null terminator)
        port_name[7] = 48 + (portNum / 10); // ascii number
        port_name[8] = 48 + (portNum % 10); // ascii number
    }

    ComFileHandle  =     CreateFile( "COM6", //port_name,// pointer to name of the file
                                     GENERIC_READ|GENERIC_WRITE,// access (read-write) mode
                                     0,            // share mode
                                     0,         // pointer to security descriptor
                                     OPEN_EXISTING,      // how to create
                                     FILE_ATTRIBUTE_NORMAL,   // if FILE_FLAG_OVERLAPPED is used, WaitCommEvent does NOT block.
//        FILE_FLAG_OVERLAPPED,   // if FILE_FLAG_OVERLAPPED is used, WaitCommEvent does NOT block.
                                     0 );

    if( (void *)ComFileHandle == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    err = GetCommState((void *)ComFileHandle, &dcb);
    if (err < 0)
    {
        return 2;
    }

    /*    {
           COMMTIMEOUTS  CommTimeOuts;
           // Get any early notifications
           SetCommMask(ComFileHandle, EV_RXCHAR);
           // Setup device buffers
           SetupComm(ComFileHandle, 4096, 4096);
           // Purge any information in the buffer
           PurgeComm(ComFileHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
           // Set timeouts since we are not using overlapped I/O
           CommTimeOuts.ReadIntervalTimeout         = 0; // timeout between bytes received not used.
           CommTimeOuts.ReadTotalTimeoutMultiplier  = 0; // not a function of num chars to read.
           CommTimeOuts.ReadTotalTimeoutConstant    = 100; // fixed timeout in ms
           CommTimeOuts.WriteTotalTimeoutMultiplier = 10;  // ms max for EACH byte sent
           CommTimeOuts.WriteTotalTimeoutConstant   = 1000;// ms max for entire Write operation.
           SetCommTimeouts(ComFileHandle, &CommTimeOuts);
        }
    */
    dcb.BaudRate= CBR_9600;
    dcb.Parity= NOPARITY;
    dcb.StopBits= ONESTOPBIT;
    dcb.ByteSize= 8;

    /*    dcb.fBinary= TRUE;// binary mode, no EOF check
        dcb.fOutxCtsFlow= FALSE;   // CTS output flow control
        dcb.fOutxDsrFlow= FALSE;   // DSR output flow control
        dcb.fDtrControl= DTR_CONTROL_DISABLE; //DTR_CONTROL_ENABLE;      // DTR flow control type
        dcb.fDsrSensitivity = FALSE;        // DSR sensitivity
        dcb.fTXContinueOnXoff = TRUE;     // XOFF continues Tx
        dcb.fOutX= FALSE;// XON/XOFF out flow control
        dcb.fInX= FALSE;// XON/XOFF in flow control
        dcb.fNull= FALSE;// enable null stripping
        dcb.fRtsControl= RTS_CONTROL_DISABLE; //RTS_CONTROL_ENABLE;// RTS flow control
        dcb.fAbortOnError= FALSE;// abort reads/writes on error
    */
    err = SetCommState( ComFileHandle, &dcb);

    if (err < 0)
    {
        return 3;
    }
    return failcode;

    memset(&OverlapStruct,0,sizeof(OverlapStruct));
    OverlapStruct.hEvent = CreateEvent(0, 1, 0, 0);
}