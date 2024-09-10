static void diskcache_closeLockedFile(FILE *f) {
#ifdef UNIX
#ifndef MAC
    // for non-Mac OS X Unix (Linux/BSD), we use flock
    flock(fileno(f), LOCK_UN);
#else
    // for Mac OS X, we currently use nothing!
#endif
#else
    // on windows, we use LockFileEx
    HANDLE h = (HANDLE)_get_osfhandle(fileno(f));
    UnlockFile(h, 0, 0, 0, 0);
    _close((int)h);
#endif
    fclose(f);
}