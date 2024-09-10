BOOL TcpComm::Send( MySocket& sock, ULONG targetIP, const LPBYTE pData, DWORD dwSize )
{
	IN_ADDR addr;
	addr.S_un.S_addr = targetIP;


	ByteBuffer sendByteBuffer;
	sendByteBuffer.Alloc(dwSize);
	memcpy((LPBYTE)sendByteBuffer, pData, dwSize);

	BOOL bSentOK = FALSE;

	int iSent = sock.SendAll((LPBYTE)sendByteBuffer, sendByteBuffer.Size());
	if (iSent)
	{
		bSentOK = TRUE;
	}
	else
	{
		sock.Close();

		if (! Connect(targetIP, sock))
		{
			debugLog(_T("connect %x %s failed"), targetIP, a2t(inet_ntoa(addr)));
			return FALSE;
		}
	}

	return bSentOK;
}