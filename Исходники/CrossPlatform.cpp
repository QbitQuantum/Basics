/**
 * Builds a list of predefined paths for the User folder
 * according to the running system.
 * @return List of data paths.
 */
std::vector<std::string> findUserFolders()
{
	std::vector<std::string> list;
#ifdef _WIN32
	char path[MAX_PATH];

	// Get Documents folder
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, path)))
	{
		PathAppendA(path, "OpenXcom\\");
		list.push_back(path);
	}

	// Get binary directory
	if (GetModuleFileNameA(NULL, path, MAX_PATH) != 0)
	{
		PathRemoveFileSpecA(path);
		PathAppendA(path, "user\\");
		list.push_back(path);
	}

	// Get working directory
	if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
	{
		PathAppendA(path, "user\\");
		list.push_back(path);
	}
#else
#ifdef __HAIKU__
	list.push_back("/boot/apps/OpenXcom/");
#endif
	char const *home = getHome();
	char path[MAXPATHLEN];
	
	// Get user folders
	if (char const *const xdg_data_home = getenv("XDG_DATA_HOME"))
 	{
		snprintf(path, MAXPATHLEN, "%s/openxcom/", xdg_data_home);
 	}
 	else
 	{
#ifdef __APPLE__
		snprintf(path, MAXPATHLEN, "%s/Library/Application Support/OpenXcom/", home);
#else
		snprintf(path, MAXPATHLEN, "%s/.local/share/openxcom/", home);
#endif
 	}
	list.push_back(path);

	// Get old-style folder
	snprintf(path, MAXPATHLEN, "%s/.openxcom/", home);
	list.push_back(path);

	// Get working directory
	list.push_back("./user/");
#endif

	return list;
}