char*
mktempdir(void)
{
	WinRune buf[1024];
	WinRune tmp[MAX_PATH];
	WinRune golink[] = {'g', 'o', 'l', 'i', 'n', 'k', '\0'};
	int n;
	
	n = GetTempPathW(nelem(buf), buf);
	if(n <= 0)
		return nil;
	buf[n] = '\0';
	
	if(GetTempFileNameW(buf, golink, 0, tmp) == 0)
		return nil;
	DeleteFileW(tmp);
	if(!CreateDirectoryW(tmp, nil))
		return nil;
	
	return toutf(tmp);
}