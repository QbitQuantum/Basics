// GetSystemTimeAsFileTime 
// Retrieves the current system date and time. The information is in Coordinated Universal Time (UTC) format. 
void getTimeAccuracy_GetSystemTimePreciseAsFileTime() {
	// FILETIME structure 
	// Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
	FILETIME start, finish;

	GetSystemTimePreciseAsFileTime(&start);
	do {
		GetSystemTimePreciseAsFileTime(&finish);
	} while (start.dwLowDateTime == finish.dwLowDateTime);

	unsigned _int64 startTime = (((unsigned _int64)start.dwHighDateTime) << 32) | (start.dwLowDateTime);
	unsigned _int64 finishTime = (((unsigned _int64)finish.dwHighDateTime) << 32) | (finish.dwLowDateTime);
	unsigned _int64 accuracy = finishTime - startTime;

	printf("TimeAccuracy_GetSystemTimePreciseAsFileTime: %I64d", accuracy);
}