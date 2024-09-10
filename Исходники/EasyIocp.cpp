bool 
EasyIocp::PostRecv(CompTransmitKey *transKey, bool reset/* = true*/)
{
	EasyIocpBuffer *iocpBuffer = transKey->GetBuffer();
	if(reset)
		iocpBuffer->Reset();

	WSABUF* pBuf = iocpBuffer->GetWSABuf();
	SOCKET transSock = transKey->GetSocket();
	OVERLAPPED *pOv = transKey->GetOverlapped();
	DWORD transBytes = 0, flags = 0;
	int ret;

	//投递recv
	transKey->SetOperType(operRecv);

	ret = WSARecv(transSock, pBuf, 1, &transBytes, &flags, pOv, NULL);
	if(ret == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING) {
		print("EasyIocp::PostRecv: WSARecv failed.");
		return false;
	}

	return true;
}