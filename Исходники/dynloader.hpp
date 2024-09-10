        bool load(const arguments & args_, std::string & result) {
            HMODULE dllHandle;
            RVExtension function;

            LOG(INFO) << "Load requested [" << args_.as_string(0) << "]";

            if (_modules.find(args_.as_string(0)) != _modules.end()) {
                LOG(ERROR) << "Module already loaded [" << args_.as_string(0) << "]";
                return true;
            }

#ifdef _WINDOWS
            // Make a copy of the file to temp, and load it from there, referencing the current path name
            char tmpPath[MAX_PATH +1], buffer[MAX_PATH + 1];

            if(!GetTempPathA(MAX_PATH, tmpPath)) {
                LOG(ERROR) << "GetTempPath() failed, e=" << GetLastError();
                return false;
            }
            if(!GetTempFileNameA(tmpPath, "ace_dynload", TRUE, buffer)) {
                LOG(ERROR) << "GetTempFileName() failed, e=" << GetLastError();
                return false;
            }
            std::string temp_filename = buffer;
            if (!CopyFileA(args_.as_string(0).c_str(), temp_filename.c_str(), FALSE)) {
                DeleteFile(temp_filename.c_str());
                if (!CopyFileA(args_.as_string(0).c_str(), temp_filename.c_str(), FALSE)) {
                    LOG(ERROR) << "CopyFile() , e=" << GetLastError();
                    return false;
                }
            }
#else
            std::string temp_filename = args_.as_string(0);
#endif

            dllHandle = LoadLibrary(temp_filename.c_str());
            if (!dllHandle) {
                LOG(ERROR) << "LoadLibrary() failed, e=" << GetLastError() << " [" << args_.as_string(0) << "]";
                return false;
            }

            function = (RVExtension)GetProcAddress(dllHandle, "_RVExtension@12");
            if (!function) {
                LOG(ERROR) << "GetProcAddress() failed, e=" << GetLastError() << " [" << args_.as_string(0) << "]";
                FreeLibrary(dllHandle);
                return false;
            }

            LOG(INFO) << "Load completed [" << args_.as_string(0) << "]";

            _modules[args_.as_string(0)] = module(args_.as_string(0), dllHandle, function, temp_filename);

            return false;
        }