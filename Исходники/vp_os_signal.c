void
vp_os_cond_wait(vp_os_cond_t *cond)
{
	#if defined USE_WINDOWS_CONDITION_VARIABLES
		SleepConditionVariableCS(&cond->cond, (CRITICAL_SECTION *)cond->mutex, INFINITE);
	#elif defined USE_PTHREAD_FOR_WIN32
		pthread_cond_wait(&cond->cond, (pthread_mutex_t *)cond->mutex);
	#else
		WaitForSingleObject(cond->LockSemaphore,INFINITE); // TODO: to test
	#endif
}