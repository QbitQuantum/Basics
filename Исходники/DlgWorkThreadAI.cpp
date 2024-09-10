void CDlgWorkThreadAI::OnBnClickedButton1()
{
	//得到所有工作进程的AI配置
	m_lcWorkThreadAI.DeleteAllItems();

	char szSendMessage[200] = {'\0'};
	char szCommand[100]     = {'\0'};
	sprintf_s(szCommand, 100, "%s GetWorkThreadAI -a", m_pTcpClientConnect->GetKey());
	int nSendLen = (int)strlen(szCommand); 

	memcpy_s(szSendMessage, 200, &nSendLen, sizeof(int));
	memcpy_s(&szSendMessage[4], 200, &szCommand, nSendLen);

	char szRecvBuff[100 * 1024] = {'\0'};
	int nRecvLen = 100 * 1024;
	bool blState = m_pTcpClientConnect->SendConsoleMessage(szSendMessage, nSendLen + sizeof(int), (char*)szRecvBuff, nRecvLen);
	if(blState == false)
	{
		MessageBox(_T(MESSAGE_SENDERROR) , _T(MESSAGE_TITLE_ERROR), MB_OK);
		return;
	}
	else
	{
		int nStrLen       = 0;
		int nPos          = 0;
		int nThreadCount  = 0;
		memcpy_s(&nThreadCount, sizeof(short), &szRecvBuff[nPos], sizeof(short));
		nPos += sizeof(short);

		for(int i = 0; i < nThreadCount; i++)
		{
			int nThreadID       = 0;
			int nAI             = 0;
			int nDisposeTime    = 0;
			int nWTCheckTime    = 0;
			int nWTTimeoutCount = 0;
			int nWTStopTime     = 0;

			memcpy_s(&nThreadID, sizeof(int), &szRecvBuff[nPos], sizeof(int));
			nPos += sizeof(int);
			memcpy_s(&nAI, sizeof(char), &szRecvBuff[nPos], sizeof(char));
			nPos += sizeof(char);
			memcpy_s(&nDisposeTime, sizeof(int), &szRecvBuff[nPos], sizeof(int));
			nPos += sizeof(int);
			memcpy_s(&nWTCheckTime, sizeof(int), &szRecvBuff[nPos], sizeof(int));
			nPos += sizeof(int);
			memcpy_s(&nWTTimeoutCount, sizeof(int), &szRecvBuff[nPos], sizeof(int));
			nPos += sizeof(int);
			memcpy_s(&nWTStopTime, sizeof(int), &szRecvBuff[nPos], sizeof(int));
			nPos += sizeof(int);

			//显示出来
			CString strData;
			strData.Format(_T("%d"), nThreadID);
			m_lcWorkThreadAI.InsertItem(i, strData);
			if(nAI == 0)
			{
				strData = _T("AI关闭");
				m_lcWorkThreadAI.SetItemText(i, 1, strData);
			}
			else
			{
				strData = _T("AI运行中");
				m_lcWorkThreadAI.SetItemText(i, 1, strData);
			}
			
			strData.Format(_T("%d"), nDisposeTime);
			m_lcWorkThreadAI.SetItemText(i, 2, strData);
			strData.Format(_T("%d"), nWTCheckTime);
			m_lcWorkThreadAI.SetItemText(i, 3, strData);
			strData.Format(_T("%d"), nWTTimeoutCount);
			m_lcWorkThreadAI.SetItemText(i, 4, strData);
			strData.Format(_T("%d"), nWTStopTime);
			m_lcWorkThreadAI.SetItemText(i, 5, strData);
		}
	}
}