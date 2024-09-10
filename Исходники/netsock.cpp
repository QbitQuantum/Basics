bool CSocket::GetSockName(string& rSocketAddress, UINT& rSocketPort)
{
	SOCKADDR_IN sockAddr;

	bool bResult = GetSockName(&sockAddr);
	if (bResult)
	{
		rSocketPort = ntohs(sockAddr.sin_port);
		rSocketAddress = inet_ntoa(sockAddr.sin_addr);
	}
	return bResult;
}