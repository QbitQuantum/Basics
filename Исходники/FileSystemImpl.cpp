	bool FileSystem::SetFileEditDate(const String& path, const TimeStamp& time) const
	{
		FILETIME lastWriteTime;
		HANDLE hFile = CreateFileA(path.Data(), GENERIC_READ | FILE_WRITE_ATTRIBUTES,
								   FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == NULL)
			return false;

		SYSTEMTIME stLocal, stUTC;

		stLocal.wSecond = time.mSecond;
		stLocal.wDayOfWeek = 0;
		stLocal.wMilliseconds = 0;
		stLocal.wMinute = time.mMinute;
		stLocal.wHour = time.mHour;
		stLocal.wDay = time.mDay;
		stLocal.wMonth = time.mMonth;
		stLocal.wYear = time.mYear;

		TzSpecificLocalTimeToSystemTime(NULL, &stLocal, &stUTC);
		SystemTimeToFileTime(&stUTC, &lastWriteTime);
		if (!SetFileTime(hFile, NULL, NULL, &lastWriteTime))
		{
			auto error = GetLastError();
			printf("err %i\n", error);
			CloseHandle(hFile);
			return false;
		}

		CloseHandle(hFile);

		return true;
	}