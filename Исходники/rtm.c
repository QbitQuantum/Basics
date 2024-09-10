/**
 * handles all time commands.
 * @return false when errors, true otherwise
 */
bool krnlSYStimeCommand(SYStimeCommand command)
{
	bool result = true;

	struct tm *sTime;
	struct timeb currTime;

	if (command != IDLE) {
		PRINT1("SYStime Command: %u\n", command);
	}

	switch (command) {
	case IDLE:
		break;
	case READTIME:
		ftime(&currTime);
		sTime = localtime(&currTime.time);
		pUIWorkspace[mm_SYStimeYear] = sTime->tm_year;
		pUIWorkspace[mm_SYStimeMonth] = sTime->tm_mon;
		pUIWorkspace[mm_SYStimeDay] = sTime->tm_mday;
		pUIWorkspace[mm_SYStimeDayOfWeek] = sTime->tm_wday;
		pUIWorkspace[mm_SYStimeHour] = sTime->tm_hour;
		pUIWorkspace[mm_SYStimeMinute] = sTime->tm_min;
		pUIWorkspace[mm_SYStimeSecond] = sTime->tm_sec;
		pUIWorkspace[mm_SYStimeMilliSeconds] = currTime.millitm;
		break;
	case READUTCTIME:
		ftime(&currTime);
		sTime = gmtime(&currTime.time);
		pUIWorkspace[mm_SYStimeYear] = sTime->tm_year;
		pUIWorkspace[mm_SYStimeMonth] = sTime->tm_mon;
		pUIWorkspace[mm_SYStimeDay] = sTime->tm_mday;
		pUIWorkspace[mm_SYStimeDayOfWeek] = sTime->tm_wday;
		pUIWorkspace[mm_SYStimeHour] = sTime->tm_hour;
		pUIWorkspace[mm_SYStimeMinute] = sTime->tm_min;
		pUIWorkspace[mm_SYStimeSecond] = sTime->tm_sec;
		pUIWorkspace[mm_SYStimeMilliSeconds] = currTime.millitm;
		break;
	case READCOUNTS:
/* 		clock_t counts = clock(); */
/* 		if (counts != -1) { */
/* 			pUIWorkspace[mm_SYStimeCounts] = counts; */
/* 			pUIWorkspace[mm_CountsPerMillisecond] = */
/* 			    (unit) CLOCKS_PER_SEC / 1000; */
/* 		} else { */
/* 			PRINTERROR("clock"); */
/* 			result = false; */
/* 		} */

		/* The use of gettimeofday is better than clock, because
		 * clock depends on the number of clock ticks spend for 
		 * this application.
		 */
		{
			struct timeval tv;
			if (gettimeofday(&tv, NULL) != -1) {
				pUIWorkspace[mm_SYStimeCounts] =
				    tv.tv_sec * 1000000 + tv.tv_usec;
				pUIWorkspace[mm_CountsPerMillisecond] = 1000;
			} else {
				PRINTERROR("gettimeofday");
				result = false;
			}
		}
		break;
	default:
		result = false;
		break;
	}

	return result;
}