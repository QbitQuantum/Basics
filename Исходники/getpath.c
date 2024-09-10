static void
calculate_path(void)
{
    extern wchar_t *Py_GetProgramName(void);

    static wchar_t delimiter[2] = {DELIM, '\0'};
    static wchar_t separator[2] = {SEP, '\0'};
    char *_rtpypath = Py_GETENV("PYTHONPATH"); /* XXX use wide version on Windows */
    wchar_t *rtpypath = NULL;
    wchar_t *home = Py_GetPythonHome();
    char *_path = getenv("PATH");
    wchar_t *path_buffer = NULL;
    wchar_t *path = NULL;
    wchar_t *prog = Py_GetProgramName();
    wchar_t argv0_path[MAXPATHLEN+1];
    wchar_t zip_path[MAXPATHLEN+1];
    int pfound, efound; /* 1 if found; -1 if found build directory */
    wchar_t *buf;
    size_t bufsz;
    size_t prefixsz;
    wchar_t *defpath;
#ifdef WITH_NEXT_FRAMEWORK
    NSModule pythonModule;
    const char*    modPath;
#endif
#ifdef __APPLE__
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    uint32_t nsexeclength = MAXPATHLEN;
#else
    unsigned long nsexeclength = MAXPATHLEN;
#endif
    char execpath[MAXPATHLEN+1];
#endif
    wchar_t *_pythonpath, *_prefix, *_exec_prefix;

    _pythonpath = _Py_char2wchar(PYTHONPATH, NULL);
    _prefix = _Py_char2wchar(PREFIX, NULL);
    _exec_prefix = _Py_char2wchar(EXEC_PREFIX, NULL);

    if (!_pythonpath || !_prefix || !_exec_prefix) {
        Py_FatalError(
            "Unable to decode path variables in getpath.c: "
            "memory error");
    }

    if (_path) {
        path_buffer = _Py_char2wchar(_path, NULL);
        path = path_buffer;
    }

    /* If there is no slash in the argv0 path, then we have to
     * assume python is on the user's $PATH, since there's no
     * other way to find a directory to start the search from.  If
     * $PATH isn't exported, you lose.
     */
    if (wcschr(prog, SEP))
        wcsncpy(progpath, prog, MAXPATHLEN);
#ifdef __APPLE__
     /* On Mac OS X, if a script uses an interpreter of the form
      * "#!/opt/python2.3/bin/python", the kernel only passes "python"
      * as argv[0], which falls through to the $PATH search below.
      * If /opt/python2.3/bin isn't in your path, or is near the end,
      * this algorithm may incorrectly find /usr/bin/python. To work
      * around this, we can use _NSGetExecutablePath to get a better
      * hint of what the intended interpreter was, although this
      * will fail if a relative path was used. but in that case,
      * absolutize() should help us out below
      */
    else if(0 == _NSGetExecutablePath(execpath, &nsexeclength) && execpath[0] == SEP) {
        size_t r = mbstowcs(progpath, execpath, MAXPATHLEN+1);
        if (r == (size_t)-1 || r > MAXPATHLEN) {
            /* Could not convert execpath, or it's too long. */
            progpath[0] = '\0';
        }
    }
#endif /* __APPLE__ */
    else if (path) {
        while (1) {
            wchar_t *delim = wcschr(path, DELIM);

            if (delim) {
                size_t len = delim - path;
                if (len > MAXPATHLEN)
                    len = MAXPATHLEN;
                wcsncpy(progpath, path, len);
                *(progpath + len) = '\0';
            }
            else
                wcsncpy(progpath, path, MAXPATHLEN);

            joinpath(progpath, prog);
            if (isxfile(progpath))
                break;

            if (!delim) {
                progpath[0] = L'\0';
                break;
            }
            path = delim + 1;
        }
    }
    else
        progpath[0] = '\0';
    PyMem_RawFree(path_buffer);
    if (progpath[0] != SEP && progpath[0] != '\0')
        absolutize(progpath);
    wcsncpy(argv0_path, progpath, MAXPATHLEN);
    argv0_path[MAXPATHLEN] = '\0';

#ifdef WITH_NEXT_FRAMEWORK
    /* On Mac OS X we have a special case if we're running from a framework.
    ** This is because the python home should be set relative to the library,
    ** which is in the framework, not relative to the executable, which may
    ** be outside of the framework. Except when we're in the build directory...
    */
    pythonModule = NSModuleForSymbol(NSLookupAndBindSymbol("_Py_Initialize"));
    /* Use dylib functions to find out where the framework was loaded from */
    modPath = NSLibraryNameForModule(pythonModule);
    if (modPath != NULL) {
        /* We're in a framework. */
        /* See if we might be in the build directory. The framework in the
        ** build directory is incomplete, it only has the .dylib and a few
        ** needed symlinks, it doesn't have the Lib directories and such.
        ** If we're running with the framework from the build directory we must
        ** be running the interpreter in the build directory, so we use the
        ** build-directory-specific logic to find Lib and such.
        */
        wchar_t* wbuf = _Py_char2wchar(modPath, NULL);
        if (wbuf == NULL) {
            Py_FatalError("Cannot decode framework location");
        }

        wcsncpy(argv0_path, wbuf, MAXPATHLEN);
        reduce(argv0_path);
        joinpath(argv0_path, lib_python);
        joinpath(argv0_path, LANDMARK);
        if (!ismodule(argv0_path)) {
            /* We are in the build directory so use the name of the
               executable - we know that the absolute path is passed */
            wcsncpy(argv0_path, progpath, MAXPATHLEN);
        }
        else {
            /* Use the location of the library as the progpath */
            wcsncpy(argv0_path, wbuf, MAXPATHLEN);
        }
        PyMem_RawFree(wbuf);
    }
#endif

#if HAVE_READLINK
    {
        wchar_t tmpbuffer[MAXPATHLEN+1];
        int linklen = _Py_wreadlink(progpath, tmpbuffer, MAXPATHLEN);
        while (linklen != -1) {
            if (tmpbuffer[0] == SEP)
                /* tmpbuffer should never be longer than MAXPATHLEN,
                   but extra check does not hurt */
                wcsncpy(argv0_path, tmpbuffer, MAXPATHLEN);
            else {
                /* Interpret relative to progpath */
                reduce(argv0_path);
                joinpath(argv0_path, tmpbuffer);
            }
            linklen = _Py_wreadlink(argv0_path, tmpbuffer, MAXPATHLEN);
        }
    }
#endif /* HAVE_READLINK */

    reduce(argv0_path);
    /* At this point, argv0_path is guaranteed to be less than
       MAXPATHLEN bytes long.
    */

    /* Search for an environment configuration file, first in the
       executable's directory and then in the parent directory.
       If found, open it for use when searching for prefixes.
    */

    {
        wchar_t tmpbuffer[MAXPATHLEN+1];
        wchar_t *env_cfg = L"pyvenv.cfg";
        FILE * env_file = NULL;

        wcscpy(tmpbuffer, argv0_path);

        joinpath(tmpbuffer, env_cfg);
        env_file = _Py_wfopen(tmpbuffer, L"r");
        if (env_file == NULL) {
            errno = 0;
            reduce(tmpbuffer);
            reduce(tmpbuffer);
            joinpath(tmpbuffer, env_cfg);
            env_file = _Py_wfopen(tmpbuffer, L"r");
            if (env_file == NULL) {
                errno = 0;
            }
        }
        if (env_file != NULL) {
            /* Look for a 'home' variable and set argv0_path to it, if found */
            if (find_env_config_value(env_file, L"home", tmpbuffer)) {
                wcscpy(argv0_path, tmpbuffer);
            }
            fclose(env_file);
            env_file = NULL;
        }
    }

    if (!(pfound = search_for_prefix(argv0_path, home, _prefix))) {
        if (!Py_FrozenFlag)
            fprintf(stderr,
                "Could not find platform independent libraries <prefix>\n");
        wcsncpy(prefix, _prefix, MAXPATHLEN);
        joinpath(prefix, lib_python);
    }
    else
        reduce(prefix);

    wcsncpy(zip_path, prefix, MAXPATHLEN);
    zip_path[MAXPATHLEN] = L'\0';
    if (pfound > 0) { /* Use the reduced prefix returned by Py_GetPrefix() */
        reduce(zip_path);
        reduce(zip_path);
    }
    else
        wcsncpy(zip_path, _prefix, MAXPATHLEN);
    joinpath(zip_path, L"lib/python00.zip");
    bufsz = wcslen(zip_path);   /* Replace "00" with version */
    zip_path[bufsz - 6] = VERSION[0];
    zip_path[bufsz - 5] = VERSION[2];

    if (!(efound = search_for_exec_prefix(argv0_path, home, _exec_prefix))) {
        if (!Py_FrozenFlag)
            fprintf(stderr,
                "Could not find platform dependent libraries <exec_prefix>\n");
        wcsncpy(exec_prefix, _exec_prefix, MAXPATHLEN);
        joinpath(exec_prefix, L"lib/lib-dynload");
    }
    /* If we found EXEC_PREFIX do *not* reduce it!  (Yet.) */

    if ((!pfound || !efound) && !Py_FrozenFlag)
        fprintf(stderr,
                "Consider setting $PYTHONHOME to <prefix>[:<exec_prefix>]\n");

    /* Calculate size of return buffer.
     */
    bufsz = 0;

    if (_rtpypath && _rtpypath[0] != '\0') {
        size_t rtpypath_len;
        rtpypath = _Py_char2wchar(_rtpypath, &rtpypath_len);
        if (rtpypath != NULL)
            bufsz += rtpypath_len + 1;
    }

    defpath = _pythonpath;
    prefixsz = wcslen(prefix) + 1;
    while (1) {
        wchar_t *delim = wcschr(defpath, DELIM);

        if (defpath[0] != SEP)
            /* Paths are relative to prefix */
            bufsz += prefixsz;

        if (delim)
            bufsz += delim - defpath + 1;
        else {
            bufsz += wcslen(defpath) + 1;
            break;
        }
        defpath = delim + 1;
    }

    bufsz += wcslen(zip_path) + 1;
    bufsz += wcslen(exec_prefix) + 1;

    buf = (wchar_t *)PyMem_Malloc(bufsz*sizeof(wchar_t));

    if (buf == NULL) {
        /* We can't exit, so print a warning and limp along */
        fprintf(stderr, "Not enough memory for dynamic PYTHONPATH.\n");
        fprintf(stderr, "Using default static PYTHONPATH.\n");
        module_search_path = L"" PYTHONPATH;
    }
    else {
        /* Run-time value of $PYTHONPATH goes first */
        if (rtpypath) {
            wcscpy(buf, rtpypath);
            wcscat(buf, delimiter);
        }
        else
            buf[0] = '\0';

        /* Next is the default zip path */
        wcscat(buf, zip_path);
        wcscat(buf, delimiter);

        /* Next goes merge of compile-time $PYTHONPATH with
         * dynamically located prefix.
         */
        defpath = _pythonpath;
        while (1) {
            wchar_t *delim = wcschr(defpath, DELIM);

            if (defpath[0] != SEP) {
                wcscat(buf, prefix);
                wcscat(buf, separator);
            }

            if (delim) {
                size_t len = delim - defpath + 1;
                size_t end = wcslen(buf) + len;
                wcsncat(buf, defpath, len);
                *(buf + end) = '\0';
            }
            else {
                wcscat(buf, defpath);
                break;
            }
            defpath = delim + 1;
        }
        wcscat(buf, delimiter);

        /* Finally, on goes the directory for dynamic-load modules */
        wcscat(buf, exec_prefix);

        /* And publish the results */
        module_search_path = buf;
        module_search_path_malloced = 1;
    }

    /* Reduce prefix and exec_prefix to their essence,
     * e.g. /usr/local/lib/python1.5 is reduced to /usr/local.
     * If we're loading relative to the build directory,
     * return the compiled-in defaults instead.
     */
    if (pfound > 0) {
        reduce(prefix);
        reduce(prefix);
        /* The prefix is the root directory, but reduce() chopped
         * off the "/". */
        if (!prefix[0])
                wcscpy(prefix, separator);
    }
    else
        wcsncpy(prefix, _prefix, MAXPATHLEN);

    if (efound > 0) {
        reduce(exec_prefix);
        reduce(exec_prefix);
        reduce(exec_prefix);
        if (!exec_prefix[0])
                wcscpy(exec_prefix, separator);
    }
    else
        wcsncpy(exec_prefix, _exec_prefix, MAXPATHLEN);

    PyMem_RawFree(_pythonpath);
    PyMem_RawFree(_prefix);
    PyMem_RawFree(_exec_prefix);
    PyMem_RawFree(rtpypath);
}