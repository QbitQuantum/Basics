SXE_RETURN
sxe_set_file_limit(const unsigned limit)
{
    SXE_RETURN result = SXE_RETURN_ERROR_INTERNAL;

#ifndef _WIN32
    struct rlimit rt;
    rt.rlim_max = limit;
    rt.rlim_cur = limit;
#endif

    if
#ifdef _WIN32
       (_setmaxstdio(limit) == -1)
#else
       (setrlimit(RLIMIT_NOFILE, &rt) == -1)
#endif
    {
        SXEL91("Failed to set file limit to '%u'", limit);
        goto SXE_ERROR_OUT; /* COVERAGE EXCLUSION - TODO: WIN32 COVERAGE */
    }