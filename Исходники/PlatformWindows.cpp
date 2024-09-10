	Path getUserDataPath()
	{
	  Path result;
	  char l_path[MAX_PATH];

	  if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, l_path)))
	  {
	    result = reinterpret_cast<char*>(l_path);
	  }
	  return result;
	}