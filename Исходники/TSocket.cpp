int TSocket::Receive(void *buf,unsigned int buf_len)
{
	WSABUF wsabuf;
	wsabuf.buf=(char *)buf;
	wsabuf.len=buf_len;

	DWORD num_read;
	DWORD flags=0;	// this variable is both an input and an output
	
	int ret=WSARecv(m_hSocket,&wsabuf,1,&num_read,&flags,NULL,NULL);

	if(ret==SOCKET_ERROR)
	{
		return SOCKET_ERROR;
	}
	else
	{
		return (int)num_read;
	}

	return ret;
}