void CLiveRoomRankManager::SetLiveRoomConfig(
	const char *pstrStartTime, const char *pstrEndTime, 
	int nLeaderBoardSize, const char *pstrFirstUpdateTime, int nUpdateInterval,int nAuditionBaseScore)
{
	m_nStartTime = SetTime(pstrStartTime);
	m_nEndTime = SetTime(pstrEndTime);
	m_nLeaderBoardSize = nLeaderBoardSize;

	std::string strTimeBuff("2014-07-01 ");
	if (pstrFirstUpdateTime)
		strTimeBuff.append(pstrFirstUpdateTime);
	time_t tFirstUpdateTime = SetTime(strTimeBuff.c_str());
	struct tm tmFirstUpdateTime;
	LocalTime(&tFirstUpdateTime, &tmFirstUpdateTime);

	m_nFirstUpdateTime = tmFirstUpdateTime.tm_hour * 3600 + tmFirstUpdateTime.tm_min * 60 + tmFirstUpdateTime.tm_sec;
	m_nTideUpdateInterval = nUpdateInterval * 1000;
	m_nAuditionBaseScore = nAuditionBaseScore;
}