void Condition::signal()
{
#if defined(OS_WINDOWS_VISTA_DISABLED)
	WakeConditionVariable(&cond);
#elif defined(OS_WINDOWS)
	PulseEvent(cond);
#elif defined(OS_UNIX)
	pthread_cond_signal(&cond);
#endif
}