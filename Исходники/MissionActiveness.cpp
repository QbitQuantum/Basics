bool CMissionActiveness::InitDataMgr(void * pData)
{
	if (pData != nullptr)
		m_dwMissionActiveness = static_cast<DWORD*>(pData);

	///初始判断是否可以重置任务数据
	__time64_t tCurTime = m_pBaseDataMgr.GetLogoutTime();
	__time64_t nextRefreshTime = tCurTime;

	__time64_t now = _time64(nullptr);
	tm curTime;
	_localtime64_s(&curTime, &now);
	curTime.tm_hour = 5;
	curTime.tm_min = 0;
	curTime.tm_sec = 0;
	nextRefreshTime = _mktime64(&curTime);

	if (RefreshJudgement::JudgeCrossed(tCurTime, nextRefreshTime))
	{
		m_bInitResetMissionActiveness = true;
	}

	return true;
}