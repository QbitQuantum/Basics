////////////////////////////////////////////////////////////////////
// 投递接收数据请求
bool IocpPool::_PostRecv( IoContent* pIoContext )
{
	// 初始化变量
	DWORD dwFlags = 0;
	DWORD dwBytes = 0;
	WSABUF *p_wbuf   = &pIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pIoContext->overlapped;

	pIoContext->ResetBuffer();
	pIoContext->optype = RECV_POSTED;
	if (!pIoContext->socket) return false;
	// 初始化完成后，，投递WSARecv请求
	int nBytesRecv = WSARecv( pIoContext->socket->getHandle().getHandle(), p_wbuf, 1, &pIoContext->msgLen, &dwFlags, p_ol, NULL );

	// 如果返回值错误，并且错误的代码并非是Pending的话，那就说明这个重叠请求失败了
	if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError()))
	{
		//this->_ShowMessage("投递第一个WSARecv失败！");
		return false;
	}
	return true;
}