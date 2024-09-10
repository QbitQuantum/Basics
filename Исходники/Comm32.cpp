// Habilitacion y programacion del puerto serie
int CComm32::OpenComm()
{
	if (m_OnOpen) return ERROR_ALREADY_INITIALIZED;
	
	m_HPort=CreateFile(m_Name,GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (m_HPort==INVALID_HANDLE_VALUE)
		return GetLastError();
	
	m_OnOpen=true;

	if (GetFileType(m_HPort)!=FILE_TYPE_CHAR)
	{
		CloseHandle(m_HPort);
		return ERROR_OPEN_FAILED;
	}

	m_Read_Overlapped.hEvent=CreateEvent(NULL,true,true,NULL);
	if (m_Read_Overlapped.hEvent==0)
	{
		CloseAll();
		return GetLastError();
	}

	m_Write_Overlapped.hEvent=CreateEvent(NULL,true,true,NULL);
	if (m_Write_Overlapped.hEvent==0)
	{
		CloseAll();
		return GetLastError();
	}
	GetCommProperties(m_HPort,&m_CommProp);
	SetCommMask(m_HPort,m_EvtMask);
	SetCommTimeouts(m_HPort,&m_CommTimeOuts);
	GetCommModemStatus(m_HPort,&m_ModemStat);
	DWORD size=sizeof(COMMCONFIG);
	GetCommConfig(m_HPort,&m_CommConfig,&size);
	return 0;

}