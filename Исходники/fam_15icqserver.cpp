static int calcAgeFromBirthDate(double dDate)
{
	if (dDate > 0)
	{ // date is stored as double with unit equal to a day, incrementing since 1/1/1900 0:00 GMT
		SYSTEMTIME sDate = {0};
		if (VariantTimeToSystemTime(dDate + 2, &sDate))
		{
			SYSTEMTIME sToday = {0};

			GetLocalTime(&sToday);

			int nAge = sToday.wYear - sDate.wYear;

			if (sToday.wMonth < sDate.wMonth || (sToday.wMonth == sDate.wMonth && sToday.wDay < sDate.wDay))
				nAge--;

			return nAge;
		}
	}
	return 0;
}