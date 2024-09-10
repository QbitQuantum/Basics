static void gtaThreadProc(void*)
{
	Netlib_Logf(NULL, "GTA thread start");

	SHORTDATA data = { 0 };

	while (!MirandaExiting()) {
		Sync(CLUI_SyncGetShortData, (WPARAM)pcli->hwndContactTree, (LPARAM)&data);
		while (true) {
			if (MirandaExiting())
				goto LBL_Exit;

			SleepEx(0, TRUE); //1000 contacts per second

			GTACHAINITEM mpChain = { 0 };
			SHORTDATA dat2 = { 0 };
			if (!gtaGetItem(&mpChain))
				break;

			SHORTDATA *dat;
			if (mpChain.dat == NULL || (!IsBadReadPtr(mpChain.dat, sizeof(*mpChain.dat)) && mpChain.dat->hWnd == data.hWnd))
				dat = &data;
			else {
				Sync(CLUI_SyncGetShortData, (WPARAM)mpChain.dat->hWnd, (LPARAM)&dat2);
				dat = &dat2;
			}
			if (MirandaExiting())
				goto LBL_Exit;

			ClcCacheEntry cacheEntry;
			memset(&cacheEntry, 0, sizeof(cacheEntry));
			cacheEntry.hContact = mpChain.hContact;
			if (!Sync(CLUI_SyncGetPDNCE, (WPARAM)0, (LPARAM)&cacheEntry)) {
				Cache_GetSecondLineText(dat, &cacheEntry);
				Cache_GetThirdLineText(dat, &cacheEntry);
				Sync(CLUI_SyncSetPDNCE, (WPARAM)CCI_LINES, (LPARAM)&cacheEntry);
				CListSettings_FreeCacheItemData(&cacheEntry);
			}

			KillTimer(dat->hWnd, TIMERID_INVALIDATE_FULL);
			CLUI_SafeSetTimer(dat->hWnd, TIMERID_INVALIDATE_FULL, 500, NULL);
		}

		WaitForSingleObjectEx(hgtaWakeupEvent, INFINITE, TRUE);
		ResetEvent(hgtaWakeupEvent);
	}

LBL_Exit:
	CloseHandle(hgtaWakeupEvent);
	hgtaWakeupEvent = NULL;
	g_hGetTextAsyncThread = NULL;
	Netlib_Logf(NULL, "GTA thread end");
}