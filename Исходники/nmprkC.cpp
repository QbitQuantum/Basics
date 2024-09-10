NMPRKC_API nmprk_status_t NMPRK_StartDebugLogging(
	const char *filename)
{
	char dateStr[MAX_DATE_STR_LEN];
	char timeStr[MAX_DATE_STR_LEN];

	if(si_fsDebugLog.is_open() == true)
		return NMPRK_FAILURE;

	try
	{
		si_debugModule = SI_DEBUG_MODULE_ALL;
		si_debugLevel = SI_DEBUG_LEVEL_ALL;
		si_fsDebugLog.open(filename, std::fstream::out | std::fstream::app);
		if(si_fsDebugLog.is_open() != true)
			return NMPRK_FAILURE;
	}
	catch (...)
	{
		return NMPRK_FAILURE;
	}

#if defined WIN32
	_strdate_s(dateStr, MAX_DATE_STR_LEN);
	_strtime_s(timeStr, MAX_DATE_STR_LEN);
#else
	time_t mytime = time(NULL);
	strftime(dateStr, 9, "%D", localtime(&mytime));
	strftime(timeStr, 9, "%T", localtime(&mytime));
#endif
		
	SI_DEBUG_INFO(SI_THIS_MODULE, "Debug Logging Started: %s %s", dateStr, timeStr);

	return NMPRK_SUCCESS;
}