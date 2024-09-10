dng_time_zone LocalTimeZone (const dng_date_time &dt)
	{
	
	dng_time_zone result;
	
	if (dt.IsValid ())
		{
		
		#if qMacOS
		
		CFTimeZoneRef zoneRef = CFTimeZoneCopyDefault ();
		
		if (zoneRef)
			{
			
			CFGregorianDate gregDate;

			gregDate.year   = dt.fYear;
			gregDate.month  = dt.fMonth;
			gregDate.day    = dt.fDay;
			gregDate.hour   = dt.fHour;
			gregDate.minute = dt.fMinute;
			gregDate.second = dt.fSecond;
			
			CFAbsoluteTime absTime = CFGregorianDateGetAbsoluteTime (gregDate, zoneRef);
			
			CFTimeInterval secondsDelta = CFTimeZoneGetSecondsFromGMT (zoneRef, absTime);
		
			CFRelease (zoneRef);
			
			result.SetOffsetSeconds (secondsDelta);
			
			if (result.IsValid ())
				{
				return result;
				}
			
			}
		
		#endif
		
		#if qWinOS
		
		if (GetTimeZoneInformation          != NULL &&
			SystemTimeToTzSpecificLocalTime != NULL &&
		    SystemTimeToFileTime            != NULL)
			{
			
			TIME_ZONE_INFORMATION tzInfo;
			
			DWORD x = GetTimeZoneInformation (&tzInfo);
			
			SYSTEMTIME localST;
			
			memset (&localST, 0, sizeof (localST));

			localST.wYear   = (WORD) dt.fYear;
			localST.wMonth  = (WORD) dt.fMonth;
			localST.wDay    = (WORD) dt.fDay;
			localST.wHour   = (WORD) dt.fHour;
			localST.wMinute = (WORD) dt.fMinute;
			localST.wSecond = (WORD) dt.fSecond;
			
			SYSTEMTIME utcST;

			if (TzSpecificLocalTimeToSystemTime (&tzInfo, &localST, &utcST))
				{
				
				FILETIME localFT;
				FILETIME utcFT;
				
				(void) SystemTimeToFileTime (&localST, &localFT);
				(void) SystemTimeToFileTime (&utcST  , &utcFT  );
				
				uint64 time1 = (((uint64) localFT.dwHighDateTime) << 32) + localFT.dwLowDateTime;
				uint64 time2 = (((uint64) utcFT  .dwHighDateTime) << 32) + utcFT  .dwLowDateTime;
				
				// FILETIMEs are in units to 100 ns.  Convert to seconds.
				
				int64 time1Sec = time1 / 10000000;
				int64 time2Sec = time2 / 10000000;
			
				int32 delta = (int32) (time1Sec - time2Sec);

				result.SetOffsetSeconds (delta);
					
				if (result.IsValid ())
					{
					return result;
					}
			
				}
			
			}
		
		#endif
		
		}
	
	// Figure out local time zone.
	
	dng_date_time_info current_info;
	
	CurrentDateTimeAndZone (current_info);
	
	result = current_info.TimeZone ();
		
	return result;
			
	}