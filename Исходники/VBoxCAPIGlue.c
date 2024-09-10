/**
 * Tries to locate and load VBoxCAPI.so/dylib/dll, resolving all the related
 * function pointers.
 *
 * @returns 0 on success, -1 on failure.
 *
 * @remark  This should be considered moved into a separate glue library since
 *          its its going to be pretty much the same for any user of VBoxCAPI
 *          and it will just cause trouble to have duplicate versions of this
 *          source code all around the place.
 */
int VBoxCGlueInit(void)
{
    const char *pszHome;

    memset(g_szVBoxErrMsg, 0, sizeof(g_szVBoxErrMsg));

    /*
     * If the user specifies the location, try only that.
     */
    pszHome = getenv("VBOX_APP_HOME");
    if (pszHome)
        return tryLoadLibrary(pszHome, 0);

    /*
     * Try the known standard locations.
     */
#if defined(__gnu__linux__) || defined(__linux__)
    if (tryLoadLibrary("/opt/VirtualBox", 1) == 0)
        return 0;
    if (tryLoadLibrary("/usr/lib/virtualbox", 1) == 0)
        return 0;
#elif defined(__sun__)
    if (tryLoadLibrary("/opt/VirtualBox/amd64", 1) == 0)
        return 0;
    if (tryLoadLibrary("/opt/VirtualBox/i386", 1) == 0)
        return 0;
#elif defined(__APPLE__)
    if (tryLoadLibrary("/Application/VirtualBox.app/Contents/MacOS", 1) == 0)
        return 0;
#elif defined(__FreeBSD__)
    if (tryLoadLibrary("/usr/local/lib/virtualbox", 1) == 0)
        return 0;
#elif defined(__OS2__)
    if (tryLoadLibrary("C:/Apps/VirtualBox", 1) == 0)
        return 0;
#elif defined(WIN32)
    pszHome = getenv("ProgramFiles");
    if (pszHome)
    {
        char szPath[4096];
        size_t cb = sizeof(szPath);
        char *tmp = szPath;
        strncpy(tmp, pszHome, cb);
        tmp[cb - 1] = '\0';
        cb -= strlen(tmp);
        tmp += strlen(tmp);
        strncpy(tmp, "/Oracle/VirtualBox", cb);
        tmp[cb - 1] = '\0';
        if (tryLoadLibrary(szPath, 1) == 0)
            return 0;
    }
    if (tryLoadLibrary("C:/Program Files/Oracle/VirtualBox", 1) == 0)
        return 0;
#else
# error "port me"
#endif

    /*
     * Finally try the dynamic linker search path.
     */
    if (tryLoadLibrary(NULL, 1) == 0)
        return 0;

    /* No luck, return failure. */
    return -1;
}