void tosThread_exit(void *exitCode)
{
#ifdef rt_LIB_Win32_i386
    HANDLE tHandle;
#endif

#ifdef tosThread_DEBUG
    if (exitCode == NULL)
        tosLog_debug("tosThread",
                     "exit",
                     "Terminating thread with exit code 0");
    else
        tosLog_debug("tosThread",
                     "exit",
                     "Terminating thread with exit code %d",
                     *(unsigned*)exitCode);
#endif

#ifdef rt_LIB_Win32_i386
    /*
     * Close thread handle, if exists
     */
    tHandle = GetCurrentThread();
    if (tHandle != (HANDLE)(-1L)) {
        CloseHandle(tHandle);
#ifdef tosThread_DEBUG
        tosLog_debug("tosThread",
                     "exit",
                     "Handle closed: %u, win32err=%d",
                     tHandle,
                     tosError_getCodeDetail());
#endif
    }

    if (exitCode == NULL)
        _endthreadex(0);
    else
        _endthreadex(*(DWORD*)exitCode);

#else
    pthread_exit(exitCode);
#endif
}