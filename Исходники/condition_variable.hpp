	void wait(cybozu::Mutex& mutex)
	{
#ifdef _WIN32
		EnterCriticalSection(&waiterNumLock_);
		waiterNum_++;
		LeaveCriticalSection(&waiterNumLock_);

		SignalObjectAndWait(mutex.hdl_, sema_, INFINITE, FALSE);
		EnterCriticalSection(&waiterNumLock_);

		waiterNum_--;
		int last_waiter = wasBroadcast_ && waiterNum_ == 0;

		LeaveCriticalSection (&waiterNumLock_);
		if (last_waiter) {
			SignalObjectAndWait(waiterDone_, mutex.hdl_, INFINITE, FALSE);
		} else {
			WaitForSingleObject(mutex.hdl_, INFINITE);
		}
#else
		pthread_cond_wait(&cv_, &mutex.hdl_);
#endif
	}