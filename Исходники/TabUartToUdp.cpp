// 打开串口
//************************************
// Method:    OnOpenCom
// FullName:  CTabUartToUdp::OnOpenCom
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnOpenCom(void)
{
// 	UpdateData(TRUE);
// 	CString str;
// 	m_comboSerialPortCom.GetWindowText(str);
// 	hCom =CreateFile( str, GENERIC_READ | GENERIC_WRITE/*允许读写*/,
// 		0/*此项必须为0*/,NULL/*no security attrs*/,
// 		OPEN_EXISTING/*设置产生方式*/,
// 		0/*使用同步通信*/,
// 		NULL );
// 
// 	if(hCom!=INVALID_HANDLE_VALUE)			// 检测打开串口操作是否成功
// 	{
// 		AfxMessageBox(_T("Open Serial Port Successful!"));
// 	}
// 	else
// 	{
// 		AfxMessageBox(_T("Serial Port COM Nb is Invalid!"));
// 		return;
// 	}
// 
// 
// 	SetupComm( hCom, 1024,1024);					// 设置输入、输出缓冲区的大小
// 
// 	PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR| PURGE_RXCLEAR );	// 清干净输入、输出缓冲区
// 
// 	LPCOMMTIMEOUTS lpCommTimeouts = new COMMTIMEOUTS;//(LPCOMMTIMEOUTS)malloc(sizeof(LPCOMMTIMEOUTS));
// 	lpCommTimeouts->ReadIntervalTimeout=MAXDWORD; // 读间隔超时
// 	lpCommTimeouts->ReadTotalTimeoutMultiplier=0; // 读时间系数
// 	lpCommTimeouts->ReadTotalTimeoutConstant=0; // 读时间常量 
// 	lpCommTimeouts->WriteTotalTimeoutMultiplier=50; // 写时间系数
// 	lpCommTimeouts->WriteTotalTimeoutConstant=2000; // 写时间常量
// 	//加入读取和写入延时以避免同步通信过程中的线程阻塞情况
// 
// 	SetCommTimeouts(hCom, lpCommTimeouts);
// 
// 	DCB	dcb ; // 定义数据控制块结构
// 
// 	GetCommState(hCom, &dcb ) ; //读串口原来的参数设置
// 
// 	dcb.BaudRate = OnGetSerialPortBaud(); 
// 	dcb.ByteSize = 8; 
// 	dcb.Parity = NOPARITY;
// 	dcb.StopBits = ONESTOPBIT ;
// 	dcb.fBinary = TRUE ;
// 	dcb.fParity = FALSE;
// 
// 	SetCommState(hCom, &dcb ) ; //串口参数配置
// 
// 	int iRecPort;
// 	GetDlgItem(IDC_EDIT_PORT_REC)->GetWindowText(str);			// 0x9002
// 	sscanf_s(str,"%x", &iRecPort);
// 	// 创建Socket
// 	m_socketUartToUdp.Create(iRecPort,SOCK_DGRAM);
// 	m_socketUartToUdp.SetSockOpt(SO_RCVBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);
// 	m_socketUartToUdp.SetSockOpt(SO_SNDBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);

	int iPort = 0;
	int iBaud = 0;
	CString str = _T("");
	if(m_ctrlMSComm1.get_PortOpen())
	{
		m_ctrlMSComm1.put_PortOpen(FALSE);
		m_socketUartToUdp.Close();
	}
	UpdateData(TRUE);
	iPort = OnGetSerialPortCom();
	iBaud = OnGetSerialPortBaud();
	m_ctrlMSComm1.put_CommPort(iPort);
	str.Format(_T("%d,n,8,1"), iBaud);
	m_ctrlMSComm1.put_Settings(str);

	if(!m_ctrlMSComm1.get_PortOpen())
	{
		m_ctrlMSComm1.put_PortOpen(TRUE);
		m_socketUartToUdp.m_pctrlMSComm1 = &m_ctrlMSComm1;
		GetDlgItem(IDC_EDIT_PORT_REC)->GetWindowText(str);			// 0x9002
		sscanf_s(str,"%x", &m_uiRecPort);
		m_uiSerialPortComCurSel = m_comboSerialPortCom.GetCurSel();
		m_uiSerialPortBaudCurSel = m_comboSerialPortBaud.GetCurSel();
	
		BOOL bReturn = FALSE; 
		// 创建Socket
		bReturn =  m_socketUartToUdp.Create(m_uiRecPort,SOCK_DGRAM);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("UDP转串口端口创建失败！"));
		}
		else
		{
			bReturn = m_socketUartToUdp.SetSockOpt(SO_SNDBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);
			if (bReturn == FALSE)
			{
				AfxMessageBox(_T("UDP转串口端口设置发送缓冲区设置失败！"));
			}
			bReturn = m_socketUartToUdp.SetSockOpt(SO_RCVBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);
			if (bReturn == FALSE)
			{
				AfxMessageBox(_T("UDP转串口端口设置接收缓冲区设置失败！"));
			}
			DWORD dwBytesReturned = 0;
			BOOL bNewBehavior = FALSE;
			DWORD status = 0;
			status = WSAIoctl(m_socketUartToUdp, SIO_UDP_CONNRESET ,
				&bNewBehavior, sizeof(bNewBehavior),
				NULL, 0, &dwBytesReturned,
				NULL, NULL);
		}
		ControlDisable();
		AfxMessageBox(_T("Open Serial Port Successful!"));
	}
	KillTimer(TabUartToUdpRecTimerNb);
	SetTimer(TabUartToUdpRecTimerNb, TabUartToUdpRecTimerSet, NULL);
}