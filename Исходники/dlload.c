JL_DLLEXPORT void *jl_dlopen(const char *filename, unsigned flags)
{
#if defined(_OS_WINDOWS_)
    needsSymRefreshModuleList = 1;
    size_t len = MultiByteToWideChar(CP_UTF8, 0, filename, -1, NULL, 0);
    if (!len) return NULL;
    WCHAR *wfilename = (WCHAR*)alloca(len * sizeof(WCHAR));
    if (!MultiByteToWideChar(CP_UTF8, 0, filename, -1, wfilename, len)) return NULL;
    return LoadLibraryExW(wfilename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#else
    dlerror(); /* Reset error status. */
    return dlopen(filename,
                  (flags & JL_RTLD_NOW ? RTLD_NOW : RTLD_LAZY)
                  | JL_RTLD(flags, LOCAL)
                  | JL_RTLD(flags, GLOBAL)
#ifdef RTLD_NODELETE
                  | JL_RTLD(flags, NODELETE)
#endif
#ifdef RTLD_NOLOAD
                  | JL_RTLD(flags, NOLOAD)
#endif
#if defined(RTLD_DEEPBIND) && !defined(JL_ASAN_ENABLED)
                  | JL_RTLD(flags, DEEPBIND)
#endif
#ifdef RTLD_FIRST
                  | JL_RTLD(flags, FIRST)
#endif
                  );
#endif
}