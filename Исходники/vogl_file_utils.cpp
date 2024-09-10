bool file_utils::split_path(const char *p, dynamic_string *pDrive, dynamic_string *pDir, dynamic_string *pFilename, dynamic_string *pExt)
{
    VOGL_ASSERT(p);

#if defined(PLATFORM_WINDOWS)
    char drive_buf[_MAX_DRIVE];
    char dir_buf[_MAX_DIR];
    char fname_buf[_MAX_FNAME];
    char ext_buf[_MAX_EXT];

#if defined(COMPILER_MSVC)
    // Compiling with MSVC
    errno_t error = _splitpath_s(p,
                                 pDrive ? drive_buf : NULL, pDrive ? _MAX_DRIVE : 0,
                                 pDir ? dir_buf : NULL, pDir ? _MAX_DIR : 0,
                                 pFilename ? fname_buf : NULL, pFilename ? _MAX_FNAME : 0,
                                 pExt ? ext_buf : NULL, pExt ? _MAX_EXT : 0);
    if (error != 0)
        return false;
#elif defined(COMPILER_MINGW)
    // Compiling with MinGW
    _splitpath(p,
               pDrive ? drive_buf : NULL,
               pDir ? dir_buf : NULL,
               pFilename ? fname_buf : NULL,
               pExt ? ext_buf : NULL);
#else
#error "Need to provide splitpath functionality for this compiler / platform combo."
#endif

    if (pDrive)
        *pDrive = drive_buf;
    if (pDir)
        *pDir = dir_buf;
    if (pFilename)
        *pFilename = fname_buf;
    if (pExt)
        *pExt = ext_buf;
#else // !PLATFORM_WINDOWS
    char dirtmp[1024];
    char nametmp[1024];
    strcpy_safe(dirtmp, sizeof(dirtmp), p);
    strcpy_safe(nametmp, sizeof(nametmp), p);

    if (pDrive)
        pDrive->clear();

    const char *pDirName = dirname(dirtmp);
    if (!pDirName)
        return false;

    if (pDir)
    {
        pDir->set(pDirName);
        if ((!pDir->is_empty()) && (pDir->back() != '/'))
            pDir->append_char('/');
    }

    const char *pBaseName = basename(nametmp);
    if (!pBaseName)
        return false;

    if (pFilename)
    {
        pFilename->set(pBaseName);
        remove_extension(*pFilename);
    }

    if (pExt)
    {
        pExt->set(pBaseName);
        get_extension(*pExt);
        if (pExt->get_len())
            *pExt = "." + *pExt;
    }
#endif // #if defined(PLATFORM_WINDOWS)

    return true;
}