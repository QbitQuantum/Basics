ULONG GetCurrentTime()
{
	LARGE_INTEGER currentSystemTime;
	LARGE_INTEGER currentLocalTime;
	ULONG time;

	KeQuerySystemTime(&currentSystemTime);
	ExSystemTimeToLocalTime(&currentSystemTime,&currentLocalTime);
	RtlTimeToSecondsSince1970(&currentLocalTime, &time);
	return time;
}