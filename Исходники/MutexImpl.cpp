		MutexImpl::MutexImpl()
		{
			InitializeCriticalSection(&myMutex);
		}