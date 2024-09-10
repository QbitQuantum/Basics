void CHostSet::CancelRunningHosts( int nMaxHosts )
{
	Lock();

	//sort the running hosts in trRunningHosts.
	CAvlHostSpeedTree	trRunningHosts;	//running hosts ordered by their speed
	list<CHostObject*>::iterator iter = m_lsRunningHosts.begin();
	while( iter!=m_lsRunningHosts.end() ){
		CHostObject* pHostObj = *iter++;
		trRunningHosts.Insert( pHostObj );
	}

	POSITION posRun = trRunningHosts.GetTailPosition();
	POSITION posAlv = m_trAliveHosts.GetHeadPosition();
	//list<CHostObject*>::iterator iter = m_lsRunningHosts.begin();
//	int nCanceled = 0;
//	while( iter!=m_lsRunningHosts.end() && nCanceled<nMaxHosts ){
//		CHostObject* pHostObj = *iter++;
//	while( posRun && posAlv && nCanceled<nMaxHosts ){
	while( posRun && posAlv ){
		CHostObject* pHostObj = trRunningHosts.GetPrev( posRun );		//this is the canceled host
		CHostObject* pHostObjAlv = m_trAliveHosts.GetNext( posAlv );	//this is the preempting host
		bool bCancelIt = false;
		if( pHostObjAlv->GetSpeedHint()==-1 ){
			bCancelIt = (double)rand() / RAND_MAX < 0.3;
		}else if( 2*pHostObjAlv->GetSpeedHint()<pHostObj->GetSpeedHint() ){
			bCancelIt = true;
		}
		//do the preemption.
		if( bCancelIt && (pHostObj->m_pSession!=NULL) ){
			IN_ADDR addr = pHostObj->GetAddr();
			char* pname = GetHostByAddr( addr );
			cdump<<lock<<"killing host connection "<<pname<<endl<<unlock;
			pHostObj->m_pSession->KillConnect();
			cdump<<lock<<pname<<" killed"<<endl<<unlock;

			//kill the running processes
			SOCKADDR_IN sockaddr;
			sockaddr.sin_family = AF_INET;
			sockaddr.sin_addr = pHostObj->GetAddr();
			sockaddr.sin_port = htons( NCP_SERVER_PORT );

			CClientSession* pSession = new CClientSession();
			int nRet;
			try{
				cdump<<lock<<"killing processes on "<<pname<<endl<<unlock;
				nRet = pSession->Connect( &sockaddr, "root", "" );
				if( nRet==0 ){
					pSession->KillProcs();
					pSession->Disconnect();
				}
				cdump<<lock<<"processes killed on "<<pname<<endl<<unlock;
			}catch( CSockException* e){
				e->Delete();
			}
			delete pSession;

//			nCanceled++;
		}
	}
	Unlock();
}