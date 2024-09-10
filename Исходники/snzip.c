static void copy_file_attributes(int infd, int outfd, const char *outfile)
{
#ifdef WIN32
    BY_HANDLE_FILE_INFORMATION fi;
    BOOL bOk;

    bOk = GetFileInformationByHandle((HANDLE)_get_osfhandle(infd), &fi);
    trace("GetFileInformationByHandle(...) => %s\n", bOk ? "TRUE" : "FALSE");
    if (bOk) {
        bOk = SetFileTime((HANDLE)_get_osfhandle(outfd), NULL, &fi.ftLastAccessTime, &fi.ftLastWriteTime);
        trace("SetFileTime(...) => %s\n", bOk ? "TRUE" : "FALSE");
        bOk = SetFileAttributesA(outfile, fi.dwFileAttributes);
        trace("SetFileAttributesA(...) => %s\n", bOk ? "TRUE" : "FALSE");
    }
#else
    struct stat sbuf;
#ifdef HAVE_FUTIMENS
    struct timespec times[2];
#else
    struct timeval times[2];
#endif
    int rv;

    if ((rv = fstat(infd, &sbuf)) != 0) {
        trace("fstat(%d, &sbuf) => %d (errno = %d)\n",
              infd, rv, errno);
        return;
    }

    /* copy file times. */
#ifdef HAVE_FUTIMENS
    times[0].tv_sec = sbuf.st_atime;
    times[0].tv_nsec = SNZ_ST_TIME_NSEC(sbuf, a);
    times[1].tv_sec = sbuf.st_mtime;
    times[1].tv_nsec = SNZ_ST_TIME_NSEC(sbuf, m);
    rv = futimens(outfd, times);
    trace("futimens(%d, [{%ld, %ld}, {%ld, %ld}]) => %d\n",
          outfd, times[0].tv_sec, times[0].tv_nsec,
          times[1].tv_sec, times[1].tv_nsec, rv);
#else /* HAVE_FUTIMENS */
    times[0].tv_sec = sbuf.st_atime;
    times[0].tv_usec = SNZ_ST_TIME_NSEC(sbuf, a) / 1000;
    times[1].tv_sec = sbuf.st_mtime;
    times[1].tv_usec = SNZ_ST_TIME_NSEC(sbuf, m) / 1000;
#ifdef HAVE_FUTIMES
    rv = futimes(outfd, times);
    trace("futimes(%d, [{%ld, %ld}, {%ld, %ld}]) => %d\n",
          outfd, times[0].tv_sec, times[0].tv_usec,
          times[1].tv_sec, times[1].tv_usec, rv);
#else /* HAVE_FUTIMES */
    rv = utimes(outfile, times);
    trace("utimes(\"%s\", [{%ld, %ld}, {%ld, %ld}]) => %d\n",
          outfile, times[0].tv_sec, times[0].tv_usec,
          times[1].tv_sec, times[1].tv_usec, rv);
#endif /* HAVE_FUTIMES */
#endif /* HAVE_FUTIMENS */

    /* copy other attributes */
    rv = fchown(outfd, sbuf.st_uid, sbuf.st_gid);
    trace("fchown(%d, %d, %d) => %d\n",
          outfd, sbuf.st_uid, sbuf.st_gid, rv);
    rv = fchmod(outfd, sbuf.st_mode);
    trace("fchmod(%d, 0%o) => %d\n",
          outfd, sbuf.st_mode, rv);
#endif
}