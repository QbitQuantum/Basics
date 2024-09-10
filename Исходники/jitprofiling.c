/* this function loads the collector dll (BistroJavaCollector) 
 * and the relevant functions.
 * on success: all functions load,     iJIT_DLL_is_missing = 0, return value = 1
 * on failure: all functions are NULL, iJIT_DLL_is_missing = 1, return value = 0
 */ 
static int loadiJIT_Funcs()
{
    static int bDllWasLoaded = 0;
    char *dllName = (char*)rcsid; /* !! Just to avoid unused code elimination */
#if ITT_PLATFORM==ITT_PLATFORM_WIN
    DWORD dNameLength = 0;
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */

    if(bDllWasLoaded)
    {
        /* dll was already loaded, no need to do it for the second time */
        return 1;
    }

    /* Assumes that the DLL will not be found */
    iJIT_DLL_is_missing = 1;
    FUNC_NotifyEvent = NULL;

    if (m_libHandle) 
    {
#if ITT_PLATFORM==ITT_PLATFORM_WIN
        FreeLibrary(m_libHandle);
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
        dlclose(m_libHandle);
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */
        m_libHandle = NULL;
    }

    /* Try to get the dll name from the environment */
#if ITT_PLATFORM==ITT_PLATFORM_WIN
    dNameLength = GetEnvironmentVariableA(NEW_DLL_ENVIRONMENT_VAR, NULL, 0);
    if (dNameLength)
    {
        DWORD envret = 0;
        dllName = (char*)malloc(sizeof(char) * (dNameLength + 1));
        envret = GetEnvironmentVariableA(NEW_DLL_ENVIRONMENT_VAR, 
                                         dllName, dNameLength);
        if (envret)
        {
            /* Try to load the dll from the PATH... */
            m_libHandle = LoadLibraryExA(dllName, 
                                         NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        }
        free(dllName);
    } else {
        /* Try to use old VS_PROFILER variable */
        dNameLength = GetEnvironmentVariableA(DLL_ENVIRONMENT_VAR, NULL, 0);
        if (dNameLength)
        {
            DWORD envret = 0;
            dllName = (char*)malloc(sizeof(char) * (dNameLength + 1));
            envret = GetEnvironmentVariableA(DLL_ENVIRONMENT_VAR, 
                                             dllName, dNameLength);
            if (envret)
            {
                /* Try to load the dll from the PATH... */
                m_libHandle = LoadLibraryA(dllName);
            }
            free(dllName);
        }
    }
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    dllName = getenv(NEW_DLL_ENVIRONMENT_VAR);
    if (!dllName)
        dllName = getenv(DLL_ENVIRONMENT_VAR);
#ifdef ANDROID
    if (!dllName)
        dllName = ANDROID_JIT_AGENT_PATH;
#endif
    if (dllName)
    {
        /* Try to load the dll from the PATH... */
        m_libHandle = dlopen(dllName, RTLD_LAZY);
    }
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */

    if (!m_libHandle)
    {
#if ITT_PLATFORM==ITT_PLATFORM_WIN
        m_libHandle = LoadLibraryA(DEFAULT_DLLNAME);
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
        m_libHandle = dlopen(DEFAULT_DLLNAME, RTLD_LAZY);
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    }

    /* if the dll wasn't loaded - exit. */
    if (!m_libHandle)
    {
        iJIT_DLL_is_missing = 1; /* don't try to initialize 
                                  * JIT agent the second time 
                                  */
        return 0;
    }

#if ITT_PLATFORM==ITT_PLATFORM_WIN
    FUNC_NotifyEvent = (TPNotify)GetProcAddress(m_libHandle, "NotifyEvent");
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    FUNC_NotifyEvent = (TPNotify)(intptr_t)dlsym(m_libHandle, "NotifyEvent");
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    if (!FUNC_NotifyEvent) 
    {
        FUNC_Initialize = NULL;
        return 0;
    }

#if ITT_PLATFORM==ITT_PLATFORM_WIN
    FUNC_Initialize = (TPInitialize)GetProcAddress(m_libHandle, "Initialize");
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    FUNC_Initialize = (TPInitialize)(intptr_t)dlsym(m_libHandle, "Initialize");
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    if (!FUNC_Initialize) 
    {
        FUNC_NotifyEvent = NULL;
        return 0;
    }

    executionMode = (iJIT_IsProfilingActiveFlags)FUNC_Initialize();

    bDllWasLoaded = 1;
    iJIT_DLL_is_missing = 0; /* DLL is ok. */

    /*
     * Call Graph mode: init the thread local storage
     * (need to store the virtual stack there).
     */
    if ( executionMode == iJIT_CALLGRAPH_ON )
    {
        /* Allocate a thread local storage slot for the thread "stack" */
        if (!threadLocalStorageHandle)
#if ITT_PLATFORM==ITT_PLATFORM_WIN
            threadLocalStorageHandle = TlsAlloc();
#else  /* ITT_PLATFORM==ITT_PLATFORM_WIN */
        pthread_key_create(&threadLocalStorageHandle, NULL);
#endif /* ITT_PLATFORM==ITT_PLATFORM_WIN */
    }

    return 1;
}