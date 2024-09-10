/// Try to set std HANDLE from FILE*
static void WINAPI_SetStdHandleFromFile(int type, FILE *file)
{

	int fd;
	HANDLE handle;

	fd = _fileno(file);

	if (fd < 0) {
		return;
	}

	handle = (HANDLE)_get_osfhandle(fd);

	if (! handle || handle == INVALID_HANDLE_VALUE) {
		return;
	}

	SetStdHandle(type, handle);

}