void LanguageInfo::Set(int lang_)
{
	language = lang_;
	dword q = sGetLanguageDetails(language, &english_name, &native_name);	
	if(!q)
		return;

	getindexletter = DefaultGetIndexLetter;
	compare = DefaultLanguageCompare;
	if(language == LNG_('C','S','C','Z')) {
		getindexletter = CSCZGetIndexLetter;
		compare = CSCZLanguageCompare;
	}
#ifdef PLATFORM_WIN32
	LCID lcid = q;
	thousand_separator = GetLocaleInfoA(lcid, LOCALE_STHOUSAND);
	decimal_point = GetLocaleInfoA(lcid, LOCALE_SDECIMAL);
	static const LCTYPE months[] =
	{
		LOCALE_SMONTHNAME1,  LOCALE_SMONTHNAME2,  LOCALE_SMONTHNAME3,
		LOCALE_SMONTHNAME4,  LOCALE_SMONTHNAME5,  LOCALE_SMONTHNAME6,
		LOCALE_SMONTHNAME7,  LOCALE_SMONTHNAME8,  LOCALE_SMONTHNAME9,
		LOCALE_SMONTHNAME10, LOCALE_SMONTHNAME11, LOCALE_SMONTHNAME12,
	};
	static const LCTYPE smonths[] =
	{
		LOCALE_SABBREVMONTHNAME1,  LOCALE_SABBREVMONTHNAME2,  LOCALE_SABBREVMONTHNAME3,
		LOCALE_SABBREVMONTHNAME4,  LOCALE_SABBREVMONTHNAME5,  LOCALE_SABBREVMONTHNAME6,
		LOCALE_SABBREVMONTHNAME7,  LOCALE_SABBREVMONTHNAME8,  LOCALE_SABBREVMONTHNAME9,
		LOCALE_SABBREVMONTHNAME10, LOCALE_SABBREVMONTHNAME11, LOCALE_SABBREVMONTHNAME12,
	};
	ASSERT(__countof(months) == __countof(month_names));
	int i;
	for(i = 0; i < __countof(months); i++)
	{
		month_names[i] = GetLocaleInfoW(lcid, months[i]);
		short_month_names[i] = GetLocaleInfoW(lcid, smonths[i]);
	}
	static const LCTYPE days[] =
	{
		LOCALE_SDAYNAME1, LOCALE_SDAYNAME2, LOCALE_SDAYNAME3, LOCALE_SDAYNAME4,
		LOCALE_SDAYNAME5, LOCALE_SDAYNAME6, LOCALE_SDAYNAME7,
	};
	static const LCTYPE sdays[] =
	{
		LOCALE_SABBREVDAYNAME1, LOCALE_SABBREVDAYNAME2, LOCALE_SABBREVDAYNAME3, LOCALE_SABBREVDAYNAME4,
		LOCALE_SABBREVDAYNAME5, LOCALE_SABBREVDAYNAME6, LOCALE_SABBREVDAYNAME7,
	};
	ASSERT(__countof(days) == __countof(day_names));
	for(i = 0; i < __countof(days); i++)
	{
		day_names[i] = GetLocaleInfoW(lcid, days[i]);
		short_day_names[i] = GetLocaleInfoW(lcid, sdays[i]);
	}
#endif

#ifdef PLATFORM_POSIX
	String langtext = LNGAsText(language);
	char ltext[6];
	ltext[0] = ToLower(langtext[0]);
	ltext[1] = ToLower(langtext[1]);
	ltext[2] = '_';
	ltext[3] = ToUpper(langtext[3]);
	ltext[4] = ToUpper(langtext[4]);
	ltext[5] = 0;
	String oldloc = setlocale(LC_ALL, NULL);
	if(setlocale(LC_ALL, ltext))
	{
		const struct lconv *lc = localeconv();
		decimal_point = lc->decimal_point;
		thousand_separator = lc->thousands_sep;
		static const int months[] =
		{
			MON_1, MON_2, MON_3, MON_4, MON_5, MON_6, MON_7, MON_8, MON_9, MON_10, MON_11, MON_12,
		};
		static const int smonths[] =
		{
			ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6, ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12,
		};
		ASSERT(__countof(months) == __countof(month_names) && __countof(smonths) == __countof(month_names));
		int i;
		for(i = 0; i < __countof(months); i++)
		{
			month_names[i] = nl_langinfo(months[i]);
			short_month_names[i] = nl_langinfo(smonths[i]);
		}
		static const int days[] =
		{ // Linux locale starts with Sunday
			DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7, DAY_1,
		};
		static const int sdays[] =
		{
			ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7, ABDAY_1,
		};
		ASSERT(__countof(days) == __countof(day_names) && __countof(sdays) == __countof(day_names));
		for(i = 0; i < __countof(days); i++)
		{
			day_names[i] = nl_langinfo(days[i]);
			short_day_names[i] = nl_langinfo(sdays[i]);
		}

		setlocale(LC_ALL, oldloc);
	}
#endif
	for(int i = 0; i < 12; i++) {
		month[i] = month_names[i].ToString();
		smonth[i] = short_month_names[i].ToString();
	}
	for(int i = 0; i < 7; i++) {
		day[i] = day_names[i].ToString();
		sday[i] = short_day_names[i].ToString();
	}
}