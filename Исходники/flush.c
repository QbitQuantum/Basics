static VSTRING *flush_site_to_path(VSTRING *path, const char *site)
{
    const char *ptr;
    int     ch;

    /*
     * Allocate buffer on the fly; caller still needs to clean up.
     */
    if (path == 0)
	path = vstring_alloc(10);

    /*
     * Mask characters that could upset the name-to-queue-file mapping code.
     */
    for (ptr = site; (ch = *(unsigned const char *) ptr) != 0; ptr++)
	if (ISALNUM(ch))
	    VSTRING_ADDCH(path, ch);
	else
	    VSTRING_ADDCH(path, '_');
    VSTRING_TERMINATE(path);

    if (msg_verbose)
	msg_info("site %s to path %s", site, STR(path));

    return (path);
}