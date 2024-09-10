bool FileStdStream::Open(uint32 nAccess, String::EFormat nStringFormat)
{
	// If a standard stream has been used, we cannot open/reopen it
	if (m_bStream)
		return false;

	// Close file
	Close();

	// Set file mode
	char szMode[4];
	if ((nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && (nAccess & File::FileAppend)) {
		// Append at the end of the file
		if (nAccess & File::FileRead)
			strcpy(szMode, "a+");	// Append, read and write
		else
			strcpy(szMode, "a");	// Append, write only
	} else if ((nAccess & File::FileWrite) && (nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Create and open writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "w+");	// Create, read and write
		else
			strcpy(szMode, "w");	// Create, write only
	} else if ((nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Open writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "r+");	// Open, read and write

		// We need to check whether the file already exist, if so, we can go on...
		else {
			if (Exists())
				strcpy(szMode, "w");	// Open, write only
			else
				return false;			// Invalid
		}
	} else if (!(nAccess & File::FileWrite) && !(nAccess & File::FileCreate) && !(nAccess & File::FileAppend)) {
		// Open not writable
		if (nAccess & File::FileRead)
			strcpy(szMode, "r");	// Open, read only
		else
			return false;			// Invalid
	} else {
		// Invalid combination
		return false;
	}

	// Set text or binary mode
	strcat(szMode, (nAccess & File::FileText) ? "t" : "b");

	// Save access modes and string encoding format
	m_nAccess       = nAccess;
	m_nStringFormat = nStringFormat;

	// Get OS file handle and open file
	#if defined(WIN32)
		const int nFile = _open_osfhandle(m_hFile, 0);
		if (nFile > -1) {
			// ASCII or Unicode?
			if (nStringFormat == String::ASCII) {
				// ASCII
				m_pFile = _fdopen(nFile, szMode);
			} else {
				// Unicode
				const wchar_t szModeUnicode[4] = {szMode[0], szMode[1], szMode[2], szMode[3]};
				m_pFile = _wfdopen(nFile, szModeUnicode);
			}
		}
	#elif defined(LINUX)
		// [TODO] Support for "nStringFormat"-parameter?
		if (m_hFile > -1)
			m_pFile = _fdopen(m_hFile, szMode);
	#endif

	// Done
	return (m_pFile != nullptr);
}