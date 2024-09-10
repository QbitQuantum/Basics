CPrivateChatFrame* CChatWindows::OpenPrivate(GGUID* pGUID, SOCKADDR_IN* pHost, BOOL bMustPush, PROTOCOLID nProtocol, SOCKADDR_IN* pServer)
{
	CPrivateChatFrame* pFrame = NULL;

	ASSERT ( pHost != NULL );

	if ( ( nProtocol == PROTOCOL_BT ) || ( nProtocol == PROTOCOL_FTP ) )
		return NULL;

	if ( ! MyProfile.IsValid() )
	{
		CString strMessage;
		LoadString( strMessage, IDS_CHAT_NEED_PROFILE );
		if ( AfxMessageBox( strMessage, MB_YESNO|MB_ICONQUESTION ) == IDYES )
			AfxGetMainWnd()->PostMessage( WM_COMMAND, ID_TOOLS_PROFILE );
		return NULL;
	}

	if ( nProtocol == PROTOCOL_ED2K )
	{
		CEDClient* pClient;

		// First, check if it's a low ID user on another server. 
		if ( bMustPush && pServer ) 
		{
			// It's a firewalled user (Low ID). If they are using another server, we 
			// can't (shouldn't) contact them. (It places a heavy load on the ed2k servers)
			CSingleLock pLock1( &Network.m_pSection );
			if ( ! pLock1.Lock( 250 ) ) return NULL;
			if ( Neighbours.Get( &pServer->sin_addr ) == NULL ) return NULL;
			pLock1.Unlock();
		}

		// ED2K chat is handled by the EDClient section. (Transfers)
		// We need to find (or create) an EDClient to handle this chat session, since everything 
		// on ed2k shares a TCP link.

		// First, lock the section to prevent a problem with other threads
		CSingleLock pLock( &Transfers.m_pSection );
		if ( ! pLock.Lock( 250 ) ) return NULL;

		// We need to connect to them, so either find or create an EDClient
		if ( pServer )
			pClient = EDClients.Connect(pHost->sin_addr.S_un.S_addr, pHost->sin_port, &pServer->sin_addr, pServer->sin_port, pGUID );
		else
			pClient = EDClients.Connect(pHost->sin_addr.S_un.S_addr, pHost->sin_port, NULL, 0, pGUID );
		// If we weren't able to create a client (Low-id and no server), then exit.
		if ( ! pClient ) return NULL;
		// Have it connect (if it isn't)
		if ( ! pClient->m_bConnected ) pClient->Connect();
		// Tell it to start a chat session as soon as it's able
		pClient->OpenChat();
		pLock.Unlock();

		// Check for / make active any existing window
		pFrame = FindPrivate( &pHost->sin_addr );
		// Check for an empty frame
		if ( pFrame == NULL )
		{
			if ( bMustPush ) pFrame = FindED2KFrame( pHost->sin_addr.S_un.S_addr, pServer );
			else pFrame = FindED2KFrame( pHost );
		}
		if ( pFrame != NULL ) 
		{
			// Open window if we found one
			CWnd* pParent = pFrame->GetParent();
			if ( pParent->IsIconic() ) pParent->ShowWindow( SW_SHOWNORMAL );
			pParent->BringWindowToTop();
			pParent->SetForegroundWindow();
			// And exit
			return pFrame;
		}
		// Open an empty (blank) chat frame. This is totally unnecessary- The EDClient will open 
		// one as required, but it looks better to open one here.
		pFrame = new CPrivateChatFrame();
		// Set name (Also used to match incoming connection)
		if ( bMustPush && pServer ) // Firewalled user (Low ID)
		{
			pFrame->m_sNick.Format( _T("%lu@%s:%hu"),
			pHost->sin_addr.S_un.S_addr,
			(LPCTSTR)CString( inet_ntoa( pServer->sin_addr ) ),
			pServer->sin_port );
		}
		else	// Regular user (High ID)
		{
			pFrame->m_sNick.Format( _T("%s:%hu"), (LPCTSTR)CString( inet_ntoa( pHost->sin_addr ) ), pHost->sin_port );
		}

		// Open window
		CWnd* pParent = pFrame->GetParent();
		if ( pParent->IsIconic() ) pParent->ShowWindow( SW_SHOWNORMAL );
		pParent->BringWindowToTop();
		pParent->SetForegroundWindow();
		// Put a 'connecting' message in the window
		CString strMessage, strConnecting;
		LoadString( strConnecting, IDS_CHAT_CONNECTING_TO );
		strMessage.Format( strConnecting, pFrame->m_sNick );
		pFrame->OnStatusMessage( 0, strMessage );

		return pFrame;
	}

	if ( pGUID != NULL ) pFrame = FindPrivate( pGUID );
	if ( pFrame == NULL ) pFrame = FindPrivate( &pHost->sin_addr );
	
	if ( pFrame == NULL )
	{
		pFrame = new CPrivateChatFrame();
		pFrame->Initiate( pGUID, pHost, bMustPush );	
	}

	pFrame->PostMessage( WM_COMMAND, ID_CHAT_CONNECT );
	
	CWnd* pParent = pFrame->GetParent();
	if ( pParent->IsIconic() ) pParent->ShowWindow( SW_SHOWNORMAL );
	pParent->BringWindowToTop();
	pParent->SetForegroundWindow();

	return pFrame;
}