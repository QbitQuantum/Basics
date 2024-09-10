BOOL ShellEntry::launch_entry(HWND hwnd, UINT nCmdShow)
{
	CONTEXT("ShellEntry::launch_entry()");

	SHELLEXECUTEINFO shexinfo;

	shexinfo.cbSize = sizeof(SHELLEXECUTEINFO);
	shexinfo.fMask = SEE_MASK_INVOKEIDLIST;	// SEE_MASK_IDLIST is also possible.
	shexinfo.hwnd = hwnd;
	shexinfo.lpVerb = NULL;
	shexinfo.lpFile = NULL;
	shexinfo.lpParameters = NULL;
	shexinfo.lpDirectory = NULL;
	shexinfo.nShow = nCmdShow;

	ShellPath shell_path = create_absolute_pidl();
	shexinfo.lpIDList = &*shell_path;

	 // add PIDL to the recent file list
	SHAddToRecentDocs(SHARD_PIDL, shexinfo.lpIDList);

	BOOL ret = TRUE;

	if (!ShellExecuteEx(&shexinfo)) {
		display_error(hwnd, GetLastError());
		ret = FALSE;
	}

	return ret;
}