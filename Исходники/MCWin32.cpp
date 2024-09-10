struct tm * mailcore::win32_gmtime_r(const time_t *clock, struct tm *result)
{
    gmtime_s(result, clock);
	return result;
}