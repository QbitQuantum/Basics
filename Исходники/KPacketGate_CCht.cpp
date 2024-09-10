void KPacketGate_CCht::Process_CCht_AddFriend_ByName(KSocket_Client* pSock, const void* pData, int len)
{
	CCht_AddFriend_ByName* req = (CCht_AddFriend_ByName*)pData;

	const char* friendAcctName = req->friendAcctName;
	const char* note = req->note;

	if(!pSock->m_chatAcct) return;

	KChatAccount* chatAcct = g_pApp->m_acctCache.find(friendAcctName);
	if(!chatAcct)
	{
		ChtC_AddFriend_Rsp rsp;
		rsp.result = JgErrorCode::err_Peer_NotFound;
		pSock->Send(s_nChtC_AddFriend_Rsp, &rsp, sizeof(rsp));

		JgMessageRequest_AddFriend* request = new JgMessageRequest_AddFriend();
		request->m_requestID = g_pApp->m_requestManager.m_nextRequestID++;
		request->m_requestTime = time(NULL);
		request->m_initialAcctID = pSock->m_chatAcct->m_acctID;
		request->m_friendAcctID = 0;
		request->m_friendAcctName = friendAcctName;
		strcpy_k(request->m_note, sizeof(request->m_note), req->note);

		DB_LoadAccountByName* task = DB_LoadAccountByName::Alloc(); task->reset();
		task->m_acctName = friendAcctName;
		task->setNextRequest(request);
		g_pApp->m_databaseAgent.push(*task);
		return;
	}

	if(chatAcct == pSock->m_chatAcct)
	{
		ChtC_AddFriend_Rsp rsp;
		rsp.result = JgErrorCode::err_AddFriend_Self;
		pSock->Send(s_nChtC_AddFriend_Rsp, &rsp, sizeof(rsp));
		return;
	}

	if(!chatAcct->isSocketReady())
	{
		JgMessageRequest_AddFriend request;
		request.m_requestID = g_pApp->m_requestManager.m_nextRequestID++;
		request.m_requestTime = time(NULL);
		request.m_initialAcctID = pSock->m_chatAcct->m_acctID;
		request.m_friendAcctID = chatAcct->m_acctID;
		request.m_friendAcctName = friendAcctName;
		strcpy_k(request.m_note, sizeof(request.m_note), req->note);

		FS_SaveMessage_2* task = FS_SaveMessage_2::Alloc(); task->reset();
		task->m_messageID = g_pApp->nextMessageID();
		task->m_messageSource = chatAcct->toMessageSource();
		task->m_messageTarget = chatAcct->toMessageTarget();
		task->m_contentType = JgMessageContentType::SYS_COMMAND;
		task->m_messageData.write(&request, sizeof(request));
		task->m_messageTime = time(NULL);
		g_pApp->m_storageAgent.Push(task);
		return;
	}
	{
		ChtC_AddFriend_Invite rsp;
		rsp.acctID = pSock->m_chatAcct->m_acctID;
		strcpy_k(rsp.note, sizeof(rsp.note), req->note);
		chatAcct->send(s_nChtC_AddFriend_Invite, &rsp, sizeof(rsp));
	}
}