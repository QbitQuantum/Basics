int wxSerialPort::SendBreak(int duration)
{
    if(duration <= 0) duration = 1;
    if(!SetCommBreak(fd)) return -1;
    // win32 Sleep parameter is ms
    Sleep(duration * 250);
    if(!ClearCommBreak(fd)) return -1;
    // no error
    return 0;
};