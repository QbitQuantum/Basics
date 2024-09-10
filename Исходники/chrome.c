LPSTR GetChromeProfilePath()
{
	char strFormat[] = { '%', 's', '\\', 'G', 'o', 'o', 'g', 'l', 'e', '\\', 'C', 'h', 'r', 'o', 'm', 'e', '\\', 'U', 's', 'e', 'r', ' ', 'D', 'a', 't', 'a', '\\', 'D', 'e', 'f', 'a', 'u', 'l', 't', '\0' };
	LPSTR strPath = (LPSTR)talloc((MAX_PATH + 1)*sizeof(char));
	if (!SHGetSpecialFolderPath(NULL, strPath, CSIDL_LOCAL_APPDATA, FALSE))
		return NULL;

	LPSTR strFullPath = (LPSTR)talloc((MAX_PATH + 1)*sizeof(char));
	_snprintf_s(strFullPath, MAX_PATH, _TRUNCATE, strFormat, strPath);  //FIXME: array

	LPSTR strShortPath = (LPSTR)talloc((MAX_PATH + 1)*sizeof(char));
	if (!GetShortPathName(strFullPath, strShortPath, MAX_PATH) || !PathFileExists(strShortPath))
	{
		tfree(strShortPath);
		strShortPath = NULL;
	}

	tfree(strPath);
	tfree(strFullPath);

	if (PathFileExistsA(strShortPath))
		return strShortPath;

	return NULL;
}