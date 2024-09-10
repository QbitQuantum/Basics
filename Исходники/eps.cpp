BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
{
	switch(fdwReason) {
	case DLL_PROCESS_ATTACH:
		MaxSDK::Util::UseLanguagePackLocale();
		hInstance = hinstDLL;				// Hang on to this DLL's instance handle.
		DisableThreadLibraryCalls(hInstance);
		break;
	case DLL_PROCESS_DETACH:
#ifndef NDEBUG 
		if( hResource )
		{
			// Leak resource DLL: shouldn't call FreeLibrary() from here.
			OutputDebugString(_T("eps/eps.cpp: DllMain(DLL_PROCESS_DETACH) called before LibShutdown()\n"));
		}
#endif
		break;
	}
	return(TRUE);
}