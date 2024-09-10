/*
	BSD systems provide ftruncate, several others supply chsize, and a few
	may provide a (possibly undocumented) fcntl option F_FREESP. Under MS-DOS,
	you can sometimes use write(fd, "", 0). However, there is no portable
	solution, nor a way to delete blocks at the beginning.
*/
static void MelderFile_truncate (MelderFile me, long size) {
#if defined(_WIN32)

	HANDLE hFile;
	DWORD fdwAccess = GENERIC_READ | GENERIC_WRITE, fPos;
	DWORD fdwShareMode = 0; /* File cannot be shared */
	LPSECURITY_ATTRIBUTES lpsa = NULL;
	DWORD fdwCreate = OPEN_EXISTING;
	LARGE_INTEGER fileSize;

	MelderFile_close (me);

	hFile = CreateFileW (my path, fdwAccess, fdwShareMode, lpsa, fdwCreate,
	                     FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		Melder_throw ("Can't open file ", MelderFile_messageName (me), ".");
	}

	// Set current file pointer to position 'size'

	fileSize.LowPart = size;
	fileSize.HighPart = 0; /* Limit the file size to 2^32 - 2 bytes */
	fPos = SetFilePointer (hFile, fileSize.LowPart, &fileSize.HighPart, FILE_BEGIN);
	if (fPos == 0xFFFFFFFF) {
		Melder_throw ("Can't set the position at size ", size, "for file ", 	MelderFile_messageName (me), ".");
	}

	// Limit the file size as the current position of the file pointer.

	SetEndOfFile (hFile);
	CloseHandle (hFile);

#elif defined(linux) || defined(macintosh)

	MelderFile_close (me);
	if (truncate (Melder_peekWcsToUtf8 (my path), size) == -1) Melder_throw ("Truncating failed for file ",
		        MelderFile_messageName (me), " (", Melder_peekUtf8ToWcs (strerror (errno)), ").");
#else
	Melder_throw ("Don't know what to do.");
#endif
}