bool CheckLdrNotificationAvailable()
{
	static bool bLdrWasChecked = false;
	if (bLdrWasChecked)
		return gbLdrDllNotificationUsed;

	#ifndef _WIN32_WINNT_WIN8
	#define _WIN32_WINNT_WIN8 0x602
	#endif
	_ASSERTE(_WIN32_WINNT_WIN8==0x602);
	OSVERSIONINFOEXW osvi = {sizeof(osvi), HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8)};
	DWORDLONG const dwlConditionMask = VerSetConditionMask(VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL);
	BOOL isAllowed = VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);

	// LdrDllNotification работает так как нам надо начиная с Windows 8
	// В предыдущих версиях Windows нотификатор вызывается из LdrpFindOrMapDll
	// ДО того, как были обработаны импорты функцией LdrpProcessStaticImports (а точнее LdrpSnapThunk)

	if (isAllowed)
	{
		HMODULE hNtDll = GetModuleHandle(L"ntdll.dll");
		if (hNtDll)
		{
			LdrRegisterDllNotification = (LdrRegisterDllNotification_t)GetProcAddress(hNtDll, "LdrRegisterDllNotification");
			LdrUnregisterDllNotification = (LdrUnregisterDllNotification_t)GetProcAddress(hNtDll, "LdrUnregisterDllNotification");

			if (LdrRegisterDllNotification && LdrUnregisterDllNotification)
			{
				gnLdrDllNotificationState = LdrRegisterDllNotification(0, LdrDllNotification, NULL, &gpLdrDllNotificationCookie);
				gbLdrDllNotificationUsed = (gnLdrDllNotificationState == 0/*STATUS_SUCCESS*/);
			}
		}
	}

	bLdrWasChecked = true;

	return gbLdrDllNotificationUsed;
}