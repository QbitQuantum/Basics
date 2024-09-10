/**
 * Find display width for longest argument string.
 * @param opt		option(s)
 * @param translation_domain	translation domain
 * @return		display width
 */
static size_t maxArgWidth(const struct poptOption * opt,
		       /*@null@*/ const char * translation_domain)
	/*@*/
{
    size_t max = 0;
    size_t len = 0;
    const char * s;
    
    if (opt != NULL)
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (opt->arg)	/* XXX program error */
	    len = maxArgWidth(opt->arg, translation_domain);
	    if (len > max) max = len;
	} else if (!(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN)) {
	    len = sizeof("  ")-1;
	    if (opt->shortName != '\0') len += sizeof("-X")-1;
	    if (opt->shortName != '\0' && opt->longName) len += sizeof(", ")-1;
	    if (opt->longName) {
		len += ((opt->argInfo & POPT_ARGFLAG_ONEDASH)
			? sizeof("-")-1 : sizeof("--")-1);
		len += strlen(opt->longName);
	    }

	    s = getArgDescrip(opt, translation_domain);

#ifdef POPT_WCHAR_HACK
	    /* XXX Calculate no. of display characters. */
	    if (s) {
		const char * scopy = s;
		mbstate_t t;
		size_t n;

/*@-boundswrite@*/
		memset ((void *)&t, '\0', sizeof (t));	/* In initial state.  */
/*@=boundswrite@*/
		/* Determine number of characters.  */
		n = mbsrtowcs (NULL, &scopy, strlen(scopy), &t);
		len += sizeof("=")-1 + n;
	    }
#else
	    if (s)
		len += sizeof("=")-1 + strlen(s);
#endif

	    if (opt->argInfo & POPT_ARGFLAG_OPTIONAL) len += sizeof("[]")-1;
	    if (len > max) max = len;
	}

	opt++;
    }
    
    return max;
}