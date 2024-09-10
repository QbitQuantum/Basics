void SimpleDate::now()
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(p);
#ifdef _WIN32
	tm timeinfo;
	localtime_s(&timeinfo, &t);
	year = 1900 + timeinfo.tm_year;
	month = 1 + timeinfo.tm_mon;
	day = timeinfo.tm_mday;
#else
	tm *timeinfo = localtime(&t);
	year = std::to_string(1900 + timeinfo->tm_year);
	month = std::to_string(1 + timeinfo->tm_mon);
	day = std::to_string(timeinfo->tm_mday);
#endif
}