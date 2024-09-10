static	geBoolean	GENESISCC FSDos_SetTime(void *Handle, const geVFile_Time *Time)
{
	DosFile *	File;
	FILETIME	Win32Time;

	File = Handle;

	CHECK_HANDLE(File);

	assert(File->FileHandle != INVALID_HANDLE_VALUE);

	Win32Time.dwLowDateTime  = Time->Time1;
	Win32Time.dwHighDateTime = Time->Time2;
	if	(SetFileTime(File->FileHandle, &Win32Time, &Win32Time, &Win32Time) == FALSE)
		return GE_FALSE;

	return GE_TRUE;
}