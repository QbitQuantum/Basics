BOOL Serial::Wait(DWORD timeout)
{
//	SetCommMask(m_hComm,EV_RXCHAR);
	DWORD dwEvent;
	if(!WaitCommEvent(m_hComm,&dwEvent,NULL))
	{
	}

	return TRUE;
}