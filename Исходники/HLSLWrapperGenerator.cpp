wrBuffer GetCurrentDateTimeString()
{
	wrBuffer	currentDateTime;

	CalendarTime	localTime( CalendarTime::GetCurrentLocalTime() );

	String	timeOfDay;
	GetTimeOfDayString( localTime.hour, localTime.minute, localTime.second,
		timeOfDay );

	currentDateTime.Format(
		"on %s, %s %u%s, at %s",
		CalendarTime::WeekdayToStr( localTime.weekday ),
		CalendarTime::MonthToStr( localTime.month ),
		localTime.day, GetNumberExtension( localTime.day ),
		timeOfDay.ToChars()
	);

	return currentDateTime;
}