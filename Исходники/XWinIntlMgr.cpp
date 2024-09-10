void XWinIntlMgr::FormatDate( const VTime& inDate, VString& outDate, EOSFormats inFormat, bool inUseGMTTimeZoneForDisplay)
{
	// Prepare SYSTEMTIME for windows.
	sWORD YY = 0;
	sWORD MM = 0;
	sWORD DD = 0;
	sWORD hh = 0;
	sWORD mm = 0;
	sWORD ss = 0;
	sWORD ms = 0;
	if (inUseGMTTimeZoneForDisplay)
		inDate.GetUTCTime (YY,MM,DD,hh,mm,ss,ms);
	else
		inDate.GetLocalTime (YY,MM,DD,hh,mm,ss,ms);

	// Verify if date >1st Jan 1601 (GetDateFormat doesn't support earlier dates.
	if (YY>=1601)
	{
		// Let the OS do it's job.
		UniChar acBuffer[256];

		SYSTEMTIME osDate={0};
		osDate.wYear=YY;
		osDate.wMonth=MM;
		osDate.wDay=DD;
		osDate.wHour=hh;
		osDate.wMinute=mm;
		osDate.wSecond=ss;
		osDate.wMilliseconds=ms;

		if (inFormat == eOS_MEDIUM_FORMAT)
		{
			VString pattern;
			if (GetLocaleInfo( LOCALE_SLONGDATE, pattern))
			{
				// replace long month and date by medium ones
				pattern.ExchangeRawString( CVSTR( "MMMM"), CVSTR( "MMM"));
				pattern.ExchangeRawString( CVSTR( "dddd"), CVSTR( "ddd"));
				if (::GetDateFormatW( fDialect, 0, &osDate, pattern.GetCPointer(), acBuffer, sizeof(acBuffer)))
					outDate = acBuffer;
			}
		}
		else
		{
			// Let the OS do the stuff.
			DWORD dateFormat = (inFormat == eOS_SHORT_FORMAT) ? DATE_SHORTDATE : DATE_LONGDATE;
			if (::GetDateFormatW(fDialect,dateFormat,&osDate,NULL,acBuffer,sizeof(acBuffer)))
				outDate = acBuffer;
		}
	}
	else
	{
		// Get the date pattern
		VString pattern;
		if (GetLocaleInfo( (inFormat == eOS_LONG_FORMAT) ? LOCALE_SLONGDATE : LOCALE_SSHORTDATE, pattern))
		{
			XBOX::VString tokens="gyMd";
			UniChar oldToken=0;
			sLONG count=0;
			pattern.AppendChar(' ');
			sLONG YY2=YY%100;
			XBOX::VString oneName;
			for (int pos=0;pos<pattern.GetLength();pos++)
			{
				UniChar token=pattern[pos];
				if (tokens.FindUniChar(token)>=1)
				{
					if (token==oldToken)
						count++;
					else
					{
						if (!count)
						{
							count=1;
							oldToken=token;
						}
					}
				}

				if (count && token!=oldToken)
				{
					switch(oldToken)
					{
					case 'g':
						if (count==2)
						{
							// TODO: ERA will be added if really wanted.
						}
						else
						{
							for (int i=0;i<count;i++)
								outDate.AppendUniChar(oldToken);
						}
						break;

					case 'y':	// YEAR
						switch(count)
						{
						case 5:
						case 4:		// 4 or more digits date
							outDate.AppendLong(YY);
							break;

						case 2:		// 2 digits with starting 0.
							if (YY2<=9)
								outDate.AppendLong(0);
						case 1:		// 1 or 2 digits
							outDate.AppendLong(YY2);
							break;

						default:
							for (int i=0;i<count;i++)
								outDate.AppendUniChar(oldToken);
							break;
						}
						break;

					case 'M':	// MONTH
						switch(count)
						{
						case 4:	// Long name
						case 3:	// Abbreviated name
							if (GetLocaleInfo( ((count==4) ? LOCALE_SMONTHNAME1 : LOCALE_SABBREVMONTHNAME1) + MM - 1, oneName))
								outDate += oneName;
							break;

						case 2:	// 2 digits number (leading 0)
							if (MM<=9)
								outDate.AppendLong(0);
						case 1:	// 1 or 2 digits number
							outDate.AppendLong(MM);
							break;

						default:
							for (int i=0;i<count;i++)
								outDate.AppendUniChar(oldToken);
							break;
						}
						break;

					case 'd':	// DAY
						switch(count)
						{
						case 4:	// Weekday long name
						case 3:	// Weekday abbreviated name
							if (GetLocaleInfo( ((count==4) ? LOCALE_SDAYNAME1 : LOCALE_SABBREVDAYNAME1) + (inDate.GetWeekDay() + 6) % 7, oneName))
								outDate += oneName;
							break;

						case 2:	// Month day on 2 digits (leading 0)
							if (DD<=9)
								outDate.AppendLong(0);
						case 1:	// Month day on 1 or 2 digits.
							outDate.AppendLong(DD);
							break;

						default:
							for (int i=0;i<count;i++)
								outDate.AppendUniChar(oldToken);
							break;
						}
						break;

					}
					count=0;
				}

				if (!count)
					outDate.AppendUniChar(token);
				oldToken=token;
			}

			// Remove the extra space at end of pattern.
			if (outDate.GetLength()>1)
				outDate.SubString(1,outDate.GetLength()-1);
		}
	}
}