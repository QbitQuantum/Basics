	//-----------------------------------------------------------------------
	bool UnicodeFileSystemArchive::isAbsolutePath(const WString& _wFilename) const
	{
		const wchar_t* p = _wFilename.c_str();
		if (iswalpha(p[0]) && p[1] == ':')
			return true;

		return p[0] == '/' || p[0] == '\\';
	}