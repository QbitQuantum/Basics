void VHTTPServerLog::_GetCurrentFormatedDate (XBOX::VString& outDateString, bool inLocalTime, const char inDateSeparator)
{
	sWORD		year, month, day, hour, minute, seconds, milliseconds;
	XBOX::VTime	time;
	
	time.FromSystemTime();	// GMT time
	if (inLocalTime)
		time.GetLocalTime (year, month, day, hour, minute, seconds, milliseconds);
	else
		time.GetUTCTime (year, month, day, hour, minute, seconds, milliseconds);
	
	outDateString.Clear();
	outDateString.Printf ("%04d%c%02d%c%02d %02d:%02d:%02d",	year, inDateSeparator,
																month, inDateSeparator, day,
																hour, minute, seconds);
}