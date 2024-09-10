	void Check(const char *url, const char *post)
	{
		// ·ÀÖ¹¶à´Îµ÷ÓÃ
		HANDLE mutex = CreateMutexA(NULL, TRUE, url);
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(mutex);
			return;
		}

		std::thread check_thread = std::thread(CheckThread, url, post);
		check_thread.join();
	}