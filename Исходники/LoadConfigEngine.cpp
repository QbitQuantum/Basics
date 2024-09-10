int LoadConfigEngine::StopThread(void)
{
	void *pReturnValue = 0;

	return pthread_join(GetThreadID(), &pReturnValue);
}