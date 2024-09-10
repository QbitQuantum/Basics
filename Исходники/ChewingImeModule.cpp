ImeModule::ImeModule(HMODULE module):
	Ime::ImeModule(module, g_textServiceClsid),
	config_(windowsVersion()) {
	
	config_.load(); // load configurations

	// override default location of chewing data directories
	std::wstring env;
	wchar_t path[MAX_PATH];

	HRESULT result;

	// get user profile directory
	if(::GetEnvironmentVariableW(L"USERPROFILE", path, MAX_PATH)) {
		userDir_ = path;
		userDir_ += L"\\ChewingTextService";
		// create the user directory if not exists
		// NOTE: this call will fail in Windows 8 store apps
		// We need a way to create the dir in desktop mode and
		// set proper ACL, so later we can access it inside apps.
		DWORD attributes = ::GetFileAttributesW(userDir_.c_str());
		if(attributes == INVALID_FILE_ATTRIBUTES) {
			// create the directory if it does not exist
			if(::GetLastError() == ERROR_FILE_NOT_FOUND) {
				::CreateDirectoryW(userDir_.c_str(), NULL);
				attributes = ::GetFileAttributesW(userDir_.c_str());
			}
		}

		// make the directory hidden
		if(attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_HIDDEN) == 0)
			::SetFileAttributesW(userDir_.c_str(), attributes|FILE_ATTRIBUTE_HIDDEN);

		env = L"CHEWING_USER_PATH=";
		env += userDir_;
		_wputenv(env.c_str());
	}

	// get the program data directory
	// try C:\program files (x86) first
	result = ::SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILESX86, NULL, 0, path);
	if(result != S_OK) // failed, fall back to C:\program files
		result = ::SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES, NULL, 0, path);
	if(result == S_OK) { // program files folder is found
		programDir_ = path;
		programDir_ += L"\\ChewingTextService";
		env = L"CHEWING_PATH=";
		// prepend user dir path to program path, so user-specific files, if they exist,
		// can take precedence over built-in ones. (for ex: symbols.dat)
		env += userDir_;
		env += ';'; // add ; to separate two dir paths
		// add program dir after user profile dir
		env += programDir_;
		env += L"\\Dictionary";
		_wputenv(env.c_str());
	}

}