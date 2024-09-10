int  _access(const char *sName, int mode)
{
	USES_CONVERSION;
	WIN32_FIND_DATA FindFileData;

        PString test(sName);
        if (test[test.GetLength() - 1] == '.' && test[test.GetLength() - 2] == PDIR_SEPARATOR)
            test.Delete(test.GetLength() - 2, 2);

        HANDLE file = FindFirstFile(A2T((const char*) test), &FindFileData);
	if (file == INVALID_HANDLE_VALUE ) return -1;
	FindClose(file);
	switch(mode)
	{
		//checking for the existance
		case 0: return 0;
		//checking for read permission
		case 4: return 0;
		//checking for write permission
		case 2: return (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_READONLY) ? -1 : 0;
		//checking for read and write permission
		case 6: return (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_READONLY) ? -1 : 0;
	}
	return -1;
}