static string_32 getFirstDayTime(int yyyymmdd, int dayOffset)
{
	if(yyyymmdd)
	{
		int y = yyyymmdd/10000;
		int m = (yyyymmdd/100) % 100;
		int d = yyyymmdd % 100;
		KLocalDatetime ldt = {y,m,d,0,0,0};
		KDatetime dt(ldt);
		dt.AddDay(dayOffset);
		return dt.ToString();
	}
	else
	{
		KDatetime dt;
		KLocalDatetime ldt = dt.GetLocalTime();
		ldt.hour = ldt.minute = ldt.second = 0;
		dt.SetLocalTime(ldt);
		dt.AddDay(dayOffset);
		return dt.ToString();
	}
}