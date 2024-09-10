void CWeekTimePicker::UpdateTimeToRect()
{
	for (int i=0; i<WEEK_LEN; ++i)
	{
		if (i >= (int)m_vecWeekTimes.size())
		{
			break;
		}
		else
		{
			if (m_vecWeekTimes[i].nWeekIndex != i)
			{
				WeekDayTime weekDaytime;
				weekDaytime.nWeekIndex = i;
				m_vecWeekTimes.insert(m_vecWeekTimes.begin()+i, weekDaytime);
			}
		}
		auto &weekDayTime = m_vecWeekTimes[i];
		auto &rcBar = m_vecWeekDayBarRect[i];
		int iHour, iMinute, iSecond;
		CString cstrTime;
		m_vecWeekDayBarSelectedRect[i].vecDayRects.clear();

		for (size_t j=0; j<weekDayTime.vecDayTimes.size(); ++j)
		{
			CRect rcBarSelect = rcBar;
			cstrTime = weekDayTime.vecDayTimes[j].cstrBeginTime;
#ifdef _UNICODE
			swscanf_s(cstrTime.GetBuffer(), L"%d:%d:%d", &iHour, &iMinute, &iSecond);
#else
			sscanf_s(cstrTime.GetBuffer(), "%d:%d:%d", &iHour, &iMinute, &iSecond);
#endif
			rcBarSelect.left = rcBar.left + iHour*HOUR_WIDTH + iMinute*HOUR_WIDTH/60;
			cstrTime = weekDayTime.vecDayTimes[j].cstrEndTime;
#ifdef _UNICODE
			swscanf_s(cstrTime.GetBuffer(), L"%d:%d:%d", &iHour, &iMinute, &iSecond);
#else
			sscanf_s(cstrTime.GetBuffer(), "%d:%d:%d", &iHour, &iMinute, &iSecond);
#endif
			rcBarSelect.right = rcBar.left + iHour*HOUR_WIDTH + iMinute*HOUR_WIDTH/60;
			m_vecWeekDayBarSelectedRect[i].vecDayRects.push_back(rcBarSelect);
		}
	}
}