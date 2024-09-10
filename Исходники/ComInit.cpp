/*
打开串口
*/
HANDLE CComInit::OpenComm(int ncom)
{
	memset( &m_read_os, 0, sizeof( OVERLAPPED ) ) ;    
	memset( &m_write_os, 0, sizeof( OVERLAPPED ) ) ;
	
	CString Com;
	Com.Format(_T("COM%d"),ncom);
	HANDLE hCom = CreateFile(Com,GENERIC_READ | GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	if(INVALID_HANDLE_VALUE==hCom)
	{
		CloseHandle(hCom);
		return hCom;
	}
	//创建事件
	m_read_os.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_write_os.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(NULL == m_read_os.hEvent || NULL == m_write_os.hEvent){
		CloseHandle(hCom);
		CloseHandle(m_read_os.hEvent);
		CloseHandle(m_write_os.hEvent);
		hCom = INVALID_HANDLE_VALUE;
		return hCom;
	}
	//设置com事件类型，参见msdn
	SetCommMask(hCom,EV_RXCHAR | EV_TXEMPTY);
	SetupComm( hCom, 1024,512 );//设置缓冲区大小;
	PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR
		| PURGE_RXCLEAR ); //清干净输入、输出缓冲区

	DCB dcb={0};
	dcb.DCBlength=sizeof(dcb);
	BOOL bres=GetCommState(hCom,&dcb);
	if(!bres)
	{
		CloseHandle(hCom);
		hCom=INVALID_HANDLE_VALUE;
		return hCom;
	}
	dcb.ByteSize=8;//后改
	dcb.fParity=0;
	dcb.BaudRate=CBR_9600;
	dcb.StopBits=ONESTOPBIT;

	bres=SetCommState(hCom,&dcb);
	if(!bres)
	{
		CloseHandle(hCom);
		hCom=INVALID_HANDLE_VALUE;
		return hCom;
	}
	COMMTIMEOUTS comm_time={0};
	comm_time.ReadIntervalTimeout=MAXDWORD;
	bres=SetCommTimeouts(hCom,&comm_time);
//	SetupComm(m_hComWndScreen, 4096, 1024);

	if(!bres)
	{
		CloseHandle(hCom);
		CloseHandle(m_read_os.hEvent);
		CloseHandle(m_write_os.hEvent);
		hCom = INVALID_HANDLE_VALUE;
		return hCom;
	}
	return hCom;
}