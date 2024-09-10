extern "C" int __declspec(dllexport) Unload(void)
{
	UninitIdleTimer();

	if (g_hWinHook != 0)
		UnhookWinEvent(g_hWinHook);

	DestroyServiceFunction(g_hHideService);

	if (g_hListenWindow)
	{
		WTSUnRegisterSessionNotification(g_hListenWindow);
		DestroyWindow(g_hListenWindow);
	}

	if (hDwmApi)
		FreeLibrary(hDwmApi);

	// free all sessions
	HWND_ITEM *pTemp = g_pMirWnds;
	while (pTemp != NULL)
	{
		HWND_ITEM *pNext = pTemp->next;
		delete pTemp;
		pTemp = pNext;
	}

	delete[] oldStatus;
	delete[] oldStatusMsg;

	return 0;
}