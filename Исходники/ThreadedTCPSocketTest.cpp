	virtual void OnPacketReceived( CTCPPacket *pPacket )
	{
		if ( g_ClientPacket.Count() < pPacket->GetLen() )
			g_ClientPacket.SetSize( pPacket->GetLen() );
		
		memcpy( g_ClientPacket.Base(), pPacket->GetData(), pPacket->GetLen() );
		g_ClientPacketEvent.SetEvent();
		pPacket->Release();
	}