static void detect_msys_tty(int fd)
{
	ULONG result;
	BYTE buffer[1024];
	POBJECT_NAME_INFORMATION nameinfo = (POBJECT_NAME_INFORMATION) buffer;
	PWSTR name;

	/* check if fd is a pipe */
	HANDLE h = (HANDLE) _get_osfhandle(fd);
	if (GetFileType(h) != FILE_TYPE_PIPE)
		return;

	/* get pipe name */
	if (!NT_SUCCESS(NtQueryObject(h, ObjectNameInformation,
			buffer, sizeof(buffer) - 2, &result)))
		return;
	name = nameinfo->Name.Buffer;
	name[nameinfo->Name.Length / sizeof(*name)] = 0;

	/*
	 * Check if this could be a MSYS2 pty pipe ('msys-XXXX-ptyN-XX')
	 * or a cygwin pty pipe ('cygwin-XXXX-ptyN-XX')
	 */
	if ((!wcsstr(name, L"msys-") && !wcsstr(name, L"cygwin-")) ||
			!wcsstr(name, L"-pty"))
		return;

	if (fd == 2)
		setvbuf(stderr, NULL, _IONBF, BUFSIZ);
	fd_is_interactive[fd] |= FD_MSYS;
}