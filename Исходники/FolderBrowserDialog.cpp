bool FolderBrowserDialog::SetRoot(const wchar_t * str)
{
	bool ret = false;
	wchar_t* tstr = (wchar_t*)LocalAlloc(LPTR, sizeof(wchar_t)*MAX_WPATH);
	if (tstr)
	{
		if (SetBufFromDir(str, tstr, MAX_WPATH))
			if (SHParseDisplayName(tstr, NULL, &root, NULL, NULL) == S_OK)
				ret = true;
		LocalFree(tstr);
	}
	return ret;
}