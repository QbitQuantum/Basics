static SERIALPORT *serial_open(const char *device){
    HANDLE fh;
    DCB dcb={sizeof(DCB)};
    COMMTIMEOUTS timeouts;
    SERIALPORT *port;

    fh = CreateFile(device,GENERIC_READ|GENERIC_WRITE,0,NULL,
      OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (!fh) return NULL;

    port = malloc(sizeof(SERIALPORT));
    ZeroMemory(port, sizeof(SERIALPORT));
    port->fh = fh;

    /* save current port settings */
    GetCommState(fh,&port->dcb_save);
    GetCommTimeouts(fh,&port->timeouts_save);

    dcb.DCBlength=sizeof(DCB);
    BuildCommDCB("96,n,8,1",&dcb);
    SetCommState(fh,&dcb);

    ZeroMemory(&timeouts,sizeof(timeouts));
    timeouts.ReadTotalTimeoutConstant=1;
    timeouts.WriteTotalTimeoutConstant=1;
    SetCommTimeouts(fh,&timeouts);

    serial_flush(port);

    return port;
}