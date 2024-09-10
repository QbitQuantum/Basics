void
Perl_set_caret_X(pTHX) {
    GV* tmpgv = gv_fetchpvs("\030", GV_ADD|GV_NOTQUAL, SVt_PV); /* $^X */
    SV *const caret_x = GvSV(tmpgv);
#if defined(OS2)
    sv_setpv(caret_x, os2_execname(aTHX));
#elif defined(USE_KERN_PROC_PATHNAME)
    size_t size = 0;
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PATHNAME;
    mib[3] = -1;

    if (sysctl(mib, 4, NULL, &size, NULL, 0) == 0
        && size > 0 && size < MAXPATHLEN * MAXPATHLEN) {
        sv_grow(caret_x, size);

        if (sysctl(mib, 4, SvPVX(caret_x), &size, NULL, 0) == 0
            && size > 2) {
            SvPOK_only(caret_x);
            SvCUR_set(caret_x, size - 1);
            SvTAINT(caret_x);
            return;
        }
    }
#elif defined(USE_NSGETEXECUTABLEPATH)
    char buf[1];
    uint32_t size = sizeof(buf);

    _NSGetExecutablePath(buf, &size);
    if (size < MAXPATHLEN * MAXPATHLEN) {
        sv_grow(caret_x, size);
        if (_NSGetExecutablePath(SvPVX(caret_x), &size) == 0) {
            char *const tidied = realpath(SvPVX(caret_x), NULL);
            if (tidied) {
                sv_setpv(caret_x, tidied);
                free(tidied);
            } else {
                SvPOK_only(caret_x);
                SvCUR_set(caret_x, size);
            }
            return;
        }
    }
#elif defined(HAS_PROCSELFEXE)
    char buf[MAXPATHLEN];
    SSize_t len = readlink(PROCSELFEXE_PATH, buf, sizeof(buf) - 1);
    /* NOTE: if the length returned by readlink() is sizeof(buf) - 1,
     * it is impossible to know whether the result was truncated. */

    if (len != -1) {
        buf[len] = '\0';
    }

    /* On Playstation2 Linux V1.0 (kernel 2.2.1) readlink(/proc/self/exe)
       includes a spurious NUL which will cause $^X to fail in system
       or backticks (this will prevent extensions from being built and
       many tests from working). readlink is not meant to add a NUL.
       Normal readlink works fine.
    */
    if (len > 0 && buf[len-1] == '\0') {
        len--;
    }

    /* FreeBSD's implementation is acknowledged to be imperfect, sometimes
       returning the text "unknown" from the readlink rather than the path
       to the executable (or returning an error from the readlink). Any
       valid path has a '/' in it somewhere, so use that to validate the
       result. See http://www.freebsd.org/cgi/query-pr.cgi?pr=35703
    */
    if (len > 0 && memchr(buf, '/', len)) {
        sv_setpvn(caret_x, buf, len);
        return;
    }
#elif defined(WIN32)
    char *ansi;
    WCHAR widename[MAX_PATH];
    GetModuleFileNameW(NULL, widename, sizeof(widename)/sizeof(WCHAR));
    ansi = win32_ansipath(widename);
    sv_setpv(caret_x, ansi);
    win32_free(ansi);
    return;
#else
    /* Fallback to this:  */
    sv_setpv(caret_x, PL_origargv[0]);
#endif
}