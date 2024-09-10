int read_option_from_file(time_t *start_time, time_t *end_time, int *time_zone)
{
    struct timeval tv;
    struct timezone tz;
    struct tm tm_start, tm_end;
    struct tm *p_start, *p_end, *p_cur;
	int start_sday_of_week, end_sday_of_week;
    int i;
	time_t time_start_mon_1st, time_end_mon_1st; // The 1st day of start/end month of daylight saving time
  	char wday_start_mon_1st, wday_end_mon_1st; // The weekday of the 1th day in both start/end DLS months
   	char days2target_start_day, days2target_end_day;
   	
	
	FILE *fp;
	char buf[24], *pos;
	char daylight_saving_enable[2]={0};
	int start_week = 0, end_week = 0;

	fp = fopen("/var/etc/daylight_saving.conf", "r");
	if (fp == NULL) 
	{
		printf("Could not open /var/etc/daylight_saving.conf\n");
		return 0;
	}
	
	while (fgets(buf, sizeof(buf), fp) != NULL ) 
	{
		pos = buf;
		while (*pos != '\0') {
			if (*pos == '\n') {
				*pos = '\0';
				break;
			}
			pos++;
		}
		pos = strchr(buf, '=');
		
		if (pos == NULL) 
		{
			printf("daylight_saving.conf: invalid line '%s'\n", buf);
			continue;
		}
		pos++;
		
		if(strstr(buf, "enable")) 
			strncpy(daylight_saving_enable, pos, strlen(pos));
		else if(strstr(buf, "zone"))
			*time_zone = atoi(pos);
		else if(strstr(buf, "start_month"))
			tm_start.tm_mon = atoi(pos) - 1;
		else if(strstr(buf, "start_time"))
			tm_start.tm_hour = atoi(pos);
		else if(strstr(buf, "start_day_of_week"))
			tm_start.tm_wday = atoi(pos) - 1 ;
		else if(strstr(buf, "start_week"))
			start_week = atoi(pos);
		else if(strstr(buf, "end_month"))
			tm_end.tm_mon = atoi(pos) - 1;
		else if(strstr(buf, "end_time"))
			tm_end.tm_hour = atoi(pos);
		else if(strstr(buf, "end_day_of_week"))
			tm_end.tm_wday = atoi(pos) - 1;
		else if(strstr(buf, "end_week"))
			end_week = atoi(pos);
	}
	
	fclose(fp);
	  	
   	gettimeofday(&tv,&tz);
  	
	// DL 
	p_cur = localtime(&tv.tv_sec);
	
	DEBUG_MSG("start day of week %d \n",tm_start.tm_wday);
	tm_start.tm_year = p_cur->tm_year;
	tm_start.tm_yday = 0;
	tm_start.tm_mday = 1;
	tm_start.tm_min  = 0;
	tm_start.tm_sec  = 0;
	start_sday_of_week = tm_start.tm_wday;
	for( i = 1; i < tm_start.tm_mon + 1; i++)
	{
        if((tm_start.tm_year % 4) == 0)
       		tm_start.tm_yday += year_month_days[1][i];
       	else
       		tm_start.tm_yday += year_month_days[0][i];	
	}

	time_start_mon_1st = mktime(&tm_start);    
   	p_start = gmtime(&time_start_mon_1st); // only want tm_wday
   	wday_start_mon_1st = p_start->tm_wday;
	
    days2target_start_day = ( (start_week - 1) * 7) - wday_start_mon_1st + start_sday_of_week;

   	tm_start.tm_mday += days2target_start_day; // Now we know what month day is
   	tm_start.tm_yday += days2target_start_day; 		
		
	// End Time
	tm_end.tm_year = p_cur->tm_year;
	tm_end.tm_yday = 0;
	tm_end.tm_mday = 1;
	tm_end.tm_min  = 0;
   	tm_end.tm_sec = 0;
	end_sday_of_week = tm_end.tm_wday;

	for( i = 1; i < tm_end.tm_mon + 1; i++)
	{
   		if((tm_end.tm_year % 4) == 0)
       		tm_end.tm_yday += year_month_days[1][i];
       	else
       		tm_end.tm_yday += year_month_days[0][i];	
	}

   	time_end_mon_1st = mktime(&tm_end);    
  	p_end = gmtime(&time_end_mon_1st); // only want tm_wday
	wday_end_mon_1st = p_end->tm_wday;   
 
	days2target_end_day = (( end_week - 1) * 7) - wday_end_mon_1st + end_sday_of_week;
	tm_end.tm_mday += days2target_end_day; // Now we know what month day is
	tm_end.tm_yday += days2target_end_day; 			

 	DEBUG_MSG("\n,start Year:%d,Month:%d,Day:%d,Hour:%d\n",tm_start.tm_year+1900,tm_start.tm_mon+1,tm_start.tm_mday,tm_start.tm_hour);	
 	DEBUG_MSG("\n,end Year:%d,Month:%d,Day:%d,Hour:%d\n",tm_end.tm_year+1900,tm_end.tm_mon+1,tm_end.tm_mday,tm_end.tm_hour);	
 	//syslog(LOG_INFO,"\n,Year:%d,Month:%d,Day:%d,Hour:%d,Min:%d,Sec:%d\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);	

 	// Get Secs 
	*start_time = mktime(&tm_start);                            
	*end_time = mktime(&tm_end); 
          	   
	return 0;
}