	CStressClient::CStressClient(_U32 nIndex, Zion::CClient* pClient)
	{
		m_nIndex = nIndex;
		m_pClient = pClient;
		pClient->_OnLoginDone.connect(this, &CStressClient::OnLoginDone);
		pClient->_OnLoginFailed.connect(this, &CStressClient::OnLoginFailed);
		pClient->_OnDisconnected.connect(this, &CStressClient::OnDisconnected);
		pClient->_OnData.connect(this, &CStressClient::OnData);
		pClient->SetLogCallback(std::tr1::bind(&CStressClient::OnLogMessage, this, std::tr1::placeholders::_1));
		SetTitle("NA");

		m_hTimer = NULL;
		if(pClient->GetClientApp()->IsThread())
		{
			CreateTimerQueueTimer(&m_hTimer, CStressManager::Get().GetTimerQueue(), StressTimerProc, this, 1, TIMER_PERIOD, 0);
		}
	}