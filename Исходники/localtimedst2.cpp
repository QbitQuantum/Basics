int
main(int argc, char * argv[])
{
	if(argc!=2)
	{
		printf("usage: localtime HH:MM:SS\n");
        printf("will add enough to current time to make it that time\n");
        printf("will assume the start is just before DST, Oct 27 2002 1:30am,");
        printf(" at 2 am it's fall back so it'll be 1 hr back 1 2am\n");
        exit(0);
	}
    unsigned int hour = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;

    if (sscanf(argv[1], "%u:%u:%u", &hour, &minutes, &seconds) != 3)
    {
        printf("time %s is not correct format, should be HH:MM:SS\n",
                argv[1]);
        exit(0);
    }
    printf("Want to add: hour(%u), minutes(%u), seconds(%u)\n",
            hour, minutes, seconds);

    time_t currTime = 0;
    time_t gcTime = 0;

    struct tm timeStruct;
    struct tm gcStruct;

/*
    // error setup of time before jan 1 1970 dec 31 1969
    timeStruct.tm_sec = 0;
    timeStruct.tm_min = 1;
    timeStruct.tm_hour = 2;
    timeStruct.tm_mday = 31;
    timeStruct.tm_mon = 11;
    timeStruct.tm_year = 69;
    timeStruct.tm_wday = 0;
    timeStruct.tm_yday = 365;
    timeStruct.tm_isdst = 0; // not dst
*/

    // setup the current time as oct 24 2:01am
    //
/*
    timeStruct.tm_sec = 0;
    timeStruct.tm_min = 1;
    timeStruct.tm_hour = 2;
    timeStruct.tm_mday = 24;
    timeStruct.tm_mon = 9;
    timeStruct.tm_year = 102;
    timeStruct.tm_wday = 0;
    timeStruct.tm_yday = 296;
    timeStruct.tm_isdst = 1; // currently dst
*/

    // Set time to Apr 4th 2:30am not DST, apr 7th 2002 at 2am is dst
    //
    timeStruct.tm_sec = 0;
    timeStruct.tm_min = 30;
    timeStruct.tm_hour = 2;
    timeStruct.tm_mday = 4;
    timeStruct.tm_mon = 3;
    timeStruct.tm_year = 102;
    timeStruct.tm_wday = 0;
    timeStruct.tm_yday = 93;
    timeStruct.tm_isdst = 0; // currently not dst

    printf("current time: %s\n", asctime(&timeStruct));
    currTime = mktime(&timeStruct);

    localtime_r(&currTime, &gcStruct);
    printf("current time after mktime and localtime: %s\n", asctime(&gcStruct));

    // need to adjust current time so gc time is 
    // properly setup
    //
    // figure out the # hrs and minutes the gc 
    // time is less by.
    //
    int diffHr = timeStruct.tm_hour - hour; 
    int diffMin = timeStruct.tm_min - minutes;
    int diffSec = timeStruct.tm_sec - seconds; 

    int dayAdded = 0;
    // Now lets create the gc time for next 24 hr
    //
    gcTime = currTime;

    if ((diffHr > 0) || ((diffHr == 0) && (diffMin > 0)) ||
        ((diffHr == 0) && (diffMin == 0) && (diffSec > 0)) )
    {
        // add day
        //
        timeStruct.tm_mday++; 
        dayAdded = 1;
    }

    // day added not true that means GC time is this day in future just set
    // the time and use mktime to normalize it
    //
    timeStruct.tm_hour = hour;
    timeStruct.tm_min = minutes;
    timeStruct.tm_sec = seconds;

    gcTime = mktime(&timeStruct);

    if (dayAdded)
    {
        // hour added check if the currTime is within 1 hr past the gc time if
        // the 1 day wasn't added
        //
        time_t dayOldGc = gcTime - (24 * 60 * 60);
        if ( ((currTime - dayOldGc) > 0) &&
             ((currTime - dayOldGc) <= (60 * 60)) )
        {
            // curr time is w/n 1 hr of day old gc time
            //
            printf("currTime is within 1hr past gc time\n");
        }
    }

    localtime_r(&gcTime, &gcStruct);

    printf("old time: %s\n", asctime(&timeStruct));
    printf("gc time: %s\n", asctime(&gcStruct));
    for (int i=1; i < 30; i++)
    {
        gcStruct.tm_hour = hour;
        gcStruct.tm_min = minutes;
        gcStruct.tm_sec = seconds;
        int isDstBefore = gcStruct.tm_isdst;
        gcStruct.tm_mday++; 
        gcTime = mktime(&gcStruct);
        if (isDstBefore != gcStruct.tm_isdst)
        {
            printf("DST change resting to make sure we can handle the time\n");
            // looks like dst changed.  Reset the time and normalize it.  
            // This will ensure that we can represent the time in the new zone.
            // 
            gcStruct.tm_hour = hour;
            gcStruct.tm_min = minutes;
            gcStruct.tm_sec = seconds;
            gcTime = mktime(&gcStruct);
        }
        printf("day:%d gc time: %s\n", i + 1, asctime(&gcStruct));
    }
	
	return 0;
}