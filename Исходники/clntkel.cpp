void CClientManager::OnAckPoll( CMessageBase* pMsg ){
	CObjLocker<CClientManager> locker(this);
	TOKEN_INFO* pinfo = (TOKEN_INFO*)(pMsg+1);

	IN_ADDR addrHost = pMsg->GetSrcAddr().m_addrHost;
	//update the host set
	if( m_HostAddrs.find( addrHost )==m_HostAddrs.end() )m_HostAddrs.insert( addrHost );

	//mark all the existing idle tokens from the host as dead
	map<CSessionAddr, CServerToken*>::iterator pos = m_PeerTokens.lower_bound( CSessionAddr(addrHost,0) );
	while( pos!=m_PeerTokens.end() && ( pos->second->GetServAddr().m_addrHost==addrHost) ){
		if( pos->second->IsIdle() )pos->second->SetState(CTF_DEAD);
		++pos;
	}

	//reset the tokens to idle
	int nInfos = pMsg->GetResult();
	for( int i=0; i<nInfos; i++ ){
		pinfo[i].ntoh();
		CSessionAddr addrPeer( pMsg->GetSrcAddr().m_addrHost, pinfo[i].nServId );
		pos = m_PeerTokens.find( addrPeer );
		if( pos==m_PeerTokens.end() ){
			AddToken( addrPeer, pinfo[i].nCpuType, pinfo[i].nCpuMhz );
		}else{
			if( !pos->second->IsRunning() )pos->second->SetState( CTS_IDLE );
		}
	}
	cdump<<"get poll back from host:"<<GetHostByAddr(addrHost).c_str()<<" with "<<nInfos<<" tokens"<<endl;
}