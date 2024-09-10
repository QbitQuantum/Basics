void CIocpServer::OnCompletionTrue( DWORD transfersize, ULONG_PTR key, CIocpIoData* iodata )
{
	CIocpSocket* client = m_Clients[key];
	if( client == 0 ) 
	{
		DebugBreak( );
		return;
	}
	if( transfersize > 0 )
	{
		iodata->bufferlen += transfersize;
		if( iodata->mode == IOMODE_RECV )
		{
			if( iodata->bufferlen == iodata->buffersize )
				client->RecvComplete( iodata );
			else
				client->RecvContinue( iodata );
		} else {
			if( iodata->bufferlen == iodata->buffersize )
				client->SendComplete( iodata );
			else
				client->SendContinue( iodata );
		}
	} else {
		client->CloseSocket( );
		g_IoDataPool.Release( iodata );

		client->m_Lock.Enter( );
		if( iodata->mode == IOMODE_RECV )
			client->m_RRefCount--;
		else
			client->m_SRefCount--;
		client->m_RefCount--;
		client->m_Lock.Leave( );
	}
};