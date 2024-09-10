// Open the port. Returns 0 on success, or a negative error number.
// Establishes default comms settings, but calls OnOpen virtual function to
// change the default settings (including the port number).
// DEFAULTS: COM1; 2400baud; 8 Data bits; 1 Stop Bit; No Parity; No Handshaking.
int JHCommBase::Open()
{
	char fn[10];
	DCB dcb;
	COMMTIMEOUTS cto;
	COMMPROP cp;
	COMMSETTINGS cs;

	InitSettings(&cs, &dcb, &cto);
	OnOpen(&cs, &dcb, &cto);
	dcb.DCBlength = sizeof(dcb);
	cto.ReadIntervalTimeout = MAXDWORD;
	cto.ReadTotalTimeoutConstant = 0;
	cto.ReadTotalTimeoutMultiplier = 0;
	sprintf_s(fn, 10, "\\\\.\\COM%u", cs.PortNumber);
	hPort = CreateFileA(fn, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	if (hPort == INVALID_HANDLE_VALUE)
	{
		switch (GetLastError())
		{
		case 5:
			return -107;
		default:
			return -100;
		}
	}
	if (!SetCommTimeouts(hPort, &cto)) {Close(); return -101;};
	if ((cs.rxQueueSize != 0) || (cs.txQueueSize != 0))
		if (!SetupComm(hPort, cs.rxQueueSize, cs.txQueueSize)) {Close(); return -102;};
	if ((dcb.XoffLim == 0) || (dcb.XonLim == 0))
	{
		if (!GetCommProperties(hPort, &cp))	cp.dwCurrentRxQueue = 0;
		if (cp.dwCurrentRxQueue > 0)
		{
			//If we can determine the queue size, default to 1/10th, 8/10ths, 1/10th.
			//Note that HighWater is measured from top of queue.
			dcb.XoffLim = dcb.XonLim = (short)((int)cp.dwCurrentRxQueue / 10);
		}
		else
		{
			//If we do not know the queue size, set very low defaults for safety.
			dcb.XoffLim = dcb.XonLim = 8;
		}
	}
	if (!SetCommState(hPort, &dcb)) {Close(); return -103;};
	hRxEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == hRxEvent) {Close(); return -104;};
	hTxEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == hTxEvent) {Close(); return -105;};
	rxmode = 0;
	hRxThread = CreateThread(NULL, 0, RxThread, (LPVOID)this, 0, NULL);
	if (NULL == hRxThread) {Close(); return -106;};
	sendcount = 0;
	//OutputDebugString("Port Opened");
	return 0;
}