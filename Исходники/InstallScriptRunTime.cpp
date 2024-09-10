	gcString GetWildcardPath(gcString wildcard)
	{
#ifdef WIN32
		if (Safe::stricmp("PROGRAM_FILES", wildcard.c_str()) == 0)
		{
			wchar_t path[MAX_PATH]  = {0};
			SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, path);
			return path;
		}
		else if (Safe::stricmp("DOCUMENTS", wildcard.c_str()) == 0)
		{
			return GetSpecialPath(1);
		}
		else if (Safe::stricmp("JAVA_PATH", wildcard.c_str()) == 0)
		{
			std::string cur = UTIL::WIN::getRegValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment\\CurrentVersion");

			if (cur.size() > 0)
				return UTIL::WIN::getRegValue(gcString("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment\\{0}\\JavaHome", cur));
		}
		else if (Safe::stricmp("APP_DATA", wildcard.c_str())==0)
		{
			wchar_t path[MAX_PATH]  = {0};
			SHGetFolderPathW(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, path);
			return path;
		}
		else if (Safe::stricmp("USER_APP_DATA", wildcard.c_str())==0)
		{
			return GetSpecialPath(2);
		}
#endif
		return "";
	}