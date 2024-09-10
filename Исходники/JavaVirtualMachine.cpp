//debug hook to print JVM messages into console.
static jint JNICALL vfprintfHook(FILE *fp, const char *format, va_list args) {
#ifdef WINDOWS
    char buffer[20480];
    int len;
    HANDLE hConsole;
    DWORD wasWritten;

    len = _vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer), format, args);

    if (len <= 0) {
        return len;
    }

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        return false;
    }

    //JVM will always pass us ASCII
    WriteConsoleA(hConsole, buffer, strlen(buffer), &wasWritten, NULL);

    return (jint) len;
#endif //WINDOWS
#ifdef LINUX
    return 0;
#endif //LINUX
}