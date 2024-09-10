time_t rtc_timegm(struct tm *tm)
{
	struct tm modified;
	memcpy(&modified, tm, sizeof(modified));
	return _mkgmtime(&modified);
}