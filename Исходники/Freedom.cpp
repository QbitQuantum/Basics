void change_firefox_setting() {
	char buf[1024];
	HANDLE hFind;
	WIN32_FIND_DATA data;

	std::wstring inner_dir;
	GetEnvironmentVariableA("APPDATA", buf, sizeof(buf));
	std::string conf_dir = buf;
	conf_dir.append("\\Mozilla\\Firefox\\Profiles\\*.*");
	std::wstring w_conf_dir = std::wstring(conf_dir.begin(), conf_dir.end());
	HANDLE h = FindFirstFile((LPCWSTR)w_conf_dir.c_str(), &data);
	if (h != INVALID_HANDLE_VALUE)
	{
		do
		{
			inner_dir = data.cFileName;
			if (inner_dir.length() > 2) {
				break;
			}

		} while (FindNextFile(h, &data));
	}
	else {
		std::cout << "cannot find firefox config file" << std::endl;
		exit(0);
	}
	w_conf_dir = w_conf_dir.substr(0, w_conf_dir.length() - 3);
	w_conf_dir.append(inner_dir);
	w_conf_dir.append(L"\\prefs.js");

	LPOFSTRUCT lpReOpenBuff;

	HANDLE hFile = CreateFile(w_conf_dir.c_str(),               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // normal file
		NULL);                 // no attr. template

	char   ReadBuffer[20000] = { 0 };
	OVERLAPPED ol = { 0 };
	DWORD  dwBytesRead = 0;

	ReadFileEx(hFile, ReadBuffer, 19999, &ol, FileIOCompletionRoutine);
	CloseHandle(hFile);

	std::string config = ReadBuffer;
	std::vector<std::string> v_configs= tokenize(config, "\r\n");
	std::vector<std::string> v_new_configs;
	bool proxy_setted= false, ip_setted= false, port_setted = false;
	for (int i = 0; i < v_configs.size(); i++) {
		if (std::regex_search(v_configs[i], std::regex("\"network.proxy.type\""))) {
			v_new_configs.push_back("user_pref(\"network.proxy.type\", 1);");
			proxy_setted = true;
		}
		else if (std::regex_search(v_configs[i], std::regex("\"network.proxy.http_port\""))) {
			v_new_configs.push_back("user_pref(\"network.proxy.http_port\", 8800);");
			ip_setted = true;
		}
		else if (std::regex_search(v_configs[i], std::regex("\"network.proxy.http\""))) {
			v_new_configs.push_back("user_pref(\"network.proxy.http\", \"127.0.0.1\");");
			port_setted = true;
		}
		else{
			v_new_configs.push_back(v_configs[i]);
		}
	}
	if (ip_setted == false) {
		v_new_configs.push_back("user_pref(\"network.proxy.http\", \"127.0.0.1\");");
	}
	if (port_setted == false) {
		v_new_configs.push_back("user_pref(\"network.proxy.http_port\", 8800);");
	}
	if (proxy_setted == false) {
		v_new_configs.push_back("user_pref(\"network.proxy.type\", 1);");
	}
	hFile = CreateFile(w_conf_dir.c_str(),                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template
	DWORD dwBytesWritten = 0;
	for (int i = 0; i < v_new_configs.size(); i++) {
		v_new_configs[i].append("\r\n");
		WriteFile(
			hFile,           // open file handle
			v_new_configs[i].c_str(),      // start of data to write
			v_new_configs[i].length(),  // number of bytes to write
			&dwBytesWritten, // number of bytes that were written
			NULL);            // no overlapped structure
	}
	CloseHandle(hFile);
}