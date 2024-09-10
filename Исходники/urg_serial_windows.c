static void set_timeout(urg_serial_t *serial, int timeout)
{
    COMMTIMEOUTS timeouts;
    GetCommTimeouts(serial->hCom, &timeouts);

    timeouts.ReadIntervalTimeout = (timeout == 0) ? MAXDWORD : 0;
    timeouts.ReadTotalTimeoutConstant = timeout;
    timeouts.ReadTotalTimeoutMultiplier = 0;

    SetCommTimeouts(serial->hCom, &timeouts);
}