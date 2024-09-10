void initSerialPort()
    {

    char mode[40],portname[20];
    COMMTIMEOUTS timeout_sets;
    DCB port_sets;
    strcpy(portname,"\\\\.\\");
    strcat(portname,COM);
    port_handle = CreateFileA(portname,
                              GENERIC_READ|GENERIC_WRITE,
                              0,                          /* no share  */
                              NULL,                       /* no security */
                              OPEN_EXISTING,
                              0,                          /* no threads */
                              NULL);                      /* no templates */
    if(port_handle==INVALID_HANDLE_VALUE)
        {
        printf("unable to open port %s -> %s\n",COM, portname);
        exit(0);
        }
    strcpy (mode,"baud=57600 data=8 parity=n stop=1");
    memset(&port_sets, 0, sizeof(port_sets));  /* clear the new struct  */
    port_sets.DCBlength = sizeof(port_sets);

    if(!BuildCommDCBA(mode, &port_sets))
        {
        printf("dcb settings failed\n");
        CloseHandle(port_handle);
        exit(0);
        }

    if(!SetCommState(port_handle, &port_sets))
        {
        printf("cfg settings failed\n");
        CloseHandle(port_handle);
        exit(0);
        }

    timeout_sets.ReadIntervalTimeout         = 1;
    timeout_sets.ReadTotalTimeoutMultiplier  = 1000;
    timeout_sets.ReadTotalTimeoutConstant    = 1;
    timeout_sets.WriteTotalTimeoutMultiplier = 1000;
    timeout_sets.WriteTotalTimeoutConstant   = 1;

    if(!SetCommTimeouts(port_handle, &timeout_sets))
        {
        printf("timeout settings failed\n");
        CloseHandle(port_handle);
        exit(0);
        }


    }