DWORD __alertable_wait(HANDLE handle, uint32_t millisec)
{
	LARGE_INTEGER eta, now;
	GetSystemTimeAsFileTime((FILETIME*)&eta);
	eta.QuadPart += (millisec * 10000UI64);
	for (;;)
	{
		DWORD status = WaitForSingleObjectEx(handle, millisec, TRUE);
		if (status != WAIT_IO_COMPLETION)
			return status;

		if (millisec != INFINITE && millisec != 0)
		{
			GetSystemTimeAsFileTime((FILETIME*)&now);
			LONGLONG diff = (eta.QuadPart - now.QuadPart) / 10000;
			if (diff < 0) // very very very very important this is < and not <=!
				return WAIT_TIMEOUT;
			millisec = (uint32_t)diff;
		}
	}
}