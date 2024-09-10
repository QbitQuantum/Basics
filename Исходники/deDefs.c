void deAssertFail (const char* reason, const char* file, int line)
{
#if defined(DE_ASSERT_FAILURE_CALLBACK)
	if (g_assertFailureCallback != DE_NULL)
	{
		/* Remove callback in case of the callback causes further asserts. */
		deAssertFailureCallbackFunc callback = g_assertFailureCallback;
		deSetAssertFailureCallback(DE_NULL);
		callback(reason, file, line);
	}
#endif

#if (((DE_OS == DE_OS_WIN32) || (DE_OS == DE_OS_WINCE)) && (DE_COMPILER == DE_COMPILER_MSC))
	{
		wchar_t	wreason[1024];
		wchar_t	wfile[128];
		int		num;
		int		i;

	/*	MessageBox(reason, "Assertion failed", MB_OK); */

		num = deMin32((int)strlen(reason), DE_LENGTH_OF_ARRAY(wreason)-1);
		for (i = 0; i < num; i++)
			wreason[i] = reason[i];
		wreason[i] = 0;

		num = deMin32((int)strlen(file), DE_LENGTH_OF_ARRAY(wfile)-1);
		for (i = 0; i < num; i++)
			wfile[i] = file[i];
		wfile[i] = 0;

#	if (DE_OS == DE_OS_WIN32)
		_wassert(wreason, wfile, line);
#	else /* WINCE */
		assert(wreason);
#	endif
	}
#elif ((DE_OS == DE_OS_WIN32) && (DE_COMPILER == DE_COMPILER_CLANG))
	_assert(reason, file, line);
#elif (DE_OS == DE_OS_UNIX)
	__assert_fail(reason, file, (unsigned int)line, "Unknown function");
#elif (DE_OS == DE_OS_SYMBIAN)
	__assert("Unknown function", file, line, reason);
#elif (DE_OS == DE_OS_OSX) || (DE_OS == DE_OS_IOS)
	fprintf(stderr, "Assertion '%s' failed at %s:%d\n", reason, file, line);
	raise(SIGTRAP);
	abort();
#elif (DE_OS == DE_OS_ANDROID)
	__android_log_print(ANDROID_LOG_ERROR, "delibs", "Assertion '%s' failed at %s:%d", reason, file, line);
	__assert(file, line, reason);
#else
#	error Implement assertion function on your platform.
#endif
}