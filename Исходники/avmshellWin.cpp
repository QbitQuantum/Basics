        void WinPlatform::initializeLogging(const char* filename)
        {
        #if defined (UNDER_CE)
            int filenameLen = VMPI_strlen(filename);

            TCHAR* logname = new TCHAR[filenameLen+1];

            mbstowcs(logname, filename, filenameLen+1);

            _wfreopen(logname, L"w", stdout);

            delete [] logname;
        #else
            FILE *f = freopen(filename, "w", stdout);
            if (!f)
                AvmLog("freopen %s failed.\n",filename);
        #endif /* UNDER_CE */
        }