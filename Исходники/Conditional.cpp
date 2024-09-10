	void Conditional::Wait(Mutex *mutex, Int microseconds) {
		//printf("Wait(%s) start\n", mName.GetCString());
	#if defined(FastOSWindows)
		if (0 > microseconds)
			SleepConditionVariableCS(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, INFINITE);
		else
			SleepConditionVariableCS(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, microseconds / 1000);
	#elif defined(FastOSUnixLike)
		if (0 > microseconds)
			pthread_cond_wait(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs);
		else {
			struct timespec timeToWait;
			struct timeval now;
			gettimeofday(&now, NULL);
			timeToWait.tv_sec = now.tv_sec + (microseconds / 1000000);
			timeToWait.tv_nsec = 1000 * (now.tv_usec + (microseconds -
				((microseconds / 1000000) * 1000000)));
			pthread_cond_timedwait(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, &timeToWait);
		}
	#endif
		//printf("Wait(%s) end\n", mName.GetCString());
	}