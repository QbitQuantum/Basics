int NcrComPort::OpenPort()
{
	if (hPort != 0)
		ClosePort();

    hPort = CreateFileA(
        this->Port,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (!GetCommState(hPort, &dcb))
        return -1;

    FillDcb(dcb);

    if (!SetCommState(hPort, &dcb))
        return -1;
	return 0;
}