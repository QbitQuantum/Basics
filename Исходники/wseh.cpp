EXTERN_C int wseh_EntryPoint()
{
#ifdef NEED_COOKIE_INIT
	// 2006-02-16 workaround for R6035 on VC8:
	//
	// SEH code compiled with /GS pushes a "security cookie" onto the
	// stack. since we're called before CRT init, the cookie won't have
	// been initialized yet, which would cause the CRT to FatalAppExit.
	// to solve this, we must call __security_init_cookie before any
	// hidden compiler-generated SEH registration code runs,
	// which means the __try block must be moved into a helper function.
	//
	// NB: wseh_EntryPoint() must not contain local string buffers,
	// either - /GS would install a cookie here as well (same problem).
	//
	// see http://msdn2.microsoft.com/en-US/library/ms235603.aspx
	__security_init_cookie();
#endif
	return CallStartupWithinTryBlock();
}