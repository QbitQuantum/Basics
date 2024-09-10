int OCP_DataStreamInput_Thread::OpenComPortPhysical(const wxString &com_name, int baud_rate)
{

//    Set up the serial port
    wxString xcom_name = com_name;
    xcom_name.Prepend(_T("\\\\.\\"));                  // Required for access to Serial Ports greater than COM9

#ifdef SERIAL_OVERLAPPED
    DWORD open_flags = FILE_FLAG_OVERLAPPED;
#else
    DWORD open_flags = 0;
#endif
    
    HANDLE hSerialComm = CreateFile(xcom_name.fn_str(),      // Port Name
                             GENERIC_READ | GENERIC_WRITE,     // Desired Access
                             0,                               // Shared Mode
                             NULL,                            // Security
                             OPEN_EXISTING,             // Creation Disposition
                             open_flags,
                             NULL);

    if(hSerialComm == INVALID_HANDLE_VALUE)
    {
//        ThreadMessage(_T("Error:Invalid Handle"));
        return (0 - abs((int)::GetLastError()));
    }

    DWORD err;
    COMSTAT cs;
    ClearCommError(hSerialComm, &err, &cs);

    if(!SetupComm(hSerialComm, 1024, 1024))
    {
//        ThreadMessage(_T("Error:SetupComm"));
        if(hSerialComm != INVALID_HANDLE_VALUE)
            CloseHandle( hSerialComm );
        return (0 - abs((int)::GetLastError()));
    }

    DCB dcbConfig;

    if(GetCommState(hSerialComm, &dcbConfig))           // Configuring Serial Port Settings
    {
        dcbConfig.BaudRate = baud_rate;
        dcbConfig.ByteSize = 8;
        dcbConfig.Parity = NOPARITY;
        dcbConfig.StopBits = ONESTOPBIT;
        dcbConfig.fBinary = TRUE;
        dcbConfig.fRtsControl = RTS_CONTROL_ENABLE;
        dcbConfig.fDtrControl = DTR_CONTROL_ENABLE;
        dcbConfig.fOutxDsrFlow = false;
        dcbConfig.fOutxCtsFlow = false;
        dcbConfig.fDsrSensitivity = false;
        dcbConfig.fOutX = false;
        dcbConfig.fInX = false;
        dcbConfig.fInX = false;
        dcbConfig.fInX = false;
    }

    else
    {
//        ThreadMessage(_T("Error:GetCommState"));
        if(hSerialComm != INVALID_HANDLE_VALUE)
            CloseHandle( hSerialComm );
        return (0 - abs((int)::GetLastError()));
    }

    if(!SetCommState(hSerialComm, &dcbConfig))
    {
//        ThreadMessage(_T("Error:SetCommState"));
        if(hSerialComm != INVALID_HANDLE_VALUE)
            CloseHandle( hSerialComm );
        return (0 - abs((int)::GetLastError()));
    }

    COMMTIMEOUTS commTimeout;
    int TimeOutInSec = 2;
    commTimeout.ReadIntervalTimeout = 1000*TimeOutInSec;
    commTimeout.ReadTotalTimeoutConstant = 1000*TimeOutInSec;
    commTimeout.ReadTotalTimeoutMultiplier = 0;
    commTimeout.WriteTotalTimeoutConstant = 1000*TimeOutInSec;
    commTimeout.WriteTotalTimeoutMultiplier = 0;

    if(!SetCommTimeouts(hSerialComm, &commTimeout))
    {
//        ThreadMessage(_T("Error:SetCommTimeouts"));
        if(hSerialComm != INVALID_HANDLE_VALUE)
            CloseHandle( hSerialComm );
        return (0 - abs((int)::GetLastError()));
    }

    return (int)hSerialComm;
}