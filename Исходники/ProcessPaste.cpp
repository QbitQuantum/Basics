UINT CProcessPaste::MarkAsPastedThread(LPVOID pParam)
{
	DWORD startTick = GetTickCount();

	static CEvent UpdateTimeEvent(TRUE, TRUE, _T("Ditto_Update_Clip_Time"), NULL);
	UpdateTimeEvent.ResetEvent();

	Log(_T("Start of MarkAsPastedThread"));

	//If running from a U3 device then wait a little before updating the db
	//updating the db can take a second or two and it delays the act of pasting
	if(g_Opt.m_bU3)
	{
		Sleep(350);
	}

	BOOL bRet = FALSE;
	int clipId = 0;

	try
	{
		MarkAsPastedData* pData = (MarkAsPastedData*)pParam;
		if(pData)
		{
			clipId = pData->clipId;
			if(g_Opt.m_bUpdateTimeOnPaste)
			{
				try
				{
					if(pData->pastedFromGroup)
					{
						CppSQLite3Query q = theApp.m_db.execQuery(_T("SELECT clipGroupOrder FROM Main ORDER BY clipGroupOrder DESC LIMIT 1"));

						if(q.eof() == false)
						{
							double latestDate = q.getFloatField(_T("clipGroupOrder"));
							latestDate += 1;

							Log(StrF(_T("Setting clipId: %d, GroupOrder: %f"), pData->clipId, latestDate));

							theApp.m_db.execDMLEx(_T("UPDATE Main SET clipGroupOrder = %f where lID = %d;"), latestDate, pData->clipId);

							theApp.RefreshClipOrder(pData->clipId);
						}
					}
					else
					{
						CppSQLite3Query q = theApp.m_db.execQuery(_T("SELECT clipOrder FROM Main ORDER BY clipOrder DESC LIMIT 1"));

						if(q.eof() == false)
						{
							double latestDate = q.getFloatField(_T("clipOrder"));
							latestDate += 1;

							Log(StrF(_T("Setting clipId: %d, order: %f"), pData->clipId, latestDate));

							theApp.m_db.execDMLEx(_T("UPDATE Main SET clipOrder = %f where lID = %d;"), latestDate, pData->clipId);

							theApp.RefreshClipOrder(pData->clipId);
						}
					}
				}
				CATCH_SQLITE_EXCEPTION
			}

			try
			{
				theApp.m_db.execDMLEx(_T("UPDATE Main SET lastPasteDate = %d where lID = %d;"), (int)CTime::GetCurrentTime().GetTime(), pData->clipId);
			}
			CATCH_SQLITE_EXCEPTION

			delete pData;
			bRet = TRUE;
		}
	}
	CATCH_SQLITE_EXCEPTION

	Log(_T("End of MarkAsPastedThread"));

	DWORD endTick = GetTickCount();
	if((endTick-startTick) > 350)
		Log(StrF(_T("Paste Timing MarkAsPastedThread: %d, ClipId: %d"), endTick-startTick, clipId));

	UpdateTimeEvent.SetEvent();
	return bRet;
}