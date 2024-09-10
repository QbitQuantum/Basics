void CLimitDungeonManager::UpdateSchedule()
{
	mRoomMap.clear();
	mScheduleMap.clear();

	__time64_t todayTime = 0;
	_time64(&todayTime);
	const struct tm todayDate = *_localtime64(&todayTime);
	const Event emptyEvent = {Event::TypeNone, 0, 0, 0};
	mScheduleMap.insert(
		std::make_pair(todayTime, emptyEvent));

	typedef CGameResourceManager::LimitDungeonScriptMap ScriptMap;
	const ScriptMap& scriptMap = g_CGameResourceManager.GetLimitDungeonScriptMap();

	// 091106 LUJ, 일정을 구성한다
	for(ScriptMap::const_iterator scriptIter = scriptMap.begin();
		scriptMap.end() != scriptIter;
		++scriptIter)
	{
		const LimitDungeonScript& script = scriptIter->second;
		const BOOL isNoHomeMap(script.mHome.mMapType != mMapType);
		const BOOL isNoPlayMap(script.mMapType != mMapType);

		if(isNoPlayMap && isNoHomeMap)
		{
			continue;
		}

		// 091106 LUJ, 일정을 등록한다
		for(LimitDungeonScript::DateList::const_iterator dateIter = script.mDateList.begin();
			script.mDateList.end() != dateIter;
			++dateIter)
		{
			const LimitDungeonScript::Date& date = *dateIter;
			const WORD dayOnWeek = 7;
			// 091106 LUJ: 시작 요일과 끝 요일 사이에 며칠 간격인지 나타내는 상수 테이블
			//			행: 시작 요일(일~토), 열: 끝 요일(일~토)
			const int howManyDayBetweenDayOfWeek[][dayOnWeek] =
			{
				{0, 1, 2, 3, 4, 5, 6},
				{6, 0, 1, 2, 3, 4, 5},
				{5, 6, 0, 1, 2, 3, 4},
				{4, 5, 6, 0, 1, 2, 3},
				{3, 4, 5, 6, 0, 1, 2},
				{2, 3, 4, 5, 6, 0, 1},
				{1, 2, 3, 4, 5, 6, 0},
			};

			// 091106 LUJ, 컨텐츠가 시작될 시간을 얻는다
			struct tm futureDate(todayDate);
			const int howManyDay = howManyDayBetweenDayOfWeek[todayDate.tm_wday][date.mDayOfWeek];
			futureDate.tm_mday = futureDate.tm_mday + howManyDay;
			mktime(&futureDate);
			futureDate.tm_hour = date.mStartHour;
			futureDate.tm_min = date.mStartmMinute;
			futureDate.tm_sec = 0;

			__time64_t openTime = _mktime64(&futureDate);
			const BOOL isPassed(openTime < todayTime);

			if(isPassed)
			{
				const __time64_t remainTime = openTime + date.mPlayTime - todayTime;

				// 091106 LUJ, 시간이 지났지만, 진행 가능한 경우 즉시 연다.
				//			비정기적인 사건이므로 일정 관리에 넣지 않는다
				if(0 < remainTime)
				{
					const Event openEvent = {
						Event::TypeOpenIlregulary,
						script.mMapType,
						script.mChannel,
						remainTime};
					CloseRoom(
						openEvent);
					OpenRoom(
						openEvent);

					const Event closeEvent = {
						Event::TypeCloseIlregulary,
						script.mMapType,
						script.mChannel,
						0};
					mScheduleMap.insert(
						std::make_pair(todayTime + remainTime, closeEvent));
				}

				openTime = openTime + GetSecondForOneWeek();
			}

			const Event openEvent = {
				Event::TypeOpen,
				script.mMapType,
				script.mChannel,
				date.mPlayTime};
			const Event closeEvent = {
				Event::TypeClose,
				script.mMapType,
				script.mChannel,
				0};
			const __time64_t closeTime = openTime + date.mPlayTime;

			mScheduleMap.insert(
				std::make_pair(openTime, openEvent));
			mScheduleMap.insert(
				std::make_pair(closeTime, closeEvent));
		}
	}
}