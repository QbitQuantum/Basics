int __cdecl _tspawnvpe (
    int modeflag,
    REG3 const _TSCHAR *filename,
    const _TSCHAR * const *argv,
    const _TSCHAR * const *envptr
)
{
    int i;
    REG1 _TSCHAR *env;
    REG2 _TSCHAR *buf = NULL;
    _TSCHAR *pfin;
    _ASSERTE(filename != NULL);
    _ASSERTE(*filename != _T('\0'));
    _ASSERTE(argv != NULL);
    _ASSERTE(*argv != NULL);
    _ASSERTE(**argv != _T('\0'));


    if (
        (i = _tspawnve(modeflag, filename, argv, envptr)) != -1
        /* everything worked just fine; return i */

        || (errno != ENOENT)
        /* couldn't spawn the process, return failure */

        || (_tcschr(filename, XSLASHCHAR) != NULL)
        /* filename contains a '/', return failure */


        || !(env = _tgetenv(_T("PATH")))
        /* no PATH environment string name, return failure */

        || ( (buf = _malloc_crt(_MAX_PATH * sizeof(_TSCHAR))) == NULL )
        /* cannot allocate buffer to build alternate pathnames, return
         * failure */
    ) {
        goto done;
    }



    /* could not find the file as specified, search PATH. try each
     * component of the PATH until we get either no error return, or the
     * error is not ENOENT and the component is not a UNC name, or we run
     * out of components to try.
     */

#ifdef WPRFLAG
    while ( (env = _wgetpath(env, buf, _MAX_PATH - 1)) && (*buf) ) {
#else  /* WPRFLAG */
    while ( (env = _getpath(env, buf, _MAX_PATH - 1)) && (*buf) ) {
#endif  /* WPRFLAG */

        pfin = buf + _tcslen(buf) - 1;

        /* if necessary, append a '/'
         */
#ifdef _MBCS
        if (*pfin == SLASHCHAR) {
            if (pfin != _mbsrchr(buf,SLASHCHAR))
                /* fin is the second byte of a double-byte char */
                strcat(buf, SLASH );
        }
        else if (*pfin !=XSLASHCHAR)
            strcat(buf, SLASH);
#else  /* _MBCS */
        if (*pfin != SLASHCHAR && *pfin != XSLASHCHAR)
            _tcscat(buf, SLASH);
#endif  /* _MBCS */
        /* check that the final path will be of legal size. if so,
         * build it. otherwise, return to the caller (return value
         * and errno rename set from initial call to _spawnve()).
         */
        if ( (_tcslen(buf) + _tcslen(filename)) < _MAX_PATH )
            _tcscat(buf, filename);
        else
            break;

        /* try spawning it. if successful, or if errno comes back with a
         * value other than ENOENT and the pathname is not a UNC name,
         * return to the caller.
         */
        if ( (i = _tspawnve(modeflag, buf, argv, envptr)) != -1
                || ((errno != ENOENT)
#ifdef _MBCS
                    && (!ISPSLASH(buf) || !ISPSLASH(buf+1))) )
#else  /* _MBCS */
                    && (!ISSLASH(*buf) || !ISSLASH(*(buf+1)))) )
#endif  /* _MBCS */
            break;

    }

done:
    if (buf != NULL)
        _free_crt(buf);
    return(i);
}