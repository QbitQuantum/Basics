std::string FormatHTTPDate(__int64* ltime)
{
	struct tm t;
	if(ltime != NULL)
	{
		_gmtime64_s(&t, ltime);
	}
	else
	{
		//  传入空指针,则取当前时间.
		__int64 ltime_cur;
		_time64( &ltime_cur );
		_gmtime64_s(&t, &ltime_cur);
	}

	char szTime[100] = {0};

	// 格式化邮件时间 - Sun, 24 Aug 2008 22:43:45 GMT
	sprintf(szTime, "%s, %d %s %d %d:%d:%d GMT", 
		week[t.tm_wday], t.tm_mday, month[t.tm_mon], 
		t.tm_year + 1900, t.tm_hour, t.tm_min, t.tm_sec);

	return szTime;
}