int UART::open(const std::string &portName, int baudRate)
{
    UART_inner_data     *pd;

    COMMTIMEOUTS        oComTimeout;
    BOOL                fSuccess;

    int                 ret_code = 0;

    // handle structure
    pd = (UART_inner_data *) data;

    if( portName.size() ) port_name = portName;
    if( baudRate )        baud_rate = baudRate;

    // open port
    pd->m_hCom = CreateFile(
                            port_name.c_str(),                  // COM port Name
                            GENERIC_READ | GENERIC_WRITE,       // read/write flags
                            0,                                  // comm devices must be opened w/exclusive-access
                            NULL,                               // no security attributes
                            OPEN_EXISTING,                      // COM devices must use OPEN_EXISTING
                            0,                                  // no overlapped I/O
                            NULL                                // hTemplate must be NULL for COM devices
                        );

    if (pd->m_hCom == INVALID_HANDLE_VALUE) {
        // Handle the error.
        dbg_pe("UART::open CreateFile failed with wrror %d.", GetLastError());
        return 1;
    }

    // We will build on the current configuration, and skip setting the size
    //      of the input and output buffers with SetupComm.
    fSuccess = GetCommState(pd->m_hCom, &(pd->m_oDCB));
    if ( !fSuccess ) {
        dbg_pe("UART::open GetComState failed with error %d.", GetLastError());
        ret_code = 2;
        goto UART_OPEN_ERR;
    }

    // Fill in the DCB
    switch(baud_rate) {
        case 110:
            pd->m_oDCB.BaudRate = CBR_110;
            break;
        case 300:
            pd->m_oDCB.BaudRate = CBR_300;
            break;
        case 600:
            pd->m_oDCB.BaudRate = CBR_600;
            break;
        case 1200:
            pd->m_oDCB.BaudRate = CBR_1200;
            break;
        case 2400:
            pd->m_oDCB.BaudRate = CBR_2400;
            break;
        case 4800:
            pd->m_oDCB.BaudRate = CBR_4800;
            break;
        case 9600:
            pd->m_oDCB.BaudRate = CBR_9600;
            break;
        case 14400:
            pd->m_oDCB.BaudRate = CBR_14400;
            break;
        case 19200:
            pd->m_oDCB.BaudRate = CBR_19200;
            break;
        case 38400:
            pd->m_oDCB.BaudRate = CBR_38400;
            break;
        case 56000:
            pd->m_oDCB.BaudRate = CBR_56000;
            break;
        case 57600:
            pd->m_oDCB.BaudRate = CBR_57600;
            break;
        case 115200:
            pd->m_oDCB.BaudRate = CBR_115200;
            break;
        case 128000:
            pd->m_oDCB.BaudRate = CBR_128000;
            break;
        case 2560000:
            pd->m_oDCB.BaudRate = CBR_256000;
            break;
        default:
            dbg_pe("UART::open Unsupport baud rate %d.", baud_rate);;
            ret_code = 3;
            goto UART_OPEN_ERR;
    }

    if( DTR_sw )
        pd->m_oDCB.fDtrControl = DTR_CONTROL_DISABLE;
    if( RTS_sw )
        pd->m_oDCB.fRtsControl = RTS_CONTROL_DISABLE;

    pd->m_oDCB.ByteSize = byte_size;
    pd->m_oDCB.Parity   = parity_sw;
    switch( stop_bits ) {
        case 1:
            pd->m_oDCB.StopBits = ONESTOPBIT;
            break;
        case 15:
            pd->m_oDCB.StopBits = ONE5STOPBITS;
            break;
        case 2:
            pd->m_oDCB.StopBits = TWOSTOPBITS;
            break;
    }

    fSuccess = SetCommState(pd->m_hCom, &(pd->m_oDCB));
    if (!fSuccess) {
        // Handle the error.
        dbg_pe("UART::open SetComState failed with error %d.", GetLastError());
        ret_code = 4;
        goto UART_OPEN_ERR;
    }

    // timout options
    if( timeout_sw ) {
        fSuccess = GetCommTimeouts(     pd->m_hCom,         /* Handle to comm device */
                                        &oComTimeout        /* time-out values */
                                  );
        if( !fSuccess ) {
            dbg_pe("UART::open GetCommTimeouts failed with error %d.", GetLastError());
            ret_code = 5;
            goto UART_OPEN_ERR;
        }

        oComTimeout.ReadIntervalTimeout         =  DEFAULT_READINTERVALTIMEOUT;
        oComTimeout.ReadTotalTimeoutMultiplier  =  DEFAULT_READMULTIPLIER;
        oComTimeout.ReadTotalTimeoutConstant    =  DEFAULT_READTOTALTIMEOUT;
        oComTimeout.WriteTotalTimeoutMultiplier =  DEFAULT_WRITEMULTIPLIER;
        oComTimeout.WriteTotalTimeoutConstant   =  DEFAULT_WRITETOTALTIMEOUT;

        fSuccess = SetCommTimeouts(     pd->m_hCom,
                                        &oComTimeout
                                  );
        if( !fSuccess ) {
            dbg_pe("UART::open SetCommTimeouts failed with error %d.", GetLastError());
            ret_code = 6;
            goto UART_OPEN_ERR;
        }
    }

    // port state
    goto UART_OPEN_RET;

UART_OPEN_ERR:
    CloseHandle(pd->m_hCom);
    pd->m_hCom = NULL;

UART_OPEN_RET:
    return ret_code;
}