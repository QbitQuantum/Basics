    void HEART_API InitMemTracking()
    {
#ifdef HEART_TRACK_MEMORY_ALLOCS
        InitializeCriticalSection(&g_access);
        hSysCall::hInitSystemDebugLibs();
        if (g_file == NULL)
        {
            if (g_file = fopen("mem_track.txt", "w"))
            {
                g_open = hTrue;
                hMemTrackingHeader header;
                header.baseAddress_=SymGetModuleBase64(GetCurrentProcess(), (DWORD64)&InitMemTracking);
                GetModuleFileName(0, header.moduleName_, (hUint)hArraySize(header.moduleName_));
                fwrite(&header, sizeof(hMemTrackingHeader), 1, g_file);
                fwrite("\n", 1, 1, g_file);
                atexit(memTrackExitHandle);
                //TrackPushMarker("ROOT");
            }
        }
#endif
    }