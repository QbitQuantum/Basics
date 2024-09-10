/*
 * Add an environment variable for [eid] to the container [zsp].
 *
 * The variable name is the concatenation of [prefix] and [name] converted to
 * uppercase with non-alphanumeric characters converted to underscores;
 * [prefix] is optional, and [name] must begin with an alphabetic character.
 * If the converted variable name already exists within the container [zsp],
 * its existing value will be replaced with the new value.
 *
 * The variable value is specified by the format string [fmt].
 *
 * Returns 0 on success, and -1 on error (with errno set).
 *
 * All environment variables in [zsp] should be added through this function.
 */
static int
_zed_event_add_var(uint64_t eid, zed_strings_t *zsp,
    const char *prefix, const char *name, const char *fmt, ...)
{
	char keybuf[MAXBUF];
	char valbuf[MAXBUF];
	char *dstp;
	const char *srcp;
	const char *lastp;
	int n;
	int buflen;
	va_list vargs;

	assert(zsp != NULL);
	assert(fmt != NULL);

	if (!name) {
		errno = EINVAL;
		zed_log_msg(LOG_WARNING,
		    "Failed to add variable for eid=%llu: Name is empty", eid);
		return (-1);
	} else if (!isalpha(name[0])) {
		errno = EINVAL;
		zed_log_msg(LOG_WARNING,
		    "Failed to add variable for eid=%llu: "
		    "Name \"%s\" is invalid", eid, name);
		return (-1);
	}
	/*
	 * Construct the string key by converting PREFIX (if present) and NAME.
	 */
	dstp = keybuf;
	lastp = keybuf + sizeof (keybuf);
	if (prefix) {
		for (srcp = prefix; *srcp && (dstp < lastp); srcp++)
			*dstp++ = isalnum(*srcp) ? toupper(*srcp) : '_';
	}
	for (srcp = name; *srcp && (dstp < lastp); srcp++)
		*dstp++ = isalnum(*srcp) ? toupper(*srcp) : '_';

	if (dstp == lastp) {
		errno = ENAMETOOLONG;
		zed_log_msg(LOG_WARNING,
		    "Failed to add variable for eid=%llu: Name too long", eid);
		return (-1);
	}
	*dstp = '\0';
	/*
	 * Construct the string specified by "[PREFIX][NAME]=[FMT]".
	 */
	dstp = valbuf;
	buflen = sizeof (valbuf);
	n = strlcpy(dstp, keybuf, buflen);
	if (n >= sizeof (valbuf)) {
		errno = EMSGSIZE;
		zed_log_msg(LOG_WARNING, "Failed to add %s for eid=%llu: %s",
		    keybuf, eid, "Exceeded buffer size");
		return (-1);
	}
	dstp += n;
	buflen -= n;

	*dstp++ = '=';
	buflen--;

	if (buflen <= 0) {
		errno = EMSGSIZE;
		zed_log_msg(LOG_WARNING, "Failed to add %s for eid=%llu: %s",
		    keybuf, eid, "Exceeded buffer size");
		return (-1);
	}

	va_start(vargs, fmt);
	n = vsnprintf(dstp, buflen, fmt, vargs);
	va_end(vargs);

	if ((n < 0) || (n >= buflen)) {
		errno = EMSGSIZE;
		zed_log_msg(LOG_WARNING, "Failed to add %s for eid=%llu: %s",
		    keybuf, eid, "Exceeded buffer size");
		return (-1);
	} else if (zed_strings_add(zsp, keybuf, valbuf) < 0) {
		zed_log_msg(LOG_WARNING, "Failed to add %s for eid=%llu: %s",
		    keybuf, eid, strerror(errno));
		return (-1);
	}
	return (0);
}