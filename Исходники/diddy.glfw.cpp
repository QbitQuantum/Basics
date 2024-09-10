	static String savefilename() {
		#ifdef _WIN32
		char *filter = "All Files (*.*)\0*.*\0";
		HWND owner = NULL;
		OPENFILENAME ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";

		String fileNameStr;

		if ( GetSaveFileNameA(&ofn) )
			fileNameStr = fileName;

		return fileNameStr;
		#endif
		#ifdef linux
		return "";
		#endif
	}