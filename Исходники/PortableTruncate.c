int truncate(const char *path, long length)
{
    HANDLE file = CreateFile(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
    				FILE_SHARE_WRITE | FILE_SHARE_READ, NULL);
	
    if (file == INVALID_HANDLE_VALUE)
    {
		return -1;
    }
	
    if (SetFilePointer(file, length, NULL, FILE_BEGIN) == 0xFFFFFFFF || !SetEndOfFile(file))
    {
		CloseHandle(file);
		return -1;
    }
	
    CloseHandle(file);
    return 0;
}