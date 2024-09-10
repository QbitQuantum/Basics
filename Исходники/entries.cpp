BOOL Entry::launch_entry(HWND hwnd, UINT nCmdShow)
{
	TCHAR cmd[MAX_PATH];

	if (!get_path(cmd, COUNTOF(cmd)))
		return FALSE;

	 // add path to the recent file list
	SHAddToRecentDocs(SHARD_PATH, cmd);

	  // start program, open document...
	return launch_file(hwnd, cmd, nCmdShow);
}