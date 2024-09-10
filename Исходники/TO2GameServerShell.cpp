void CTO2GameServerShell::Update(LTFLOAT timeElapsed)
{
	// Update the main server first
	CGameServerShell::Update(timeElapsed);

	m_VersionMgr.Update();

	if (!GetServerDir())
		return;

	//if we're hosting LANOnly game, don't publish the server
	if( m_ServerGameOptions.m_bLANOnly )
		return;

	// Are we still waiting?
	static std::string status;
	switch (GetServerDir()->GetCurStatus())
	{
		case IServerDirectory::eStatus_Processing : 
			status ="";
			break;
		case IServerDirectory::eStatus_Waiting : 
			if (status.empty())
				status = GetServerDir()->GetLastRequestResultString();
			break;
		case IServerDirectory::eStatus_Error : 
			{
				
				IServerDirectory::ERequest eErrorRequest = GetServerDir()->GetLastErrorRequest();
				status = GetServerDir()->GetLastRequestResultString();
				GetServerDir()->ProcessRequestList();
			}
			break;
	};



	// Publish the server if we've waited long enough since the last directory update
	uint32 nCurTime = (uint32)GetTickCount();
	if ((m_nLastPublishTime == 0) || 
		((nCurTime - m_nLastPublishTime) > k_nRepublishDelay))
	{
		status = "";
		m_nLastPublishTime = nCurTime;
		uint32 nMax = 0;
		g_pLTServer->GetMaxConnections(nMax);

		// If not run by a dedicated server, we need to add one connection
		// for the local host.
		if( !m_ServerGameOptions.m_bDedicated )
			nMax++;

		GetServerDir()->SetActivePeer(0);

		CAutoMessage cMsg;

		// Update the summary info
		cMsg.WriteString(GetHostName());
		GetServerDir()->SetActivePeerInfo(IServerDirectory::ePeerInfo_Name, *cMsg.Read());

		char fname[_MAX_FNAME] = "";
		_splitpath( GetCurLevel(), NULL, NULL, fname, NULL );

		// Update the summary info
		cMsg.WriteString(g_pVersionMgr->GetBuild());
		cMsg.WriteString( fname );
		cMsg.Writeuint8(GetNumPlayers());
		cMsg.Writeuint8(nMax);
		cMsg.Writebool(m_ServerGameOptions.m_bUsePassword);
		cMsg.Writeuint8((uint8)GetGameType());
		cMsg.WriteString( m_ServerGameOptions.m_sModName.c_str() );

		GetServerDir()->SetActivePeerInfo(IServerDirectory::ePeerInfo_Summary, *cMsg.Read());


		// Update the details
		ServerMissionSettings sms = g_pServerMissionMgr->GetServerSettings();
		cMsg.Writebool(sms.m_bUseSkills);
		cMsg.Writebool(sms.m_bFriendlyFire);
		cMsg.Writeuint8(sms.m_nMPDifficulty);
		cMsg.Writefloat(sms.m_fPlayerDiffFactor);

		CPlayerObj* pPlayer = GetFirstNetPlayer();
	    while (pPlayer)
		{
			//has player info
			cMsg.Writebool(true);
			cMsg.WriteString(pPlayer->GetNetUniqueName());
			cMsg.Writeuint16( Min( GetPlayerPing(pPlayer), ( uint32 )65535 ));
			pPlayer = GetNextNetPlayer();
		};

		//end of player info
		cMsg.Writebool(false);

	
		cMsg.Writeuint8(sms.m_nRunSpeed);
		cMsg.Writeuint8(sms.m_nScoreLimit);
		cMsg.Writeuint8(sms.m_nTimeLimit);

		GetServerDir()->SetActivePeerInfo(IServerDirectory::ePeerInfo_Details, *cMsg.Read());

		// Update the port
		char aHostAddr[16];
		uint16 nHostPort;
		g_pLTServer->GetTcpIpAddress(aHostAddr, sizeof(aHostAddr), nHostPort);
		cMsg.Writeuint16(nHostPort);
		GetServerDir()->SetActivePeerInfo(IServerDirectory::ePeerInfo_Port, *cMsg.Read());
		
		// Tell serverdir again about info, but in service specific manner.
		PeerInfo_Service_Titan peerInfo;
		peerInfo.m_sHostName = GetHostName( );
		peerInfo.m_sCurWorld = fname; 
		peerInfo.m_nCurNumPlayers = GetNumPlayers( );
		peerInfo.m_nMaxNumPlayers = nMax;
		peerInfo.m_bUsePassword = m_ServerGameOptions.m_bUsePassword;
		peerInfo.m_sGameType = GameTypeToString( GetGameType( ));
		peerInfo.m_nScoreLimit = sms.m_nScoreLimit;
		peerInfo.m_nTimeLimit = sms.m_nTimeLimit;

		PeerInfo_Service_Titan::Player player;
		CPlayerObj::PlayerObjList::const_iterator iter = CPlayerObj::GetPlayerObjList( ).begin( );
		while( iter != CPlayerObj::GetPlayerObjList( ).end( ))
		{
			CPlayerObj* pPlayerObj = *iter;

			player.m_sName = pPlayerObj->GetNetUniqueName( );
			player.m_nScore = pPlayerObj->GetPlayerScore()->GetScore( );

			float fPing;
			g_pLTServer->GetClientPing( pPlayerObj->GetClient( ), fPing );
			player.m_nPing = ( uint16 )( fPing + 0.5f );

			peerInfo.m_PlayerList.push_back( player );

			iter++;
		}


		cMsg.Writeuint32(( uint32 )&peerInfo );
		GetServerDir()->SetActivePeerInfo(IServerDirectory::ePeerInfo_Service, *cMsg.Read());

		// Tell the world about me...
		GetServerDir()->QueueRequest(IServerDirectory::eRequest_Publish_Server);
	}
}