/**
* 初始化
* @param CString strIPForInstrument 信宿IP地址
* @param UINT uiPortForTailFrame	信宿端口号
* @param UINT uiPortForTailFrameSend	用于尾包转发的端口号
* @return BOOL TRUE：成功；FALSE：失败
*/
BOOL CSocketTailFrame::OnInit(CString strIPForInstrument, UINT uiPortForTailFrame, UINT uiPortForTailFrameSend)
{
	BOOL bReturn = false;

	// 和现场仪器通讯的本机IP地址
	m_strIPForInstrument = strIPForInstrument;
	// 用于尾包接收的端口号
	m_uiPortForTailFrame = uiPortForTailFrame;
	// 用于尾包转发的端口号
	m_uiPortForTailFrameSend = uiPortForTailFrameSend;
	// 生成网络端口
	bReturn = Create(m_uiPortForTailFrame, SOCK_DGRAM, m_strIPForInstrument);
	//设置广播模式
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
	Bind(m_uiPortForTailFrame,m_strIPForInstrument);

	return bReturn;
}