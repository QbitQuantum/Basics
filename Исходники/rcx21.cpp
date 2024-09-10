int RCX_open(int type, char *portname){
  //Opens the connections to the RCX via tower on serial or usb port.
  //type 1: serial port, type 2: USB port
  //portname for serial port is "COM1" for example
  //portname for USB port is "\\\\.\\LEGOTOWER1" for example
  //returns 0 if failed, 1 if successful

  if (type==1){//open serial port
    RCX_port = CreateFileA("COM6", GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_FLAG_WRITE_THROUGH, 0);

    if (RCX_port == INVALID_HANDLE_VALUE) return(0);

    //set data protocol format
    GetCommState(RCX_port,&dcb);
    FillMemory(&dcb, sizeof(dcb), 0);
    dcb.DCBlength = sizeof(dcb);
    dcb.BaudRate=CBR_2400;
    dcb.fBinary=1;
    dcb.fParity=1;
    dcb.fDtrControl=DTR_CONTROL_ENABLE;
    dcb.fRtsControl=RTS_CONTROL_ENABLE;
    dcb.ByteSize=8;
    dcb.Parity=ODDPARITY;
    dcb.StopBits=ONESTOPBIT;
    if (!SetCommState(RCX_port, &dcb)){
      RCX_close();
      return(0);
    }


    GetCommTimeouts(RCX_port,&tout);
    tout.ReadIntervalTimeout=250;
    tout.ReadTotalTimeoutConstant=10;
    tout.ReadTotalTimeoutMultiplier=10;
    tout.WriteTotalTimeoutConstant=10;
    tout.WriteTotalTimeoutMultiplier=10;
    SetCommTimeouts(RCX_port,&tout);

    SetupComm(RCX_port,65536,65536);
  } else { //type 2: open USB port
    RCX_port = CreateFileA(portname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, 0);
    if (RCX_port == INVALID_HANDLE_VALUE) return(0);

    GetCommTimeouts(RCX_port,&tout);
    tout.ReadIntervalTimeout=250;
    tout.ReadTotalTimeoutConstant=10;
    tout.ReadTotalTimeoutMultiplier=10;
    tout.WriteTotalTimeoutConstant=10;
    tout.WriteTotalTimeoutMultiplier=10;
    SetCommTimeouts(RCX_port,&tout);
  }


  return(1);
}