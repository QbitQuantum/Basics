void KillWatcherThread (HWND hDlg)
{
	LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
	TerminateThread(info.fileWatcherThread, 0);
	info.fileWatcherThread = NULL;
}