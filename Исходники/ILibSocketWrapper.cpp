int ILibSocketWrapper_recvfrom(int socketObject, char *buffer, int bufferLength, struct sockaddr *src)
{
	RSocket *s = (RSocket*)SocketArray[socketObject];
	TRequestStatus status;
	TInetAddr addr;
	int RetVal=0;
	RBuf8 *buf = new RBuf8();
	
	if(buf->Create(bufferLength)==KErrNone)
	{
		TProtocolDesc aProtocol;
		
		s->Info(aProtocol);
		if(aProtocol.iSockType==KSockStream)
		{
			s->RemoteName(addr);
			((struct in_addr*)src->sa_data)->s_addr = ntohl(addr.Address());
			src->sa_port = htons(addr.Port());
			RetVal = ILibSocketWrapper_recv(socketObject, buffer, bufferLength);
		}
		else
		{
			s->RecvFrom(*buf,addr,(unsigned int)0,status);
			User::WaitForRequest(status);
			if(status!=KErrNone)
			{
				RetVal = 0;
			}
			else
			{
				((struct in_addr*)src->sa_data)->s_addr = ntohl(addr.Address());
				src->sa_port = htons(addr.Port());
				Mem::Copy(buffer,buf->Ptr(),buf->Length());
				RetVal = buf->Length();
			}
		}
	}
	buf->Close();
	delete buf;
	return(RetVal);
}