void CWin32Socket::SendTo(TWin32Message& aMessage)
	{
	__ASSERT_DEBUG((iSendMessage == NULL) && (iBytesSent == 0), Panic(EWinSockPrtCWin32SocketMultipleSendToRequests));
	iSendMessage = &aMessage;
	WSP_LOG(WspLog::Printf(_L("CWin32Socket::SendTo: this: 0x%x, bytes to send: %d"), this, iSendMessage->ReadBuffer().Length()));
	TPtrC8 bufPtr(iSendMessage->ReadBuffer());
	iSendBuffer.buf = reinterpret_cast<char*>(const_cast<TUint8*>(bufPtr.Ptr()));
	iSendBuffer.len = bufPtr.Length();
	iSendOverlapped.hEvent = (void*) this;
	TInetAddr address;
	address.Copy(iSendMessage->WriteBuffer());
	SOCKADDR_IN winSockAddress;
	ConvertAddress(address, winSockAddress);
	DWORD numberOfBytesSent;
	TInt ret = WSASendTo(iSocket, &iSendBuffer, 1, &numberOfBytesSent, 0, (LPSOCKADDR)&winSockAddress, sizeof(struct sockaddr_in), &iSendOverlapped, &SendToCompletion);
	if (ret == SOCKET_ERROR)
		{
		TInt err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
			{
			WSP_LOG(WspLog::Printf(_L("\tsocket error: %d"), err));
			Complete(iSendMessage, MapWinSockError(err));
			}
		}
	}