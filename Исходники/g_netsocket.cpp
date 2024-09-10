bool CG_NetSocket::SetNonBlocking()
{
	/* set to nonblocking mode */
	u_long arg;
	arg = 1;
	if (IOCTLSOCKET(m_socket,FIONBIO,&arg)==SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}