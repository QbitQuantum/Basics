int rpmiobSlurp(const char * fn, rpmiob * iobp)
{
    static size_t blenmax = (128 * BUFSIZ);	/* XXX 1Mb with glibc */
    rpmuint8_t * b = NULL;
    size_t blen = 0;
    struct stat sb;
    FD_t fd;
    int rc = 0;
    int xx;

    fd = Fopen(fn, "r.ufdio");
    if (fd == NULL || Ferror(fd)) {
        rc = 2;
        goto exit;
    }
    sb.st_size = 0;
    if ((xx = Fstat(fd, &sb)) < 0 || sb.st_size == 0)
        sb.st_size = blenmax;
#if defined(__linux__)
    /* XXX st->st_size = 0 for /proc files on linux, see stat(2). */
    /* XXX glibc mmap'd libio no workie for /proc files on linux?!? */
    if (sb.st_size == 0 && !strncmp(fn, "/proc/", sizeof("/proc/")-1)) {
        blen = blenmax;
        b = xmalloc(blen+1);
        b[0] = (rpmuint8_t) '\0';

        xx = read(Fileno(fd), b, blen);
        blen = (size_t) (xx >= 0 ? xx : 0);
    } else
#endif
    {
        blen = sb.st_size;
        b = xmalloc(blen+1);
        b[0] = (rpmuint8_t) '\0';

        blen = Fread(b, sizeof(*b), blen, fd);
        if (Ferror(fd)) {
            rc = 1;
            goto exit;
        }
    }
    if (blen < (size_t)sb.st_size)
        b = xrealloc(b, blen+1);
    b[blen] = (rpmuint8_t) '\0';

exit:
    if (fd != NULL) (void) Fclose(fd);

    if (rc == 0) {
        if (iobp != NULL) {
            /* XXX use rpmiobNew() if/when lazy iop->b alloc is implemented. */
            rpmiob iob = rpmiobGetPool(_rpmiobPool);
            iob->b = b;
            iob->blen = blen;
            iob->allocated = blen;
            *iobp = iob;
        }
    } else {
        if (iobp)
            *iobp = NULL;
        b = _free(b);
    }

    return rc;
}