        uint64_t Virtual::used()
        {
            uint64_t res = 0;

            #ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            res = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

            #elif __linux        
            struct sysinfo memInfo;
            sysinfo (&memInfo);
            res = memInfo.totalram - memInfo.freeram;
            //Add other values in next statement to avoid int overflow on right hand side...
            res += memInfo.totalswap - memInfo.freeswap;
            res *= memInfo.mem_unit;
            #endif
            return res;
        }