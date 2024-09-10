	void RemoveFile(const tWString& asFilePath)
	{
	#ifdef WIN32
		_wremove(asFilePath.c_str());
	#else
		remove(cString::To8Char(asFilePath).c_str());
	#endif
	}