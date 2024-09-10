rpmRC rpmpythonRunFile(rpmpython python, const char * fn, const char ** resultp)
{
    rpmRC rc = RPMRC_FAIL;


if (_rpmpython_debug)
fprintf(stderr, "==> %s(%p,%s)\n", __FUNCTION__, python, fn);

    if (python == NULL) python = rpmpythonI();

    if (fn != NULL) {
#if defined(WITH_PYTHONEMBED)
	const char * pyfn = ((fn == NULL || !strcmp(fn, "-")) ? "<stdin>" : fn);
	FILE * pyfp = (!strcmp(pyfn, "<stdin>") ? stdin : fopen(fn, "rb"));
	int closeit = (pyfp != stdin);
	PyCompilerFlags cf = { .cf_flags = 0 };
	
	if (pyfp != NULL) {
	    PyRun_AnyFileExFlags(pyfp, pyfn, closeit, &cf);
	    rc = RPMRC_OK;
	}
#endif
    }
    return rc;
}

static const char * rpmpythonSlurp(const char * arg)
	/*@*/
{
    rpmiob iob = NULL;
    const char * val = NULL;
    struct stat sb;
    int xx;

    if (!strcmp(arg, "-")) {	/* Macros from stdin arg. */
	xx = rpmiobSlurp(arg, &iob);
    } else
    if ((arg[0] == '/' || strchr(arg, ' ') == NULL)
     && !Stat(arg, &sb)
     && S_ISREG(sb.st_mode)) {	/* Macros from a file arg. */
	xx = rpmiobSlurp(arg, &iob);
    } else {			/* Macros from string arg. */
	iob = rpmiobAppend(rpmiobNew(strlen(arg)+1), arg, 0);
    }

    val = xstrdup(rpmiobStr(iob));
    iob = rpmiobFree(iob);
    return val;
}