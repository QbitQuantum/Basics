static void
join(wchar_t *buffer, const wchar_t *stuff)
{
    if (_PathCchCombineEx_Initialized == 0) {
        HMODULE pathapi = LoadLibraryW(L"api-ms-win-core-path-l1-1-0.dll");
        if (pathapi)
            _PathCchCombineEx = (PPathCchCombineEx)GetProcAddress(pathapi, "PathCchCombineEx");
        else
            _PathCchCombineEx = NULL;
        _PathCchCombineEx_Initialized = 1;
    }

    if (_PathCchCombineEx) {
        if (FAILED(_PathCchCombineEx(buffer, MAXPATHLEN+1, buffer, stuff, 0)))
            Py_FatalError("buffer overflow in getpathp.c's join()");
    } else {
        if (!PathCombineW(buffer, buffer, stuff))
            Py_FatalError("buffer overflow in getpathp.c's join()");
    }
}