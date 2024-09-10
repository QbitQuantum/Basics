APR_DECLARE(apr_status_t) apr_proc_mutex_child_init(apr_proc_mutex_t **mutex,
                                                    const char *fname,
                                                    apr_pool_t *pool)
{
    HANDLE hMutex;
    void *mutexkey;

    if (!fname) {
        /* Reinitializing unnamed mutexes is a noop in the Unix code. */
        return APR_SUCCESS;
    }

    /* res_name_from_filename turns file into a pseudo-name
     * without slashes or backslashes, and prepends the \global
     * prefix on Win2K and later
     */
    mutexkey = res_name_from_filename(fname, 1, pool);

#if defined(_WIN32_WCE)
    hMutex = CreateMutex(NULL, FALSE, mutexkey);
    if (hMutex && ERROR_ALREADY_EXISTS != GetLastError()) {
        CloseHandle(hMutex);
        hMutex = NULL;
        SetLastError(ERROR_FILE_NOT_FOUND);
    }
#else
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, mutexkey);
    }
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, mutexkey);
    }
#endif
#endif

    if (!hMutex) {
        return apr_get_os_error();
    }

    *mutex = (apr_proc_mutex_t *)apr_palloc(pool, sizeof(apr_proc_mutex_t));
    (*mutex)->pool = pool;
    (*mutex)->handle = hMutex;
    (*mutex)->fname = fname;
    apr_pool_cleanup_register((*mutex)->pool, *mutex, 
                              proc_mutex_cleanup, apr_pool_cleanup_null);
    return APR_SUCCESS;
}