time_t RSSFeed::convertPubDate(const string& p_str_date) // move Util::
{
	time_t l_pubDate = {0};
	if (!p_str_date.empty())
	{
		SYSTEMTIME pTime = {0};
		
		if (!InternetTimeToSystemTimeA(p_str_date.c_str(), &pTime, 0) && !InternetTimeToSystemTimeA(("Mon, " + p_str_date).c_str(), &pTime, 0))  // http://code.google.com/p/flylinkdc/issues/detail?id=1061
		{
			LogManager::message("Error InternetTimeToSystemTime p_str_date = " + p_str_date + " error = " + Util::translateError());
		}
		else
		{
			// RSS - http://news.yandex.ru/computers.rss
			// pDate - "18 Jun 2013 06:35:01 +0400"
			// pTime = {wYear=400 wMonth=6 wDayOfWeek=18 ...} BUG
			tm l_tm = {0};
			
			l_tm.tm_year = pTime.wYear - 1900;
			l_tm.tm_mon = pTime.wMonth - 1;
			l_tm.tm_mday = pTime.wDay;
			
			l_tm.tm_hour = pTime.wHour;
			l_tm.tm_min = pTime.wMinute;
			l_tm.tm_sec = pTime.wSecond;
			
			l_pubDate = mktime(&l_tm);
		}
	}
	return l_pubDate;
}