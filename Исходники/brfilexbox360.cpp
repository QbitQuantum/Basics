Word Burger::File::SetCreationTime(const TimeDate_t *pInput)
{
	Word uResult = FILENOTFOUND;
	HANDLE fp = m_pFile;
	if (fp) {
		FILETIME CreationTime;
		pInput->Store(&CreationTime);
		// Set the file creation time
		BOOL bFileInfoResult = SetFileTime(fp,&CreationTime,NULL,NULL);
		if (bFileInfoResult) {
			uResult = OKAY;
		}
	}
	return uResult;
}