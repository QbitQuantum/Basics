void Cube_SocketTCP_Connect::run()
{
	int ssize;
	Cube_SocketTCP_Connect_I _in;
	while(TRUE)
	{
		if (ssize=recv(m_Client.s,(char *)_in.Buffer,CUBE_SOCKETTCP_I_BUFFERSIZE,0)==SOCKET_ERROR)
		{
		break;
		}
		if (ssize!=0)
		{
			Recv(_in);
		}
		else
		{
			break;
		}
	}
	Offline();
}