void vcmosRefresh()
{
	static time_t tprev = 0;
	time_t tcurr;
	struct tm *ptm;
	t_nubit8 century,year,month,mday,wday,hour,min,sec;

	tcurr = time(NULL);
	if (tcurr == tprev) return;
	else tprev = tcurr;
	ptm = LOCALTIME(&tcurr);

	century = (t_nubit8)(19 + ptm->tm_year / 100);
	year    = (t_nubit8)(ptm->tm_year % 100);
	month   = (t_nubit8)(ptm->tm_mon + 0x01);
	mday    = (t_nubit8)(ptm->tm_mday);
	wday    = (t_nubit8)(ptm->tm_wday + 0x01);
	hour    = (t_nubit8)(ptm->tm_hour);
	min     = (t_nubit8)(ptm->tm_min);
	sec     = (t_nubit8)(ptm->tm_sec);

	vcmos.reg[VCMOS_RTC_SECOND]    = Hex2BCD(sec);
	vcmos.reg[VCMOS_RTC_MINUTE]    = Hex2BCD(min);
	vcmos.reg[VCMOS_RTC_HOUR]      = Hex2BCD(hour);
	vcmos.reg[VCMOS_RTC_DAY_WEEK]  = Hex2BCD(wday);
	vcmos.reg[VCMOS_RTC_DAY_MONTH] = Hex2BCD(mday);
	vcmos.reg[VCMOS_RTC_MONTH]     = Hex2BCD(month);
	vcmos.reg[VCMOS_RTC_YEAR]      = Hex2BCD(year);
	vcmos.reg[VCMOS_RTC_CENTURY]   = Hex2BCD(century);
}