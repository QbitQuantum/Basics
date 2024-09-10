void CWE511_Logic_Time_Bomb__w32CompareFileTime_10_bad()
{
    if(globalTrue)
    {
        {
            SYSTEMTIME setTime, currentTime;
            FILETIME setTimeAsFileTime, currentTimeAsFileTime;
            /* Jan 1, 2008 12:00:00 PM */
            setTime.wYear         = 2008; /* Year */
            setTime.wMonth        = 1;    /* January */
            setTime.wDayOfWeek    = 0;    /* Ignored */
            setTime.wDay          = 1;    /* The first of the month */
            setTime.wHour         = 12;   /* 12 PM */
            setTime.wMinute       = 0;    /* 0 minutes into the hour */
            setTime.wSecond       = 0;    /* 0 seconds into the minute */
            setTime.wMilliseconds = 0;    /* 0 milliseconds into the second */
            GetSystemTime(&currentTime);
            /* Must convert to FILETIME for comparison */
            SystemTimeToFileTime(&currentTime, &currentTimeAsFileTime);
            SystemTimeToFileTime(&setTime, &setTimeAsFileTime);
            /* FLAW: After a certain date, delete a file */
            if (CompareFileTime(&currentTimeAsFileTime, &setTimeAsFileTime) == 1)
            {
                UNLINK("important_file.txt");
            }
        }
    }
}