_CODE_ACCESS struct tm *localtime(const time_t *timer)
{
    struct tm *local_tm_ptr = __TI_TLS_DATA_PTR(local_tm);
    time_t ltime  = timer ? *timer : 0;
 
    local_tm_ptr->tm_sec  = 0;
    local_tm_ptr->tm_min  = 0;
    local_tm_ptr->tm_hour = 0;
    local_tm_ptr->tm_mday = 1;
    local_tm_ptr->tm_mon  = 0;
    local_tm_ptr->tm_year = 0;
 
    if (timer == 0 || ltime == (time_t)-1) return local_tm_ptr;
 
#if INT_MAX <= 32767
    /*------------------------------------------------------------------*/
    /* MAKE SURE THE NUMBER OF SECONDS SINCE Jan 1, 1900 CAN BE         */
    /* REPRESENTED IN SIGNED INTS.                                      */
    /*------------------------------------------------------------------*/
    local_tm_ptr->tm_sec   =  ltime % SECS_IN_MIN;
    local_tm_ptr->tm_min   = (ltime / SECS_IN_MIN) % MINS_IN_HR;
    local_tm_ptr->tm_hour  = (ltime / SECS_IN_HR)  % HRS_IN_DAY;
 
    /*------------------------------------------------------------------*/
    /* CONVERT ltime TO NUMBER OF DAYS                                  */
    /*------------------------------------------------------------------*/
    ltime /= SECS_IN_DAY;
 
    /*------------------------------------------------------------------*/
    /* TO DETERMINE THE YEAR, INSTEAD OF DIVIDING BY 365, DO A SUBTRACT */
    /* LOOP THAT ACCOUNTS FOR LEAP YEARS.                               */
    /*------------------------------------------------------------------*/
    {
	int year = 0;
	while (ltime >= DAYS_IN_YR(year))
	{
	    ltime -= DAYS_IN_YR(year);
	    ++year;
	}
     
	local_tm_ptr->tm_year  = year;
	local_tm_ptr->tm_mday += ltime;
    }
 
#else
    /*------------------------------------------------------------------*/
    /* MAKE SURE THE NUMBER OF SECONDS SINCE Jan 1, 1900 CAN BE         */
    /* REPRESENTED IN SIGNED INTS.                                      */
    /*------------------------------------------------------------------*/
    if ((int)ltime < 0)
    {
	local_tm_ptr->tm_sec  = ltime % 60; 
	local_tm_ptr->tm_min  = ltime / 60; 
    }
    else local_tm_ptr->tm_sec = ltime;
#endif
 
    /*------------------------------------------------------------------*/
    /* MAKE VALUES IN local INTO A VALID TIME.                          */
    /*------------------------------------------------------------------*/
    mktime(local_tm_ptr);
    return local_tm_ptr;
}