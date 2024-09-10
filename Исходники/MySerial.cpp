int	MySerial::Read(void *buffer,int len)
{
	BOOL bReadStat;
	DWORD r_len = 0;
	
	ClearCommError(hCom,&dwErrorFlags,&ComStat);

	while( ComStat.cbInQue == 0 )
	{
		ClearCommError(hCom,&dwErrorFlags,&ComStat);
	}

	bReadStat = ReadFile(hCom,buffer,len,&r_len,NULL);

	PurgeComm(hCom, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);

	if(!bReadStat)
		return -1;

	return r_len;
}