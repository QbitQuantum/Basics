bool CAcceptor::Register(CLoginSocket &loginSocket, int size)
{
	if (CDisconnected::Instance() != loginSocket.stateMachine.CurrentState())
	{
		MYERRORPRINTF("loginSocket's state is not CDisconnected !!!");
		return false;
	}

	DWORD byteTransferred;

	BOOL result = AcceptEx(
		listenSocket->sock,
		loginSocket.sock,
		loginSocket.acceptBuf, size,
		sizeof(SOCKADDR_IN)+16,
		sizeof(SOCKADDR_IN)+16,
		&byteTransferred,
		static_cast<OVERLAPPED*>(&loginSocket.acts[CLoginSocket::ACT_TYPE::ACCEPT])
		);

	int error = WSAGetLastError();

	if (!result)
	{
		if (WSA_IO_PENDING != error)
		{
			MYERRORPRINTF("AcceptEx");
			return false;
		}
	}
	return true;
}