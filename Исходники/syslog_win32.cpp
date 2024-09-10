void CSyslog::_log(PHRASEA_LOG_LEVEL level, PHRASEA_LOG_CATEGORY category, TCHAR *fmt, ...)
//void CSyslog::_log(PHRASEA_LOG_LEVEL level, PHRASEA_LOG_CATEGORY category, const char *fmt, ...)
{
	extern int debug_flag;
	if(!(debug_flag & (1<<level)))
		return;

	va_list vl;
	char buff[5000];
	va_start(vl, fmt);
#ifdef UNICODE
	_vsnwprintf(buff, 5000, fmt, vl);
#else
	_vsnprintf(buff, 5000, fmt, vl);
#endif

//	printf("%s\n", buff);

	if(where == TOLOG)
	{
		if(!this->hEventLog)
			return;

		const TCHAR *aInsertions[] = { buff };

		switch(level)
		{
			case CSyslog::LOGL_PARSE:
			case CSyslog::LOGL_SQLOK:
			case CSyslog::LOGL_ALLOC:
				ReportEvent(
								this->hEventLog,                  // Handle to the eventlog
								EVENTLOG_INFORMATION_TYPE,      // Type of event
								this->category[category],               // Category (could also be 0)
								EVENT_ALL,               // Event id
								NULL,                       // User's sid (NULL for none)
								1,                          // Number of insertion strings
								0,                          // Number of additional bytes
								aInsertions,                       // Array of insertion strings
								NULL                        // Pointer to additional bytes
							);
				break;
			case CSyslog::LOGL_RECORD:
			case CSyslog::LOGL_THESAURUS:
			case CSyslog::LOGL_INFO:
				ReportEvent(
								this->hEventLog,                  // Handle to the eventlog
								EVENTLOG_WARNING_TYPE,      // Type of event
								this->category[category],               // Category (could also be 0)
								EVENT_ALL,               // Event id
								NULL,                       // User's sid (NULL for none)
								1,                          // Number of insertion strings
								0,                          // Number of additional bytes
								aInsertions,                       // Array of insertion strings
								NULL                        // Pointer to additional bytes
							);
				break;
			case CSyslog::LOGL_ERR:
				ReportEvent(
								this->hEventLog,                  // Handle to the eventlog
								EVENTLOG_ERROR_TYPE,      // Type of event
								this->category[category],               // Category (could also be 0)
								EVENT_ALL,               // Event id
								NULL,                       // User's sid (NULL for none)
								1,                          // Number of insertion strings
								0,                          // Number of additional bytes
								aInsertions,                       // Array of insertion strings
								NULL                        // Pointer to additional bytes
							);
				break;
			default:
				break;
		}
	}
	else
	{
		// TOTTY
		printf("[%s].[%s] :\n%s\n", this->libLevel[level], this->libCategory[category], buff);
//		printf("%s\n", buff);
	}
}