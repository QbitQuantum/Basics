int custom_expand (char * param, char ***argvptr, int *argcptr)
{
	int     count,sl;
	size_t  bufsize;
	char    *filenamebuf;
	char    *ptr,*safeptr;

	/*
	 *  Check to see if we should do wild card expansion.
	 *  We only perform wildcard expansion if the parameter
	 *  was not a string and if it contains one of the
	 *  wild card characters.
	 *
	 *  We also do not expand any option that starts with '-'
	 *  as we then assume that it is a unix stylew option.
	 */
	if ((*param == '-') ||  (strpbrk (param,"*?") == NULL) ) {
	    return 0;
	}

	if ((filenamebuf = malloc (bufsize = FILEBUF_INIT)) == NULL) {
	    return -1;
	}
TRYAGAIN:
	count = getfnl (param, filenamebuf, bufsize, QDR_ALL);
	if (count == -1  && errno == ENOMEM) {
	    /*
	     *  We have overflowed the buffer, so we try
	     *  to get a bigger buffer and try again.
	     */
	    bufsize += FILEBUF_INCR;
	    if ((filenamebuf = realloc (filenamebuf, bufsize)) == NULL) {
	        return -1;
	    } else {
	        goto TRYAGAIN;
	    }
	}
	/*
	 *  If no files were found, then return unexpanded.
	 */
	if (count == 0) {
	    free (filenamebuf);
	    return 0;
	}
	/*
	 *  Files were found, so add these to the list instead
	 *  of the original parameter typed by the user.
	 */
	for ( ptr=filenamebuf ; count > 0 ; count -- ) {
		*argvptr = (char **) realloc (*argvptr, (size_t) (((*argcptr) + 2) * sizeof (char *)));
		safeptr= (char *) malloc ((size_t) (sl=strlen (ptr) + 1));
		if (safeptr == NULL || *argvptr == NULL) {
			return -1;
		}
		(void) memcpy (safeptr,ptr, (size_t) sl);
		(*argvptr) [*argcptr] = safeptr;
		*argcptr += 1;
		ptr += sl;
	}
	free (filenamebuf);
	return *argcptr;
}