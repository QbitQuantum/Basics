static void assert_result(HRESULT hres, JNIEnv *env) {
#ifdef _DEBUG
    if (hres != 0) {
        DWORD lastError = GetLastError();
        if (lastError != 0) {
            LPSTR msgBuffer = NULL;
            FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    lastError,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPSTR)&msgBuffer,
                    // it's an output parameter when allocate buffer is used
                    0,
                    NULL);
            DTRACE_PRINTLN3("Error: hres=0x%x lastError=0x%x %s\n", hres,
                                                lastError, msgBuffer);
        }
    }
#endif
}