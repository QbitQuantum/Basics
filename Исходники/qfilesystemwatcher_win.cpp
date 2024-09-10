QWindowsFileSystemWatcherEngine::QWindowsFileSystemWatcherEngine()
    : msg(0)
{
    HANDLE h = QT_WA_INLINE(CreateEventW(0, false, false, 0),
                                CreateEventA(0, false, false, 0));
    if (h != INVALID_HANDLE_VALUE) {
        handles.reserve(MAXIMUM_WAIT_OBJECTS);
        handles.append(h);
    }
}