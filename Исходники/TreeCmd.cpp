	int walktree(const wchar_t * directory,const wchar_t * command) {
		std::wstring dir = directory;
		dir += L"\\*";
		std::wstring cmd = command ? command : L"";
		WIN32_FIND_DATAW findData;
		
		HANDLE hFile = FindFirstFile(dir.c_str(), &findData);
		if  (hFile != INVALID_HANDLE_VALUE) {
			std::wstring current = getCurrent();
			SetCurrentDirectoryW(directory);

			do {
				std::wstring fname = findData.cFileName;
				if (fname == L".." || fname == L".")
					continue;
				if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					std::wstring walk = fname;
					walktree(walk.c_str(), command);
				}
				else {
					// TODO implement replacement strategy %N filename without extension %E extension %F complete file name %P path
					if (cmd.empty()) {
						wprintf(L"%s\n", fname.c_str());
					}
					else {
						std::wstring com = cmd + L" " + fname;
						wchar_t*buffer = new wchar_t[com.length() + 1];
						wsprintf(buffer, L"%s", com.c_str());
						_wsystem(buffer);
					}
				}
			} while (FindNextFileW(hFile, &findData));
			FindClose(hFile);
			SetCurrentDirectoryW(current.c_str());
		}
		
		return 0;
	}