    //
    // system warnings
    //
    void logCommonStartupWarnings() {
        // each message adds a leading and a trailing newline

        bool warned = false;
        {
            const char * foo = strchr(versionString , '.') + 1;
            int bar = atoi(foo);
            if ((2 * (bar / 2)) != bar) {
                log() << startupWarningsLog;
                log() << "** NOTE: This is a development version (" << versionString
                      << ") of MongoDB." << startupWarningsLog;
                log() << "**       Not recommended for production." << startupWarningsLog;
                warned = true;
            }
        }

#if defined(_WIN32) && !defined(_WIN64)
        // Warn user that they are running a 32-bit app on 64-bit Windows
        BOOL wow64Process;
        BOOL retWow64 = IsWow64Process(GetCurrentProcess(), &wow64Process);
        if (retWow64 && wow64Process) {
            log() << "** NOTE: This is a 32-bit MongoDB binary running on a 64-bit operating"
                    << startupWarningsLog;
            log() << "**      system. Switch to a 64-bit build of MongoDB to"
                    << startupWarningsLog;
            log() << "**      support larger databases." << startupWarningsLog;
            warned = true;
        }
#endif

#if !defined(_WIN32)
        if (getuid() == 0) {
            log() << "** WARNING: You are running this process as the root user, "
                  << "which is not recommended." << startupWarningsLog;
            warned = true;
        }
#endif

        if (warned) {
            log() << startupWarningsLog;
        }
    }