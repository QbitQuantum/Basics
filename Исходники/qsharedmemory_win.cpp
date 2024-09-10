HANDLE QSharedMemoryPrivate::handle()
{
    if (!hand) {
        const QLatin1String function("QSharedMemory::handle");
        if (nativeKey.isEmpty()) {
            error = QSharedMemory::KeyError;
            errorString = QSharedMemory::tr("%1: unable to make key").arg(function);
            return 0;
        }
#if defined(Q_OS_WINPHONE)
        Q_UNIMPLEMENTED();
        hand = 0;
#elif defined(Q_OS_WINRT)
#if _MSC_VER >= 1900
        hand = OpenFileMappingFromApp(FILE_MAP_ALL_ACCESS, FALSE, reinterpret_cast<PCWSTR>(nativeKey.utf16()));
#else
        hand = CreateFileMappingFromApp(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, (PCWSTR)nativeKey.utf16());
#endif
#elif defined(Q_OS_WINCE)
        // This works for opening a mapping too, but always opens it with read/write access in
        // attach as it seems.
        hand = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 0, (wchar_t*)nativeKey.utf16());
#else
        hand = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, (wchar_t*)nativeKey.utf16());
#endif
        if (!hand) {
            setErrorString(function);
            return 0;
        }
    }
    return hand;
}