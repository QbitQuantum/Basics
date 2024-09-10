bool MCS_datetimetouniversal(MCDateTime& x_datetime)
{
	struct tm t_local_datetime;
	datetime_to_tm(true, x_datetime, t_local_datetime);

	__time64_t t_universal_time;
	t_universal_time = _mktime64(&t_local_datetime);
	if (t_universal_time == -1)
		return false;

	struct tm t_universal_tm;
	_gmtime64_s(&t_universal_tm, &t_universal_time);

	tm_to_datetime(false, t_universal_tm, x_datetime);

	return true;
}