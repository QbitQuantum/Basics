/* There are at least four functions for generating temporary
 * filenames.  We use mkstemp (BSD 4.3) if possible, else tempnam (SVID 3),
 * else mktemp (BSD 4.3), and as last resort tmpnam (POSIX).  Reason is that
 * mkstemp, tempnam, and mktemp both allow to specify the directory in which
 * the temporary file will be created.
 *
 * And the _correct_ way to use the deprecated functions probably involves
 * opening file descriptors using O_EXCL & O_CREAT and even doing the annoying
 * NFS locking thing, but until I hear of more problems, I'm not going to
 * bother.
 */
FILE *cvs_temp_file (char **filename)
{
    char *fn;
    FILE *fp;

    /* FIXME - I'd like to be returning NULL here in noexec mode, but I think
     * some of the rcs & diff functions which rely on a temp file run in
     * noexec mode too.
     */

    assert (filename != NULL);

#ifdef HAVE_MKSTEMP

    {
        int fd;

        fn = (char*)xmalloc (strlen (Tmpdir) + 11);
        sprintf (fn, "%s/%s", Tmpdir, "cvsXXXXXX" );
        fd = mkstemp (fn);

        /* a NULL return will be interpreted by callers as an error and
         * errno should still be set
         */
        if (fd == -1) fp = NULL;
        else if ((fp = CVS_FDOPEN (fd, "w+")) == NULL)
        {
            /* attempt to close and unlink the file since mkstemp returned sucessfully and
             * we believe it's been created and opened
             */
            int save_errno = errno;
            if (close (fd))
                error (0, errno, "Failed to close temporary file %s", fn_root(fn));
            if (CVS_UNLINK (fn))
                error (0, errno, "Failed to unlink temporary file %s", fn_root(fn));
            errno = save_errno;
        }

        if (fp == NULL) xfree (fn);
        /* mkstemp is defined to open mode 0600 using glibc 2.0.7+ */
        /* FIXME - configure can probably tell us which version of glibc we are
         * linking to and not chmod for 2.0.7+
         */
        else chmod (fn, 0600);

    }

#elif HAVE_TEMPNAM

    /* tempnam has been deprecated due to under-specification */

    fn = tempnam (Tmpdir, "cvs");
    if (fn == NULL) fp = NULL;
    else if ((fp = CVS_FOPEN (fn, "w+")) == NULL) xfree (fn);
    else chmod (fn, 0600);

    /* tempnam returns a pointer to a newly malloc'd string, so there's
     * no need for a xstrdup
     */

#elif HAVE_MKTEMP

    /* mktemp has been deprecated due to the BSD 4.3 specification specifying
     * that XXXXXX will be replaced by a PID and a letter, creating only 26
     * possibilities, a security risk, and a race condition.
     */

    {
        char *ifn;

        ifn = xmalloc (strlen (Tmpdir) + 11);
        sprintf (ifn, "%s/%s", Tmpdir, "cvsXXXXXX" );
        fn = mktemp (ifn);

        if (fn == NULL) fp = NULL;
        else fp = CVS_FOPEN (fn, "w+");

        if (fp == NULL) xfree (ifn);
        else chmod (fn, 0600);

    }

#else	/* use tmpnam if all else fails */

    /* tmpnam is deprecated */

    {
        char ifn[L_tmpnam + 1];

        fn = tmpnam (ifn);

        if (fn == NULL) fp = NULL;
        else if ((fp = CVS_FOPEN (ifn, "w+")) != NULL)
        {
            fn = xstrdup (ifn);
            chmod (fn, 0600);
        }

    }

#endif

    *filename = fn;
    return fp;
}