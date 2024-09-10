bool ReadFile(String filename, JavaScript::Object options, String& result)
{
	String encoding = TEXT("");
	if (options->HasKey("encoding"))
		options->GetString("encoding");

	// text file
	if (encoding == TEXT("") || encoding == TEXT("utf-8") || encoding == TEXT("text/plain;utf-8"))
	{
		HANDLE hFile = CreateFile(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD numBytesRead = 0;
			LARGE_INTEGER fileSize;
			GetFileSizeEx(hFile, &fileSize);

			// we don't want to read too large files
			_ASSERT(fileSize.HighPart == 0);

			// allocate buffer and read file
			BYTE* data = new BYTE[fileSize.LowPart];
			::ReadFile(hFile, (LPVOID) data, (DWORD) fileSize.LowPart, &numBytesRead, NULL);

			// convert the buffer
			int wcLen = MultiByteToWideChar(CP_UTF8, 0, (LPCCH) data, numBytesRead, NULL, 0);
			TCHAR* buf = new TCHAR[wcLen + 1];
			MultiByteToWideChar(CP_UTF8, 0, (LPCCH) data, numBytesRead, buf, wcLen);
			buf[wcLen] = 0;
			result = String(buf, buf + wcLen);
			delete[] buf;
			delete[] data;
		}

		CloseHandle(hFile);
		return true;
	}

	return false;
}