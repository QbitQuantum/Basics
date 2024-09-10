/*
 * FillRunTimeLog fill the global Result array with runtime timing parameters.
 *
 * Accepts:
 * -------
 * hProcess - handle to the process.
 * test_id - test id.
 */
void FillRunTimeLog(HANDLE hProcess,int test_id)
{
	SYSTEMTIME          UTC_Time, LocalTime;
	FILETIME            CreationTime, ExitTime, KernelTime, UserTime, TotalTime;
	int time_in_ms,kernel_time,user_time;
	int len1,len2,len3,len4;
	char test_id_str[MAX_INT_TO_STRING];
	char time_in_ms_str[MAX_INT_TO_STRING];
	char kernel_time_str[MAX_INT_TO_STRING];
	char user_time_str[MAX_INT_TO_STRING];
	char start_time_str[HH_MM_SS_MMM];
	
	GetProcessTimes(
		hProcess,
		&CreationTime,
		&ExitTime,
		&KernelTime,
		&UserTime
		);

	itoa(test_id,test_id_str,10);
	len1 = strlen(test_id_str);
	FileTimeToSystemTime(&CreationTime, /* input */
		&UTC_Time);

	SystemTimeToTzSpecificLocalTime(NULL, /* use default time zone */
		&UTC_Time,     /* input */
		&LocalTime);  /* output */

	
	sprintf(start_time_str,"%02d:%02d:%02d:%02d",LocalTime.wHour,LocalTime.wMinute, LocalTime.wSecond,LocalTime.wMilliseconds);

	TotalTime = SubtractFiletimes(ExitTime, CreationTime);

	time_in_ms = TotalTime.dwLowDateTime / FILETIME_UNITS_PER_MILLISECOND;
	itoa(time_in_ms,time_in_ms_str,10);
	len2 = strlen(time_in_ms_str);

	FileTimeToSystemTime(&TotalTime, /* input */
		&UTC_Time);    /* output */

	if ((KernelTime.dwHighDateTime == 0) &&
		(UserTime.dwHighDateTime == 0))
	{

		kernel_time = KernelTime.dwLowDateTime / FILETIME_UNITS_PER_MILLISECOND;
		itoa(kernel_time,kernel_time_str,10);
		len3 = strlen(kernel_time_str);

		user_time = UserTime.dwLowDateTime / FILETIME_UNITS_PER_MILLISECOND;
		itoa(user_time,user_time_str,10);
		len4 = strlen(user_time_str);
	}
	else
	{
		printf("This function can only print the Kernel Time and User Time "
			"if they are small enough to be held in a single DWORD each. "
			"That is not true, so they will not be printed. ");
	}

	shared_result[test_id-1].runtime_log_line = (char*)malloc(sizeof(char)*(HH_MM_SS_MMM + LOG_RUNTIME_LINE + len1 + len2 + len3 + len4) + 1);

	if(shared_result[test_id-1].runtime_log_line == NULL)
	{
		printf("Failed to allocate memory for FillRunTimeLog function \n");
		exit(1);
	}

	sprintf(shared_result[test_id-1].runtime_log_line,"Test #%s : start_time=%s total_time=%s user_time=%s kernel_time=%s",test_id_str,start_time_str,time_in_ms_str,user_time_str,kernel_time_str);
	shared_result[test_id-1].result_id = test_id;
	
}