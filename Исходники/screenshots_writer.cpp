static char const * current_time(string64 & dest_time)
{
	time_t		tmp_curr_time;
	
	dest_time[0]	= 0;
	_time64			(&tmp_curr_time);
	tm* tmp_tm		= _localtime64(&tmp_curr_time);

	sprintf_s(dest_time, sizeof(dest_time),
		"%02d.%02d.%d_%02d:%02d:%02d",
		tmp_tm->tm_mday, 
		tmp_tm->tm_mon+1, 
		tmp_tm->tm_year+1900, 
		tmp_tm->tm_hour, 
		tmp_tm->tm_min, 
		tmp_tm->tm_sec
	);
	return dest_time;
}