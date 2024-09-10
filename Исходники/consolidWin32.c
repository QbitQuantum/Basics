uint32_t getCurrentProcessorNumber()
{
#if _WIN32_WINNT >= 0x0600
	return GetCurrentProcessorNumber();
#else
	return 0;
#endif
}