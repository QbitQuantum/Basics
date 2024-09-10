void CMonitorPage::UpdateGameStatus(const i8desk::GameInfoMap& GameInfos)
{
	int nIdcCount = 0, nSvrCount = 0, nMatchCount = 0;
	int nAutoUptCount = 0, nNeedUptCount = 0;
	int nIdcAddInThisWeekCount = 0, nIdcUpdateCount = 0;
	int nIdcI8PlayCount = 0, nIdcI8PlayNotDownloadCount = 0;
	unsigned __int64 ullIdcSize = 0, ullSvrSize = 0;
	unsigned __int64 ullIdcI8PlaySize = 0, ullIdcI8PlayNotDownloadSize = 0;
	
	int nAddGameNoDownNum = 0; //近期新增资源(未下载)

	int nConVirRunGameNum = 0;	//配置为虚拟盘运行的资源数
	unsigned __int64 ullConVirRunGameSize = 0;

	int nConLocRunGameNum = 0;	//配置为本地更新运行的资源数
	unsigned __int64 ullConLocRunGameSize = 0;	

	int nConRunNotUptGameNum = 0;//配置为不更新，直接运行的资源数
	unsigned __int64 ullConRunNotUptGameSize = 0;

	CTime now = CTime::GetCurrentTime();
	int nowYear = now.GetYear();
	int nowMonth = now.GetMonth();
	int nowDay = now.GetDay();

	CTime start(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0);
	start -= CTimeSpan(30,0,0,0); //30天算近期
	DWORD StartTime = (DWORD)start.GetTime();

	//得到本周开始的时刻，用于计算本周中心更新的游戏数
	int nowDayOfWeek = now.GetDayOfWeek();
	CTime ThisWeekStart = now - CTimeSpan(nowDayOfWeek);

	CTime ThisWeekStartDay(ThisWeekStart.GetYear(), 
		ThisWeekStart.GetMonth(), ThisWeekStart.GetDay(), 0, 0, 0);
	DWORD ThisWeekStartTime = (DWORD)ThisWeekStartDay.GetTime();

	i8desk::GameInfoMapCItr it = GameInfos.begin();
	for (; it != GameInfos.end(); ++it) 
	{
		if (it->second->GID >= MIN_IDC_GID) 
		{
			nIdcCount++;
			ullIdcSize += it->second->Size;

			if (it->second->Status == 1)
				nMatchCount++;

			if (it->second->AddDate > StartTime && it->second->Status == 0)
			{
				nAddGameNoDownNum++;
			}

			if (it->second->IdcVer > ThisWeekStartTime)
			{
				nIdcAddInThisWeekCount++;

				CTime IdcUpdateTime = it->second->IdcVer;
				if (IdcUpdateTime.GetDay() == nowDay
					&& IdcUpdateTime.GetMonth() == nowMonth
					&& IdcUpdateTime.GetYear() == nowYear)
				{
					nIdcUpdateCount++;
				}
			}

			if (it->second->I8Play == 1)
			{
				nIdcI8PlayCount++;
				ullIdcI8PlaySize += it->second->Size;

				if (it->second->Status == 0) 
				{
					nIdcI8PlayNotDownloadCount++;
					ullIdcI8PlayNotDownloadSize += it->second->Size;
				}
			}
		}

		if (it->second->Status == 1)
		{
			nSvrCount++;
			ullSvrSize += it->second->Size;

			if (it->second->AutoUpt == 1)
				nAutoUptCount++;
			if (it->second->GID >= MIN_IDC_GID 
				&& it->second->IdcVer != it->second->SvrVer)
				nNeedUptCount++;

			bool bConLocRunGame = false;
			bool bConVirRunGame = false;
			bool bConRunNotUptGame = false;

			for (size_t i = 0; i < it->second->RunTypes.size(); i++)
			{
				switch (it->second->RunTypes[i].RunType)
				{
				case ERT_LOCAL: 
					bConLocRunGame = true; 
					break;
				case ERT_VDISK:
					bConVirRunGame = true; 
					break;
				case ERT_DIRECT: 
					bConRunNotUptGame = true; 
					break;
				default: 
					break;
				}
			}

			if (bConLocRunGame)
			{
				nConLocRunGameNum++;
				ullConLocRunGameSize += it->second->Size;
			}

			if (bConVirRunGame)
			{
				nConVirRunGameNum++;
				ullConVirRunGameSize += it->second->Size;
			}

			if (bConRunNotUptGame)
			{
				nConRunNotUptGameNum++;
				ullConRunNotUptGameSize += it->second->Size;
			}
		}
	}

	sprintf(m_GameInfo.CGameNum, "%d个/%.2fG", nIdcCount, ullIdcSize/1024.0/1024.0);			//中心游戏数
	sprintf(m_GameInfo.MatchGameNum, "%d个", nMatchCount);		//本地己匹配到中心资源的游戏
	sprintf(m_GameInfo.LGameNum, "%d个/%.2fG", nSvrCount, ullSvrSize/1024.0/1024.0);			//本地游戏数
	
	sprintf(m_GameInfo.CAddGameNum, "%d个", nAddGameNoDownNum);	//近期新增资源(未下载)

	sprintf(m_GameInfo.ConLocRunGameNum, "%d个/%.2fG", nConLocRunGameNum, ullConLocRunGameSize/1024.0/1024.0);	//增值游戏本地未下载数
	sprintf(m_GameInfo.ConVirRunGameNum, "%d个/%.2fG", nConVirRunGameNum, ullConVirRunGameSize/1024.0/1024.0);	//增值游戏本地未下载数
	sprintf(m_GameInfo.ConRunNotUptGameNum, "%d个/%.2fG", nConRunNotUptGameNum, ullConRunNotUptGameSize/1024.0/1024.0);	//增值游戏本地未下载数

	sprintf(m_GameInfo.HaveUptGameNum, "%d个", nNeedUptCount);		//有更新的游戏数
}