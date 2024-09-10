BOOL TInifile::Lock()
{
	if (!hMutex) {
		char	buf[1024];
		char	*key = (char *)_mbsrchr((u_char *)ini_file, '\\');

		key = key ? key+1 : ini_file;

		sprintf(buf, "%s_%x", key, MakeHash(ini_file, (int)strlen(ini_file), 0));

		if (!(hMutex = ::CreateMutex(NULL, FALSE, buf))) return FALSE;
	}

	return	::WaitForSingleObject(hMutex, INFINITE);
}