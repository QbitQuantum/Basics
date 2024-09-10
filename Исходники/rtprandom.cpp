uint32_t RTPRandom::PickSeed()
{
	uint32_t x;
#if defined(WIN32) || defined(_WIN32_WINCE)
#ifndef _WIN32_WCE
	x = (uint32_t)_getpid();
	x += (uint32_t)time(0);
	x += (uint32_t)clock();
#else
	x = (uint32_t)GetCurrentProcessId();

	FILETIME ft;
	SYSTEMTIME st;
	
	GetSystemTime(&st);
	SystemTimeToFileTime(&st,&ft);
	
	x += ft.dwLowDateTime;
#endif // _WIN32_WCE
	x ^= (uint32_t)((uint8_t *)this - (uint8_t *)0);
#else
	x = (uint32_t)getpid();
	x += (uint32_t)time(0);
	x += (uint32_t)clock();
	x ^= (uint32_t)((uint8_t *)this - (uint8_t *)0);
#endif
	return x;
}