bool CG_NetSocket::SetNonBlocking()
{
	/* set to nonblocking mode */
	u_long arg;
	arg = 1;
	int ret;
	ret = IOCTLSOCKET(m_socket,FIONBIO,&arg);
	if (ret == SOCKET_ERROR)
	{
		CORE(LOG_NAME,"SetNonBlocking Failed,IOCTLSOCKET = %d",ret);
		return false;
	}
	else
	{
		return true;
	}
}