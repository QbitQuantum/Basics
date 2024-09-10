void DiskFile::SetLastWriteTime(time_t lastWriteTime)
{
#if defined(PLATFORM_WINDOWS)
	FILETIME localFILETIME;
	LONGLONG ll = Int32x32To64(lastWriteTime, 10000000) + 116444736000000000;
	localFILETIME.dwLowDateTime = (DWORD) ll;
	localFILETIME.dwHighDateTime = (DWORD)(ll >>32);
	
	SYSTEMTIME localSystemTime;
	FileTimeToSystemTime(&localFILETIME, &localSystemTime);

	SYSTEMTIME universalSystemTime;
	TzSpecificLocalTimeToSystemTime(NULL, &localSystemTime, &universalSystemTime);

	FILETIME lastWriteTimeFILETIME;
	SystemTimeToFileTime(&localSystemTime, &lastWriteTimeFILETIME);

	if ( !::SetFileTime(m_fileHandle, NULL, NULL, &lastWriteTimeFILETIME) )
		return;
#else
	assert(0);
#endif

}