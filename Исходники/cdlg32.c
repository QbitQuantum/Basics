BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD Reason, LPVOID Reserved)
{
	TRACE("(%p, %d, %p)\n", hInstance, Reason, Reserved);

	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		COMDLG32_hInstance = hInstance;
		DisableThreadLibraryCalls(hInstance);

		SHELL32_hInstance = GetModuleHandleA("SHELL32.DLL");

		/* ITEMIDLIST */
		GPA(COMDLG32_PIDL_ILIsEqual, SHELL32_hInstance, (LPCSTR)21L);
		GPA(COMDLG32_PIDL_ILCombine, SHELL32_hInstance, (LPCSTR)25L);
		GPA(COMDLG32_PIDL_ILGetNext, SHELL32_hInstance, (LPCSTR)153L);
		GPA(COMDLG32_PIDL_ILClone, SHELL32_hInstance, (LPCSTR)18L);
		GPA(COMDLG32_PIDL_ILRemoveLastID, SHELL32_hInstance, (LPCSTR)17L);
		GPA(COMDLG32_PIDL_ILGetSize, SHELL32_hInstance, (LPCSTR)152L);

		/* SHELL */
		GPA(COMDLG32_SHSimpleIDListFromPathAW, SHELL32_hInstance, (LPCSTR)162);
		GPA(COMDLG32_SHAlloc, SHELL32_hInstance, (LPCSTR)196L);
		GPA(COMDLG32_SHFree, SHELL32_hInstance, (LPCSTR)195L);

		/* for the first versions of shell32 SHGetFolderPathW is in SHFOLDER.DLL */
		COMDLG32_SHGetFolderPathW = (void*)GetProcAddress(SHELL32_hInstance,"SHGetFolderPathW");
		if (!COMDLG32_SHGetFolderPathW)
		{
		  SHFOLDER_hInstance = LoadLibraryA("SHFOLDER.DLL");
		  GPA(COMDLG32_SHGetFolderPathW, SHFOLDER_hInstance,"SHGetFolderPathW");
		}

		break;

	case DLL_PROCESS_DETACH:
            if (Reserved) break;
            if (COMDLG32_TlsIndex != TLS_OUT_OF_INDEXES) TlsFree(COMDLG32_TlsIndex);
            if(SHFOLDER_hInstance) FreeLibrary(SHFOLDER_hInstance);
            break;
	}
	return TRUE;
}