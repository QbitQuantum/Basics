void TempUserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>>[TempUserSession::OnRecv]<<<<\n");
	printf("Step2: <1> CA_Login_REQ\n");
	
	assert( m_bFirst == TRUE );
	if ( !m_bFirst ) {
		printf("Debug m_bFirst != TRUE. So return.\n");
		return;
	}
	
	MSG_CA_LOGIN_REQ * pRecvMsg = (MSG_CA_LOGIN_REQ *) pMsg;
	printf("RootID = %d, UserKey = %s\n", pRecvMsg->m_uiRootID, pRecvMsg->m_byUserKey);
	
	RootID * pRoot = RootidManager::Instance()->FindRootID( pRecvMsg->m_uiRootID );
	if ( pRoot == NULL ) {
		printf("\n[RootidManager::Instance()->FindRootID] Fail.\n");
				
		// 发送出错信息 ( 还未测试 )
		MSG_CA_LOGIN_NAK msgError;
		msgError.m_dwParameter = pRecvMsg->m_dwParameter; // User ID
		msgError.m_dwErrorCode = 1234; // ???

		Session * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			//m_pSession->UnbindNetworkObject();
			pSession->BindNetworkObject(this);
		}
		pSession->Send( (BYTE *)&msgError, sizeof(MSG_CA_LOGIN_NAK) );
		
		printf("\n>>>> Free TempUserSesion <<<<\n");
		AgentFactory::Instance()->FreeTempUserSession(this);	
		return;
	}
	
	// 验证 UserKey ( MD5 )
	BOOL bRet = pRoot->IsSameUserKey(pRecvMsg->m_byUserKey);
	if ( !bRet ) {
		printf("\n[RootidManager::Instance()->IsSameRootID] Fail.\n");
		// 发送出错信息
		//MSG_CA_LOGIN_NAK msgError;
		return;
	}
	

	// TempUser 转变为 User
	User * obj = AgentFactory::Instance()->AllocUser(); // 
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocUser() Fail.\n");
		return;
	}
	// 添加进 UserManager 进行管理
	DWORD dwID = g_UserManager.AddUser(obj); // 返回的是 ObjKey
	printf("g_UserManager AddUser, Return ObjKey = %d\n", dwID);
	obj->SetUserID(dwID);
	obj->SetRootID(pRecvMsg->m_uiRootID); // 保存 RootID
	
	Session * pSession = this->m_pSession;
	if ( pSession != NULL ) {
		m_pSession->UnbindNetworkObject();
		pSession->BindNetworkObject( obj );
	}
	printf("[TempUserSession] ==> [User] Success.\n");
	
	printf("Send MSG_AG_LOGIN_REQ to [GameSrv].\n");
	
	// 发送 AG_Login_REQ 消息包给 GameServer
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_dwParameter = dwID; // User ID
	msg2.m_uiRootID = pRecvMsg->m_uiRootID; // RootID
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
	
	//pSession->Send( (BYTE *)&ancMsg, sizeof( MSG_AG_LOGIN_REQ) );
	
	printf("\n>>>> Free TempUserSesion <<<<\n");
	AgentFactory::Instance()->FreeTempUserSession(this);
}