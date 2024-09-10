static DWORD WINAPI TestSynchCritical_Main(LPVOID arg)
{
	int i, j;
	SYSTEM_INFO sysinfo;
	DWORD dwPreviousSpinCount;
	DWORD dwSpinCount;
	DWORD dwSpinCountExpected;
	HANDLE hMainThread;
	HANDLE* hThreads;
	HANDLE hThread;
	DWORD dwThreadCount;
	DWORD dwThreadExitCode;
	BOOL bTest1Running;

	PBOOL pbThreadTerminated = (PBOOL)arg;

	GetNativeSystemInfo(&sysinfo);

	hMainThread = (HANDLE) (ULONG_PTR) GetCurrentThreadId();

	/**
	 * Test SpinCount in SetCriticalSectionSpinCount, InitializeCriticalSectionEx and InitializeCriticalSectionAndSpinCount
	 * SpinCount must be forced to be zero on on uniprocessor systems and on systems
	 * where WINPR_CRITICAL_SECTION_DISABLE_SPINCOUNT is defined
	 */

	dwSpinCount = 100;
	InitializeCriticalSectionEx(&critical, dwSpinCount, 0);
	while(--dwSpinCount)
	{
		dwPreviousSpinCount = SetCriticalSectionSpinCount(&critical, dwSpinCount);
		dwSpinCountExpected = 0;
#if !defined(WINPR_CRITICAL_SECTION_DISABLE_SPINCOUNT)
		if (sysinfo.dwNumberOfProcessors > 1)
			dwSpinCountExpected = dwSpinCount+1;
#endif
		if (dwPreviousSpinCount != dwSpinCountExpected)
		{
			printf("CriticalSection failure: SetCriticalSectionSpinCount returned %"PRIu32" (expected: %"PRIu32")\n", dwPreviousSpinCount, dwSpinCountExpected);
			goto fail;
		}

		DeleteCriticalSection(&critical);

		if (dwSpinCount%2==0)
			InitializeCriticalSectionAndSpinCount(&critical, dwSpinCount);
		else
			InitializeCriticalSectionEx(&critical, dwSpinCount, 0);
	}
	DeleteCriticalSection(&critical);


	/**
	 * Test single-threaded recursive TryEnterCriticalSection/EnterCriticalSection/LeaveCriticalSection
	 *
	 */

	InitializeCriticalSection(&critical);

	for (i = 0; i < 1000; i++)
	{
		if (critical.RecursionCount != i)
		{
			printf("CriticalSection failure: RecursionCount field is %"PRId32" instead of %d.\n", critical.RecursionCount, i);
			goto fail;
		}
		if (i%2==0)
		{
			EnterCriticalSection(&critical);
		}
		else
		{
			if (TryEnterCriticalSection(&critical) == FALSE)
			{
				printf("CriticalSection failure: TryEnterCriticalSection failed where it should not.\n");
				goto fail;
			}
		}
		if (critical.OwningThread != hMainThread)
		{
			printf("CriticalSection failure: Could not verify section ownership (loop index=%d).\n", i);
			goto fail;
		}
	}
	while (--i >= 0)
	{
		LeaveCriticalSection(&critical);
		if (critical.RecursionCount != i)
		{
			printf("CriticalSection failure: RecursionCount field is %"PRId32" instead of %d.\n", critical.RecursionCount, i);
			goto fail;
		}
		if (critical.OwningThread != (HANDLE)(i ? hMainThread : NULL))
		{
			printf("CriticalSection failure: Could not verify section ownership (loop index=%d).\n", i);
			goto fail;
		}
	}
	DeleteCriticalSection(&critical);


	/**
	 * Test using multiple threads modifying the same value
	 */

	dwThreadCount = sysinfo.dwNumberOfProcessors > 1 ? sysinfo.dwNumberOfProcessors : 2;

	hThreads = (HANDLE*) calloc(dwThreadCount, sizeof(HANDLE));
	if (!hThreads)
	{
		printf("Problem allocating memory\n");
		goto fail;
	}

	for (j = 0; j < TEST_SYNC_CRITICAL_TEST1_RUNS; j++)
	{
		dwSpinCount = j * 1000;
		InitializeCriticalSectionAndSpinCount(&critical, dwSpinCount);

		gTestValueVulnerable = 0;
		gTestValueSerialized = 0;

		/* the TestSynchCritical_Test1 threads shall run until bTest1Running is FALSE */
		bTest1Running = TRUE;
		for (i = 0; i < (int) dwThreadCount; i++)
		{
			if (!(hThreads[i] = CreateThread(NULL, 0, TestSynchCritical_Test1, &bTest1Running, 0, NULL)))
			{
				printf("CriticalSection failure: Failed to create test_1 thread #%d\n", i);
				goto fail;
			}
		}

		/* let it run for TEST_SYNC_CRITICAL_TEST1_RUNTIME_MS ... */
		Sleep(TEST_SYNC_CRITICAL_TEST1_RUNTIME_MS);
		bTest1Running = FALSE;

		for (i = 0; i < (int) dwThreadCount; i++)
		{
			if (WaitForSingleObject(hThreads[i], INFINITE) != WAIT_OBJECT_0)
			{
				printf("CriticalSection failure: Failed to wait for thread #%d\n", i);
				goto fail;
			}
			GetExitCodeThread(hThreads[i], &dwThreadExitCode);
			if(dwThreadExitCode != 0)
			{
				printf("CriticalSection failure: Thread #%d returned error code %"PRIu32"\n", i, dwThreadExitCode);
				goto fail;
			}
			CloseHandle(hThreads[i]);
		}

		if (gTestValueVulnerable != gTestValueSerialized)
		{
			printf("CriticalSection failure: unexpected test value %"PRId32" (expected %"PRId32")\n", gTestValueVulnerable, gTestValueSerialized);
			goto fail;
		}

		DeleteCriticalSection(&critical);
	}

	free(hThreads);


	/**
	 * TryEnterCriticalSection in thread must fail if we hold the lock in the main thread
	 */

	InitializeCriticalSection(&critical);

	if (TryEnterCriticalSection(&critical) == FALSE)
	{
		printf("CriticalSection failure: TryEnterCriticalSection unexpectedly failed.\n");
		goto fail;
	}
	/* This thread tries to call TryEnterCriticalSection which must fail */
	if (!(hThread = CreateThread(NULL, 0,  TestSynchCritical_Test2, NULL, 0, NULL)))
	{
		printf("CriticalSection failure: Failed to create test_2 thread\n");
		goto fail;
	}
	if (WaitForSingleObject(hThread, INFINITE) != WAIT_OBJECT_0)
	{
		printf("CriticalSection failure: Failed to wait for thread\n");
		goto fail;
	}
	GetExitCodeThread(hThread, &dwThreadExitCode);
	if(dwThreadExitCode != 0)
	{
		printf("CriticalSection failure: Thread returned error code %"PRIu32"\n", dwThreadExitCode);
		goto fail;
	}
	CloseHandle(hThread);

	*pbThreadTerminated = TRUE; /* requ. for winpr issue, see below */
	return 0;

fail:
	*pbThreadTerminated = TRUE; /* requ. for winpr issue, see below */
	return 1;
}