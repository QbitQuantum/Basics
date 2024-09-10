int serial_init(const char *port, unsigned long baud)
{
    char fullPort[20];

    sprintf(fullPort, "\\\\.\\%s", port);

    hSerial = CreateFile(
        fullPort,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
        return FALSE;

    /* Set the baud rate. Always succeeds with mingw. */
    if (!serial_baud(baud)) {
        serial_done();
        return 0;
    }


    GetCommTimeouts(hSerial, &original_timeouts);
    timeouts = original_timeouts;
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
    timeouts.WriteTotalTimeoutConstant = 1;
    timeouts.WriteTotalTimeoutMultiplier = 1;

    /* setup device buffers */
    SetupComm(hSerial, 10000, 10000);

    /* purge any information in the buffer */
    PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

    return TRUE;
}