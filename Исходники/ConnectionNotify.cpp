extern "C" int __declspec(dllexport) Unload(void)
{
	WaitForSingleObjectEx(hConnectionCheckThread, INFINITE, FALSE);
        if (hConnectionCheckThread )CloseHandle(hConnectionCheckThread);
	if (hCheckEvent)DestroyHookableEvent(hCheckEvent);
	if (hOptInit) UnhookEvent(hOptInit);
	if (hCheckHook)UnhookEvent(hCheckHook);
	if (hHookModulesLoaded)UnhookEvent(hHookModulesLoaded);
	if (hHookPreShutdown)UnhookEvent(hHookPreShutdown);
	if (killCheckThreadEvent)
		CloseHandle(killCheckThreadEvent);
	//if (hCurrentEditMutex) CloseHandle(hCurrentEditMutex);
	if (hExceptionsMutex) CloseHandle(hExceptionsMutex);

#ifdef _DEBUG
	_OutputDebugString(_T("Unloaded"));
#endif
	return 0;
}