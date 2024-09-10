const char * rpmmgFile(rpmmg mg, const char *fn)
{
    const char * t = NULL;

if (_rpmmg_debug)
fprintf(stderr, "--> rpmmgFile(%p, %s)\n", mg, (fn ? fn : "(nil)"));

#if defined(HAVE_MAGIC_H)
    if (mg->ms) {
	const char * lpath = NULL;
	int ut = urlPath(fn, &lpath);

	switch (ut) {
	case URL_IS_FTP:
	case URL_IS_HKP:
	case URL_IS_HTTP:
	case URL_IS_HTTPS:
	{   char b[512];
	    size_t nb = 0;
	    FD_t fd;
	    
	    fd = Fopen(fn, "r.ufdio");
	    if (fd != NULL && !Ferror(fd)) {
		nb = Fread(b, 1, sizeof(b), fd);
		(void) Fclose(fd);
	    }
	    if (nb > 0)
		return rpmmgBuffer(mg, b, nb);
	}   break;
	case URL_IS_DASH:
	case URL_IS_MONGO:	/* XXX FIXME */
	    break;
	case URL_IS_PATH:
	    fn = lpath;
	    /*@fallthrough@*/
	case URL_IS_UNKNOWN:
	default:
	    t = magic_file(mg->ms, fn);
	    /* XXX HACK: libmagic compiled without <pcreposix.h> spews here. */
	    if (t == NULL) {
		const char * msg = magic_error(mg->ms);
		if (strstr(msg, "regexec error 17, (match failed)") == NULL)
		    rpmlog(RPMLOG_ERR, _("magic_file(ms, %s) failed: %s\n"),
			    (fn ? fn : "(nil)"), msg);
	    }
	    break;
	}
    }
#endif

    if (t == NULL) t = "";
    t = xstrdup(t);

if (_rpmmg_debug)
fprintf(stderr, "<-- rpmmgFile(%p, %s) %s\n", mg, (fn ? fn : "(nil)"), t);
    return t;
}