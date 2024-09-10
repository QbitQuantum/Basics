void CDessertSystem::InitLuaData()
{
	__time64_t now = _time64(nullptr);
	__time64_t tCurTime = m_BaseDataManager.GetLogoutTime();
	__time64_t nextRfreshTime = tCurTime;

	tm curTime;
	_localtime64_s(&curTime, &now);
	curTime.tm_hour = 5;
	curTime.tm_min = 0;
	curTime.tm_sec = 0;
	nextRfreshTime = _mktime64(&curTime);

	///判断登出时间到登陆时间的这段时间中是否已经刷新了相关的领取数据
	if (RefreshJudgement::JudgeCrossed(tCurTime, nextRfreshTime))
	{
		ResetData();
	}
}