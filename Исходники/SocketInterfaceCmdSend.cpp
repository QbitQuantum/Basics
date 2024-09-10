/**
* 初始化
* @param CString strIPForInterface 信源IP地址
* @param UINT uiPortForCommandSend 信源端口号
* @param UINT uiPortAimToLine 信宿端口号，测线
* @param UINT uiPortAimToOperation 信宿端口号，施工
* @return BOOL TRUE：成功；FALSE：失败
*/
BOOL CSocketInterfaceCmdSend::OnInit(CString strIPForInterface, UINT uiPortForCommandSend, UINT uiPortAimToLine, UINT uiPortAimToOperation)
{
	BOOL bReturn = false;

	// 和内部通讯的本机IP地址
	m_strIPForInterface = strIPForInterface;
	// 用于命令帧的端口号
	m_uiPortForCommandSend = uiPortForCommandSend;
	// 客户端目标IP端口号，测线
	m_uiPortAimToLine = uiPortAimToLine;
	// 客户端目标IP端口号，施工
	m_uiPortAimToOperation = uiPortAimToOperation;
	// 生成网络端口
	bReturn = Create(m_uiPortForCommandSend, SOCK_DGRAM, m_strIPForInterface);

	//设置广播模式
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}