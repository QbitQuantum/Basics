VOID DumpFile(HWND hwndDlg)
{
	OPENFILENAMEA ofn;
	char DumpFileName[MAX_PATH];
	
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = "Executable files\0*.exe\0\0";
	ofn.lpstrFile = DumpFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.hwndOwner = hwndDlg;
	strcpy_s(DumpFileName, MAX_PATH, "dumped.exe");
	if (GetSaveFileNameA(&ofn))
	{
		//::memset(&text, 0, 1024);
		//GetDlgItemTextA(hDlg, IDC_OEPRVA, (LPSTR)&text, 8);
		//::DumpAndFixOep(g_pid, htodw((LPSTR)&text), dumpFileName);
		//::SetDlgItemTextA(hDlg, IDC_STATUS, "Dumping done...");
		DumpPE64(dwPid, DumpFileName);
	}
}