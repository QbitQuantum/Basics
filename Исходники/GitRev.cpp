CTime GitRev::ConverFromString(CString input)
{
	// pick up date from string
	try
	{
		COleDateTime tm(_wtoi(input.Mid(0,4)),
				 _wtoi(input.Mid(5,2)),
				 _wtoi(input.Mid(8,2)),
				 _wtoi(input.Mid(11,2)),
				 _wtoi(input.Mid(14,2)),
				 _wtoi(input.Mid(17,2)));
		if( tm.GetStatus() != COleDateTime::valid )
			return CTime();//Error parsing time-string

		// pick up utc offset
		CString sign = input.Mid(20,1);		// + or -
		int hoursOffset =  _wtoi(input.Mid(21,2));
		int minsOffset = _wtoi(input.Mid(23,2));
		// convert to a fraction of a day
		double offset = (hoursOffset*60 + minsOffset) / 1440.0; // 1440 mins = 1 day
		if ( sign == "-" )
		{
			offset = -offset;
		}
		// we have to subtract this from the time given to get UTC
		tm -= offset;
		// get utc time as a SYSTEMTIME
		SYSTEMTIME sysTime;
		tm.GetAsSystemTime( sysTime );
		// and convert to users local time
		SYSTEMTIME local;
		if ( SystemTimeToTzSpecificLocalTime( &m_TimeZone, &sysTime, &local ) )
		{
			sysTime = local;
		}
		else
		{
			ASSERT(false);	// this should not happen but leave time in utc if it does
		}
		// convert to CTime and return
		return CTime( sysTime, -1 );
	}
	catch(CException* e)
	{
		//Probably the date was something like 1970-01-01 00:00:00. _mktime64() doesnt like this.
		//Dont let the application crash on this exception

#ifdef _AFX //CException classes are only defined when afx.h is included.
			//When afx.h is not included, the exception is leaked.
			//This will probably never happen because when CException is not defined, it cannot be thrown.
		e->Delete();
#else
		UNREFERENCED_PARAMETER(e);
#endif //ifdef _AFX
	}
	return CTime(); //Return an invalid time
}