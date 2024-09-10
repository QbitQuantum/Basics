int _mkdir(const char* dir)
{
	static wchar_t wdir[MAX_PATH];
	BOOL rc;
//	wchar_t* wdir = wce_AToW(dir);
	wce_AToW2(dir, wdir);

	rc = CreateDirectoryW(wdir, NULL);

	return rc==0 ? -1 : 0 ;
}