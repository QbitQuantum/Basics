static void gettimespec(struct timespec* tp)
{
	FILETIME curr;
	GetSystemTimeAsFileTime(&curr);
	convert_filetime_to_timespec(&curr, tp, 0);
}