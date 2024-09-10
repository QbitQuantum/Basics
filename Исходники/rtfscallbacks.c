static void pc_get_system_date(DATESTR * pd)
{
#ifdef RTFS_WINDOWS
	/* Windows runtime provides rotuines specifically for this purpose */
    SYSTEMTIME systemtime;
    FILETIME filetime;

    GetLocalTime(&systemtime);
    SystemTimeToFileTime(&systemtime, &filetime);
    FileTimeToDosDateTime(&filetime, &pd->date, &pd->time);
#else
    word  year;     /* relative to 1980 */
    word  month;    /* 1 - 12 */
    word  day;      /* 1 - 31 */
    word  hour;
    word  minute;
    word  sec;      /* Note: seconds are 2 second/per. ie 3 == 6 seconds */

#ifdef RTFS_LINUX
#define USE_ANSI_TIME 1	  /* Linux supports it */
#else
#define USE_ANSI_TIME 0   /* Enable if your runtime environment supports ansi time functions */
#endif
#if (USE_ANSI_TIME)
	{ /* Use ansi time functions. */
    struct tm *timeptr;
    time_t timer;

    time(&timer);
    timeptr = localtime(&timer);

    hour    =   (word) timeptr->tm_hour;
    minute  =   (word) timeptr->tm_min;
    sec =   (word) (timeptr->tm_sec/2);
    /* Date comes back relative to 1900 (eg 93). The pc wants it relative to
        1980. so subtract 80 */
    year  = (word) (timeptr->tm_year-80);
    month = (word) (timeptr->tm_mon+1);
    day   = (word) timeptr->tm_mday;
	}
#else /* In not windows and not using ansi time functions use hardwired values. */
    /* Modify this code if you have a clock calendar chip and can retrieve the values from that device instead */
    hour = 19;    /* 7:37:28 PM */
    minute = 37;
    sec = 14;
    /* 3-28-2008 */
    year  = 18;       /* relative to 1980 */
    month = 3;      /* 1 - 12 */
    day   = 28;       /* 1 - 31 */
#endif
    pd->time = (word) ( (hour << 11) | (minute << 5) | sec);
    pd->date = (word) ( (year << 9) | (month << 5) | day);
#endif /* #ifdef WINDOWS #else */

}