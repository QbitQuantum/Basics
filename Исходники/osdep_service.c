void rtw_yield_os()
{
#ifdef PLATFORM_LINUX
	yield();
#endif
#ifdef PLATFORM_FREEBSD
	yield();
#endif
#ifdef PLATFORM_WINDOWS
	SwitchToThread();
#endif
}