	icd_loader::icd_loader()
	{
#ifdef FREEOCL_ALWAYS_LOAD_FREEOCL
        bool b_FreeOCL_loaded = false;
#endif
#ifdef FREEOCL_OS_WINDOWS
        HKEY key;
        RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Khronos\\OpenCL\\Vendors", 0, KEY_QUERY_VALUE | KEY_READ, &key);
        for(int i = 0 ; true ; ++i)
        {
            char valueName[261];
            memset(valueName, 0, sizeof(valueName));
            DWORD valueNameSize = sizeof(valueName) - 1;
            DWORD type;
            DWORD data;
            DWORD data_size = sizeof(data);
            if (RegEnumValueA(key, i, valueName, &valueNameSize, NULL, &type, (LPBYTE)&data, &data_size) != 0)
                break;
            if (type == REG_DWORD && data == 0)
            {
                valueName[valueNameSize] = 0;
                load(valueName);
#ifdef FREEOCL_ALWAYS_LOAD_FREEOCL
                b_FreeOCL_loaded |= (std::string(valueName).find("libFreeOCL.dll") != std::string::npos);
#endif
            }
        }

        RegCloseKey(key);

#ifdef FREEOCL_ALWAYS_LOAD_FREEOCL
        if (!b_FreeOCL_loaded)
            load("libFreeOCL.dll");
#endif

#else
		// Get the list of all *.icd files in /etc/OpenCL/vendors/
		const std::deque<std::string> &files = list_files("/etc/OpenCL/vendors/", ".icd");
		// For each file
		for(std::deque<std::string>::const_iterator i = files.begin() ; i != files.end() ; ++i)
		{
			std::ifstream file(i->c_str(), std::ios_base::in);
			if (!file.is_open())
				continue;
			// Read the corresponding library name
			std::string lib;
			file >> lib;
			// And load it
			load(lib);
			file.close();
#ifdef FREEOCL_ALWAYS_LOAD_FREEOCL
            b_FreeOCL_loaded |= (lib.find("libFreeOCL.so") != std::string::npos);
#endif
        }
#ifdef FREEOCL_ALWAYS_LOAD_FREEOCL
        if (!b_FreeOCL_loaded)
            load("libFreeOCL.so");
#endif

#endif
	}