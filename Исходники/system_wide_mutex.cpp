SystemWideMutex::MutexData::MutexData(const wchar_t *mutex_name)
    : m_acquired(0)
{
    static const wchar_t prefix[] = L"csr_mutex_";
    //  this call previously used _alloca.  It is probably better to do so,
    //  but I'm a coward when it comes to new things...  this string gets
    //  deleted at the end of the function.

#ifdef MUTEX_LOG
    enable_logging_ = (wcscmp(mutex_name, L"spi_app_mutex" ) == 0);
#endif

    wchar_t * string = new wchar_t [ wcslen(mutex_name) + wcslen(prefix) + 1 ];
    wcscpy(string, prefix);
    wcscat(string, mutex_name);

    wchar_t *sp = string;
    while (*sp)
    {
        if (wcschr(L".\\/\"*", *sp))
            *sp = L'-';
        sp++;
    }
    handle = CreateMutexW(NULL, 0, string);
    OUTPUT_HANDLE_CREATE(handle);

    // OutputDebugString("Mutex created:");
    // OutputDebugString(string);
    // OutputDebugString("\n");
    // int lasterr = GetLastError();
    // assert(handle);
    delete string;
}