	Yuni::IO::NodeType TypeOf(const AnyString& filename)
	{
		if (filename.empty())
			return Yuni::IO::typeUnknown;

		# ifdef YUNI_OS_WINDOWS
		const char* p = filename.c_str();
		unsigned int len = filename.size();
		if (p[len - 1] == '\\' or p[len - 1] == '/')
		{
			if (!--len)
			{
				# ifdef YUNI_OS_WINDOWS
				return Yuni::IO::typeUnknown;
				# else
				// On Unixes, `/` is a valid folder
				return Yuni::IO::typeFolder;
				# endif
			}
		}

		// Driver letters
		if (len == 2 and p[1] == ':')
			return Yuni::IO::typeFolder;

		String  norm;
		Yuni::IO::Normalize(norm, AnyString(p, len));
		// Conversion into wchar_t
		Private::WString<true> wstr(norm);
		if (wstr.empty())
			return Yuni::IO::typeUnknown;

		WIN32_FILE_ATTRIBUTE_DATA infoFile;
		if (!GetFileAttributesExW(wstr.c_str(), GetFileExInfoStandard, &infoFile))
			return Yuni::IO::typeUnknown;

		return ((infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			? Yuni::IO::typeFolder
			: Yuni::IO::typeFile;

		# else // WINDOWS

		struct stat s;
		if (stat(filename.c_str(), &s) != 0)
			return Yuni::IO::typeUnknown;

		return (S_ISDIR(s.st_mode))
			? Yuni::IO::typeFolder
			: Yuni::IO::typeFile;
		# endif
	}