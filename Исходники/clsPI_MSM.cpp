int clsPI_MSM::JulianDay(time_t date)
{
	struct tm dateInfo;
	LocalTime(date,&dateInfo);
	return dateInfo.tm_yday + 1;
}