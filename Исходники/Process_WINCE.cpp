void ProcessImpl::timesImpl(long& userTime, long& kernelTime)
{
	FILETIME ftCreation;
	FILETIME ftExit;
	FILETIME ftKernel;
	FILETIME ftUser;

	if (GetThreadTimes(GetCurrentThread(), &ftCreation, &ftExit, &ftKernel, &ftUser) != 0)
	{
		ULARGE_INTEGER time;
		time.LowPart  = ftKernel.dwLowDateTime;
		time.HighPart = ftKernel.dwHighDateTime;
		kernelTime    = long(time.QuadPart/10000000L);
		time.LowPart  = ftUser.dwLowDateTime;
		time.HighPart = ftUser.dwHighDateTime;
		userTime      = long(time.QuadPart/10000000L);
	}
	else
	{
		userTime = kernelTime = -1;
	}
}