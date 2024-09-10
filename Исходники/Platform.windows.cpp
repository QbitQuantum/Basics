	gs2d::str_type::string GetCurrentDirectoryPath()
	{
		gs2d::str_type::char_t currentDirectoryBuffer[65536];

		#ifdef GS2D_STR_TYPE_WCHAR
		GetCurrentDirectoryW(65535, currentDirectoryBuffer);
		#else
		GetCurrentDirectoryA(65535, currentDirectoryBuffer);
		#endif

		return AddLastSlash(currentDirectoryBuffer);
	}