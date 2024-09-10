static int get_cpu_count()
{
    int core_count = 16;

#if HAVE_UNISTD_H && !defined(__OS2__)
#if defined(_SC_NPROCESSORS_ONLN)
    core_count = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
    core_count = sysconf(_SC_NPROC_ONLN);
#endif
#elif defined(_WIN32)
    {
#if _WIN32_WINNT >= 0x0501
        SYSTEM_INFO sysinfo;
        GetNativeSystemInfo(&sysinfo);
#else
        PGNSI pGNSI;
        SYSTEM_INFO sysinfo;

        /* Call GetNativeSystemInfo if supported or
         * GetSystemInfo otherwise. */

        pGNSI = (PGNSI) GetProcAddress(
                GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
        if (pGNSI != NULL)
            pGNSI(&sysinfo);
        else
            GetSystemInfo(&sysinfo);
#endif

        core_count = sysinfo.dwNumberOfProcessors;
    }
#elif defined(__OS2__)
    {
        ULONG proc_id;
        ULONG status;

        core_count = 0;
        for (proc_id = 1; ; proc_id++)
        {
            if (DosGetProcessorStatus(proc_id, &status))
                break;

            if (status == PROC_ONLINE)
                core_count++;
        }
    }
#else
    /* other platforms */
#endif

    return core_count > 0 ? core_count : 1;
}