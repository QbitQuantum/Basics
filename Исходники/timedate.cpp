Time TimeFromUTC(int64 seconds)
{
	Time tm = Time(1970, 1, 1) + seconds;
	return tm - GetLeapSeconds(tm);
}