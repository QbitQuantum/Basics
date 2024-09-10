HHOOK UserImp::setWindowsHookExW(int idHook, HOOKPROC lpfn, HINSTANCE hMod, DWORD dwThreadId)
{
	if (!bUserLoaded && !loadExports(bAllowLoadLibrary))
	{
		_ASSERTEX(hUser32!=NULL);
		return NULL;
	}
	
	HHOOK hRc = SetWindowsHookExW(idHook, lpfn, hMod, dwThreadId);
	/*
	if (setWindowsHookExW_f)
	{
		hRc = setWindowsHookExW_f(idHook, lpfn, hMod, dwThreadId);
	}
	else
	{
		_ASSERTEX(setWindowsHookExW_f!=NULL);
	}
	*/
	return hRc;
}