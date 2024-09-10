bool CMallManager::JudgementRefresh(const STimeData& time)
{
	if (IsFristOpen())
		return true;

	if (nullptr == m_pVecRefreshClock)
		return false;

	tm tsLogin, tsLastRefresh;
	__time64_t tLogin = *((__time64_t*)time.m_LoginTime);
	_localtime64_s(&tsLogin, &tLogin);
	__time64_t tLastRefresh = *((__time64_t*)m_pMallData->m_LastRefreshTime);
	_localtime64_s(&tsLastRefresh, &tLastRefresh);

	DWORD lastRefreshClock = tsLastRefresh.tm_hour;
	DWORD curClock = tsLogin.tm_hour;
	DWORD dwLastClockIndex = 0;
	int maxIndex = m_pVecRefreshClock->size() - 1;
	//获取上次刷新钟点的索引//
	for (int i = 0; i <= maxIndex; ++i)
	{
		if ((*m_pVecRefreshClock)[i] == lastRefreshClock)
		{
			dwLastClockIndex = i;
			break;
		}
	}

	bool bTomorrowRefresh = false;
	//当前时间(hour)大于等于最大刷新时间,即为明日刷新//
	if (curClock >= (*m_pVecRefreshClock)[maxIndex])
	{
		m_dwNextClockIndex = 0;
		m_pMallData->m_dwNextRefreshTime = (*m_pVecRefreshClock)[0] + 24;	///<加上24表示到明日刷新//
		bTomorrowRefresh = true;
	}
	else
	{
		//判断下次刷新的时间点//
		for (int i = 0; i <= maxIndex; ++i)
		{
			if ((*m_pVecRefreshClock)[i] > curClock)
			{
				m_dwNextClockIndex = i;
				m_pMallData->m_dwNextRefreshTime = (*m_pVecRefreshClock)[i];
				break;
			}
		}
	}

	int dayInterval = Days_Distance(tLogin, tLastRefresh);
	//当前登入的时间与上次刷新时间大于一天 则表示当前需要刷新(商城每日至少刷新一次)购买刷新的次数归0
	if (dayInterval >= 1)
	{
		m_pMallData->m_dwRefreshedCount = 0;
		return true;
	}

	/// 判断是否重置刷新次数
	__time64_t tLogout = *((__time64_t*)time.m_LogoutTime);
	__time64_t nextRefreshTime = tLogout;
	__time64_t now = _time64(nullptr);
	tm curTime;
	_localtime64_s(&curTime, &now);
	curTime.tm_hour = 5;
	curTime.tm_min = 0;
	curTime.tm_sec = 0;
	nextRefreshTime = _mktime64(&curTime);

	if (RefreshJudgement::JudgeCrossed(tLogout, nextRefreshTime))
	{
		m_pMallData->m_dwRefreshedCount = 0;
	}

	//精度到天的两个时间点的判断 大于0表示两个时间点至少隔天了//
	int result = CompareTimeOfYear(tsLogin, tsLastRefresh);
	///<理论上的上次刷新索引
	m_dwCurClockIndex = m_dwNextClockIndex == 0 ? maxIndex : m_dwNextClockIndex - 1;
	if (result > 0)
	{
		//每日刷新时间点大于1个//
		if (maxIndex > 1)
		{
			//上次刷新的时间小于最晚刷新时间,则需要刷新//
			if (dwLastClockIndex < maxIndex)
				return true;
			//当前时间大于最早刷新时间,则需要刷新//
			if (curClock >= (*m_pVecRefreshClock)[0])
				return true;
		}
		else //每日只需要刷新一次//
		{
			//上次刷新的时间小于刷新点时间或者当前时间大于刷新点时间,则需要刷新//
			if (lastRefreshClock < (*m_pVecRefreshClock)[0] || curClock >= (*m_pVecRefreshClock)[0])
				return true;
		}
	}
	else if (result == 0) //上次刷新时间与当前登录时间在同一天//
	{
		//每日刷新时间点大于1个//
		if (maxIndex > 1)
		{
			//上次游戏刷新时间点小于理论上的上次刷新时间点则刷新//
			if (dwLastClockIndex < m_dwCurClockIndex)
				return true;
		}
		else
		{
			//当前时间超过或等于刷新时间点,则需要刷新//
			if (lastRefreshClock < (*m_pVecRefreshClock)[0] && curClock >= (*m_pVecRefreshClock)[0])
				return true;
		}
	}

	return false;
}