// 初始化
BOOL CSocketInterfaceDataRev::OnInit(CString strIPForInterface, UINT uiPortForDataReceive)
{
	BOOL bReturn = false;

	// 和内部通讯的本机IP地址
	m_strIPForInterface = strIPForInterface;
	// 用于命令帧的端口号
	m_uiPortForDataReceive = uiPortForDataReceive;
	// 生成网络端口
	bReturn = Create(m_uiPortForDataReceive, SOCK_DGRAM, m_strIPForInterface);

	//设置广播模式
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}