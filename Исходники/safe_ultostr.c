unsigned long safe_strtoul(const char *start, char **end, int base)
{
    const char *myname = "safe_strtoul";
    static unsigned char *char_map = 0;
    unsigned char *cp;
    unsigned long sum;
    unsigned long div_limit;
    unsigned long mod_limit;
    int     char_val;

    /*
     * Sanity check.
     */
    if (base < SAFE_MIN_BASE || base > SAFE_MAX_BASE)
	msg_panic("%s: bad base: %d", myname, base);

    /*
     * One-time initialization. Assume 8-bit bytes.
     */
    if (char_map == 0) {
	char_map = (unsigned char *) mymalloc(256);
	for (char_val = 0; char_val < 256; char_val++)
	    char_map[char_val] = SAFE_MAX_BASE;
	for (char_val = 0; char_val < SAFE_MAX_BASE; char_val++)
	    char_map[safe_chars[char_val]] = char_val;
    }

    /*
     * Per-call initialization.
     */
    sum = 0;
    div_limit = ULONG_MAX / base;
    mod_limit = ULONG_MAX % base;

    /*
     * Skip leading whitespace. We don't implement sign/base prefixes.
     */
    if (end)
	*end = (char *) start;
    while (ISSPACE(*start))
	++start;

    /*
     * Start the conversion.
     */
    errno = 0;
    for (cp = (unsigned char *) start; (char_val = char_map[*cp]) < base; cp++) {
	/* Return (ULONG_MAX, ERANGE) if the result is too large. */
	if (sum > div_limit
	    || (sum == div_limit && char_val > mod_limit)) {
	    sum = ULONG_MAX;
	    errno = ERANGE;
	    /* Skip "valid" characters, per the strtoul() spec. */
	    while (char_map[*++cp] < base)
		 /* void */ ;
	    break;
	}
	sum = sum * base + char_val;
    }
    /* Return (0, EINVAL) after no conversion. Test moved here 20131209. */
    if (cp == (unsigned char *) start)
	errno = EINVAL;
    else if (end)
	*end = (char *) cp;
    return (sum);
}