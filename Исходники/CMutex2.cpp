	//Specifies the amount of time to wait for the synchronization object to be available (signaled).
	//If INFINITE, Lock will wait until the object is signaled before returning.
	//DWORD TimeOut_ms = INFINITE = 4294967295
	int CMutex::Lock(int TimeOut_ms/* = 4294967295*/){
		//std::condition_variable_any;

//		printf("Thread %.8x %.8x: Waiting to get lock \n", t);

		long int tid = getThreadId();
		//printf("%s:%d Mutex: %s waiting max timout %d thread %ld lockCount %d", __FILE__, __LINE__, name,TimeOut_ms,tid,lockCount);
		using Ms = std::chrono::milliseconds;
		bool success = mutex.try_lock_for(Ms(TimeOut_ms));
		if(success){
			owner = tid;
			lockCount++;
		}

		//printf(" %s\n",success?"Success":"Failed");
		//printf(" %s lockCount %d \n",success?"Success":"Failed",lockCount);
		return success?1:0;
	}