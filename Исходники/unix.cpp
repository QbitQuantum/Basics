/*
 *--Full format

            1         2         3         4         5         6         7
  01234567890123456789012345678901234567890123456789012345678901234567890123456789
  Sep  1  1990   - start with ' '
  Sep 11 11:59
  Sep 11 01:59   - start with 0
  Sep 11  1:59   - start with ' '
  Dec 12 1989
  FCv 23 1990

 *--Short format:

            1         2         3         4         5         6         7
  01234567890123456789012345678901234567890123456789012345678901234567890123456789
  f 01:07   - time
  f 01:7    - minutes with one digit
  F 15:43
  f  2002   - only year

 *--Expanded format:

            1         2         3         4         5         6         7
  01234567890123456789012345678901234567890123456789012345678901234567890123456789
 *2005-06-20 14:22
 *2005-07-08 19:21
 *2004-10-14 14:14
 *2004-10-14 14:14
*/
BOOL net_convert_unix_date(LPSTR& datestr, Time_t& decoded)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	st.wMilliseconds = 0;
	st.wSecond       = 0;
	st.wDayOfWeek    = 0;
	char *bcol = datestr;         /* Column begin */
	char *ecol;                   /* Column end */
	//Expanded format (DDDD-)
	if(NET_IS_DIGIT(bcol[0]) && NET_IS_DIGIT(bcol[1]) && NET_IS_DIGIT(bcol[2]) && NET_IS_DIGIT(bcol[3]) &&
	        bcol[4] == '-')
	{
#define CVT( nm, start, end )              bcol[end] = 0;                       \
	st.nm = atoi(bcol+start);   \
	CHECK( (st.nm == MAX_WORD), FALSE )
		CVT(wYear,   0,  4)
		CVT(wMonth,  5,  7)
		CVT(wDay,    8, 10)
		CVT(wHour,  11, 13)
		CVT(wMinute,14, 16)
#undef CVT
		datestr = bcol + 17;
		return SystemTimeToFileTime(&st, decoded);
	}

	//Month+day or short format
	// (ecol must be set to char after decoded part)
	if(NET_TO_UPPER(bcol[0]) == 'F' &&
	        NET_IS_SPACE(bcol[1]))
	{
		//Short format - ignore month and day
		ecol = bcol + 2;
	}
	else
	{
		//Month
		if(NET_IS_DIGIT(bcol[0]) && NET_IS_DIGIT(bcol[1]) && NET_IS_SPACE(bcol[2]))
			st.wMonth = AtoI(bcol,MAX_WORD);
		else
			st.wMonth = NET_MonthNo(datestr);

		CHECK((st.wMonth == MAX_WORD), FALSE)
		bcol = SkipSpace(SkipNSpace(bcol));
		CHECK((*bcol == 0), FALSE)
		//Day
		ecol = SkipNSpace(bcol);

		if(*ecol != ' ')
			return FALSE;

		*ecol = 0;
		st.wDay = AtoI(bcol,MAX_WORD);
		*ecol = ' ';
		CHECK((st.wDay == MAX_WORD), FALSE)
	}

	//Year or time
	ecol = SkipSpace(ecol);
	bcol = ecol;

	if(bcol[2] != ':' && bcol[1] != ':')
	{
		//Four digits year
		ecol = SkipDigit(bcol);
		CHECK((ecol == bcol), FALSE)
		*ecol = 0;
		st.wYear = AtoI(bcol,MAX_WORD);
		ecol++;
		CHECK((st.wYear == MAX_WORD), FALSE)

		//Only first three digits of year with cut last digit
		if(st.wYear > 190 && st.wYear < 300)
		{
			st.wYear *= 10;
		}

		st.wSecond = 0;
		st.wMinute = 0;
		st.wHour   = 0;
	}