void Log::DefaultLogOutput(const char* formattedText, LogMessageType messageType, int bufferSize)
{
    OVR_UNUSED2(bufferSize, formattedText);

#if defined(OVR_OS_WIN32)

    ::OutputDebugStringA(formattedText);
    fputs(formattedText, stdout);

#elif defined(OVR_OS_MS) // Any other Microsoft OSs

    ::OutputDebugStringA(formattedText);

#elif defined(OVR_OS_ANDROID)
    // To do: use bufferSize to deal with the case that Android has a limited output length.
    __android_log_write(ANDROID_LOG_INFO, "OVR", formattedText);

#else
    fputs(formattedText, stdout);

#endif

    if (messageType == Log_Error)
    {
#if defined(OVR_OS_WIN32)
        if (!ReportEventA(hEventSource, EVENTLOG_ERROR_TYPE, 0, 0, NULL, 1, 0, &formattedText, NULL))
        {
            OVR_ASSERT(false);
        }
#elif defined(OVR_OS_MS) // Any other Microsoft OSs
        // TBD
#elif defined(OVR_OS_ANDROID)
        // TBD
#elif defined(OVR_OS_MAC) || defined(OVR_OS_LINUX)
        syslog(LOG_ERR, "%s", formattedText);
#else
        // TBD
#endif
    }
}