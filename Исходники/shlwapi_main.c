/*************************************************************************
 * SHLWAPI LibMain
 *
 * NOTES
 *  calling oleinitialize here breaks sone apps.
 */
BOOL WINAPI SHLWAPI_LibMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID fImpLoad)
{
	TRACE("0x%x 0x%lx %p\n", hinstDLL, fdwReason, fImpLoad);
	switch (fdwReason)
	{
	  case DLL_PROCESS_ATTACH:
	    shlwapi_hInstance = hinstDLL;
	    SHLWAPI_ThreadRef_index = TlsAlloc();
	    break;
	  case DLL_PROCESS_DETACH:
	    if (SHLWAPI_hshell32)  FreeLibrary(SHLWAPI_hshell32);
	    if (SHLWAPI_hwinmm)    FreeLibrary(SHLWAPI_hwinmm);
	    if (SHLWAPI_hcomdlg32) FreeLibrary(SHLWAPI_hcomdlg32);
	    if (SHLWAPI_hmpr)      FreeLibrary(SHLWAPI_hmpr);
	    if (SHLWAPI_hmlang)    FreeLibrary(SHLWAPI_hmlang);
	    if (SHLWAPI_hversion)  FreeLibrary(SHLWAPI_hversion);
	    if (SHLWAPI_ThreadRef_index >= 0) TlsFree(SHLWAPI_ThreadRef_index);
	    break;
	}
	return TRUE;
}