// update an alarm so that the systemtime reflects the next time the alarm will go off, based on the last_check time
bool UpdateAlarm(SYSTEMTIME &time, Occurrence occ) {

	FILETIME ft_now, ft_then;
	ULARGE_INTEGER uli_then;

	switch(occ) {
	case OC_DAILY:
	case OC_WEEKDAYS:
	case OC_WEEKLY:
		time.wDay = last_check.wDay;
	case OC_MONTHLY:
		time.wMonth = last_check.wMonth;
	case OC_YEARLY:
		time.wYear = last_check.wYear;
	case OC_ONCE:
		break; // all fields valid
	};

	SystemTimeToFileTime(&last_check, &ft_now); // consider 'now' to be last check time
	SystemTimeToFileTime(&time, &ft_then);
	
	switch(occ) {
	case OC_ONCE:
		if (CompareFileTime(&ft_then, &ft_now) < 0)
			return false;
		break;
	case OC_YEARLY:
		while(CompareFileTime(&ft_then, &ft_now) < 0) {
			time.wYear++;
			SystemTimeToFileTime(&time, &ft_then);
		}
		break;
	case OC_MONTHLY:
		while(CompareFileTime(&ft_then, &ft_now) < 0) {
			if (time.wMonth == 12) {
				time.wMonth = 1;
				time.wYear++;
			} else
				time.wMonth++;
			SystemTimeToFileTime(&time, &ft_then);
		}
		break;
	case OC_WEEKLY:
		{
			SYSTEMTIME temp;
			uli_then.HighPart = ft_then.dwHighDateTime;
			uli_then.LowPart = ft_then.dwLowDateTime;
			FileTimeToSystemTime(&ft_then, &temp);
			do {
				if (temp.wDayOfWeek != time.wDayOfWeek || CompareFileTime(&ft_then, &ft_now) < 0) {
					uli_then.QuadPart += mult.QuadPart * (ULONGLONG)24 * (ULONGLONG)60;
					ft_then.dwHighDateTime = uli_then.HighPart;
					ft_then.dwLowDateTime = uli_then.LowPart;
					FileTimeToSystemTime(&ft_then, &temp);
				}
			} while(temp.wDayOfWeek != time.wDayOfWeek || CompareFileTime(&ft_then, &ft_now) < 0);
		}
		break;
	case OC_WEEKDAYS:
		{
			SYSTEMTIME temp;
			uli_then.HighPart = ft_then.dwHighDateTime;
			uli_then.LowPart = ft_then.dwLowDateTime;
			do {
				FileTimeToSystemTime(&ft_then, &temp);
				if (temp.wDayOfWeek == 0 || temp.wDayOfWeek == 6 || CompareFileTime(&ft_then, &ft_now) < 0) {
					uli_then.QuadPart += mult.QuadPart * (ULONGLONG)24 * (ULONGLONG)60;
					ft_then.dwHighDateTime = uli_then.HighPart;
					ft_then.dwLowDateTime = uli_then.LowPart;
				}
			} while(temp.wDayOfWeek == 0 || temp.wDayOfWeek == 6 || CompareFileTime(&ft_then, &ft_now) < 0);
		}
		break;
	case OC_DAILY:
		uli_then.HighPart = ft_then.dwHighDateTime;
		uli_then.LowPart = ft_then.dwLowDateTime;
		while(CompareFileTime(&ft_then, &ft_now) < 0) {
			uli_then.QuadPart += mult.QuadPart * (ULONGLONG)24 * (ULONGLONG)60;
			ft_then.dwHighDateTime = uli_then.HighPart;
			ft_then.dwLowDateTime = uli_then.LowPart;
		}
		break;
	}

	FileTimeToSystemTime(&ft_then, &time);
	return true;
}