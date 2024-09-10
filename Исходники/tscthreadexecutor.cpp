unsigned int TscThreadExecutor::multi_thread(ThreadProc threadProc)
{

	TSC_THREAD *threadHandles = new TSC_THREAD[_settings._jobs];

	TSC_LOCK_INIT(&_fileSync);
	TSC_LOCK_INIT(&_errorSync);
	TSC_LOCK_INIT(&_reportSync);


#ifdef TSC_THREADING_MODEL_WIN

	for (unsigned int i = 0; i < _settings._jobs; ++i) {
		threadHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadProc, this, 0, NULL);
		if (!threadHandles[i]) {
			std::cerr << "#### .\nTscThreadExecutor::check error, errno :" << errno << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	DWORD waitResult = WaitForMultipleObjects(_settings._jobs, threadHandles, TRUE, INFINITE);
	if (waitResult != WAIT_OBJECT_0) {
		if (waitResult == WAIT_FAILED) {
			std::cerr << "#### .\nTscThreadExecutor::check wait failed, result: " << waitResult << " error: " << GetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			std::cerr << "#### .\nTscThreadExecutor::check wait failed, result: " << waitResult << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	unsigned int result = 0;
	for (unsigned int i = 0; i < _settings._jobs; ++i) {
		DWORD exitCode;

		if (!GetExitCodeThread(threadHandles[i], &exitCode)) {
			std::cerr << "#### .\nTscThreadExecutor::check get exit code failed, error:" << GetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}

		result += exitCode;

		if (!CloseHandle(threadHandles[i])) {
			std::cerr << "#### .\nTscThreadExecutor::check close handle failed, error:" << GetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

#else

	for (unsigned int i = 0; i < _settings._jobs; ++i) {
		int ret = pthread_create(&threadHandles[i], nullptr, threadProc, this);
		if (ret) {
			std::cerr << "#### .\nTscThreadExecutor::check error, errno :" << ret << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	unsigned int result = 0;
	void* tret = nullptr;
	for (int i = 0; i < _settings._jobs; ++i) {
		int ret = pthread_join(threadHandles[i], &tret);
		if (ret) {
			std::cerr << "#### .\nTscThreadExecutor::check get exit code failed, error:" << ret << std::endl;
			exit(EXIT_FAILURE);
		}
		result += (unsigned int)(intptr_t)(tret);
	}
#endif

	TSC_LOCK_DELETE(&_fileSync);
	TSC_LOCK_DELETE(&_errorSync);
	TSC_LOCK_DELETE(&_reportSync);

	delete[] threadHandles;

	return result;
}