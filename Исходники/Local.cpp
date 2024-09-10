	std::string local::savedgamesdir(std::string name) {
#if defined(_WIN32)
		char szPath[MAX_PATH];
		auto result = SHGetFolderPathA(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE,
		                               NULL, 0, szPath);
		if(FAILED(result)) {
			debugmanager()->fatal("CSIDL_PERSONAL: failed to retrieve path");
		}
		PathAppendA(szPath, "My Games");
		PathAppendA(szPath, name.data());
		return std::string(szPath);
#elif defined(__linux__)
		struct passwd *pwd = getpwuid(getuid());
		return std::string(pwd->pw_dir) + "/mygames/" + name;
#elif defined(__APPLE__)
		struct passwd *pwd = getpwuid(getuid());
		return std::string(pwd->pw_dir) + "/Documents/My Games/" + name;
#else
		debugmanager()->fatal(
		    "polar::fs::local::savedgamesdir: not implemented");
		return "";
#endif
	}