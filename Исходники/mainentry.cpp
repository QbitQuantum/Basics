////////////////////////////////////////////////////////////////////////
// DllMain -- OCX Main Entry
//
//
extern "C" BOOL APIENTRY DllMain(HINSTANCE hDllHandle, DWORD dwReason, LPVOID /*lpReserved*/)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		v_hModule = hDllHandle;
        v_hPrivateHeap = HeapCreate(0, 0x1000, 0);
		v_icoOffDocIcon = (HICON)LoadImage(hDllHandle, MAKEINTRESOURCE(IDI_SMALLOFFDOC), IMAGE_ICON, 16, 16, 0);
		{
			DWORD dwVersion = GetVersion();
			v_fUnicodeAPI = ((dwVersion & 0x80000000) == 0);
			v_fWindows2KPlus = ((v_fUnicodeAPI) && (LOBYTE(LOWORD(dwVersion)) > 4));
		}
		InitializeCriticalSection(&v_csecThreadSynch);
		DisableThreadLibraryCalls(hDllHandle);
		break;

	case DLL_PROCESS_DETACH:
		if (v_icoOffDocIcon) DeleteObject(v_icoOffDocIcon);
        if (v_hPrivateHeap) HeapDestroy(v_hPrivateHeap);
        DeleteCriticalSection(&v_csecThreadSynch);
		break;
	}
	return TRUE;
}