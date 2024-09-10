static void postmap(char *map_type, char *path_name, int postmap_flags,
		            int open_flags, int dict_flags)
{
    VSTREAM *NOCLOBBER source_fp;
    VSTRING *line_buffer;
    MKMAP  *mkmap;
    int     lineno;
    int     last_line;
    char   *key;
    char   *value;
    struct stat st;
    mode_t  saved_mask;

    /*
     * Initialize.
     */
    line_buffer = vstring_alloc(100);
    if ((open_flags & O_TRUNC) == 0) {
	/* Incremental mode. */
	source_fp = VSTREAM_IN;
	vstream_control(source_fp, CA_VSTREAM_CTL_PATH("stdin"), CA_VSTREAM_CTL_END);
    } else {
	/* Create database. */
	if (strcmp(map_type, DICT_TYPE_PROXY) == 0)
	    msg_fatal("can't create maps via the proxy service");
	dict_flags |= DICT_FLAG_BULK_UPDATE;
	if ((source_fp = vstream_fopen(path_name, O_RDONLY, 0)) == 0)
	    msg_fatal("open %s: %m", path_name);
    }
    if (fstat(vstream_fileno(source_fp), &st) < 0)
	msg_fatal("fstat %s: %m", path_name);

    /*
     * Turn off group/other read permissions as indicated in the source file.
     */
    if ((postmap_flags & POSTMAP_FLAG_SAVE_PERM) && S_ISREG(st.st_mode))
	saved_mask = umask(022 | (~st.st_mode & 077));

    /*
     * If running as root, run as the owner of the source file, so that the
     * result shows proper ownership, and so that a bug in postmap does not
     * allow privilege escalation.
     */
    if ((postmap_flags & POSTMAP_FLAG_AS_OWNER) && getuid() == 0
	&& (st.st_uid != geteuid() || st.st_gid != getegid()))
	set_eugid(st.st_uid, st.st_gid);

    /*
     * Open the database, optionally create it when it does not exist,
     * optionally truncate it when it does exist, and lock out any
     * spectators.
     */
    mkmap = mkmap_open(map_type, path_name, open_flags, dict_flags);

    /*
     * And restore the umask, in case it matters.
     */
    if ((postmap_flags & POSTMAP_FLAG_SAVE_PERM) && S_ISREG(st.st_mode))
	umask(saved_mask);

    /*
     * Trap "exceptions" so that we can restart a bulk-mode update after a
     * recoverable error.
     */
    for (;;) {
	if (dict_isjmp(mkmap->dict) != 0
	    && dict_setjmp(mkmap->dict) != 0
	    && vstream_fseek(source_fp, SEEK_SET, 0) < 0)
	    msg_fatal("seek %s: %m", VSTREAM_PATH(source_fp));

	/*
	 * Add records to the database.
	 */
	last_line = 0;
	while (readllines(line_buffer, source_fp, &last_line, &lineno)) {

	    /*
	     * First some UTF-8 checks sans casefolding.
	     */
	    if ((mkmap->dict->flags & DICT_FLAG_UTF8_ACTIVE)
		&& !allascii(STR(line_buffer))
		&& !valid_utf8_string(STR(line_buffer), LEN(line_buffer))) {
		msg_warn("%s, line %d: non-UTF-8 input \"%s\""
			 " -- ignoring this line",
			 VSTREAM_PATH(source_fp), lineno, STR(line_buffer));
		continue;
	    }

	    /*
	     * Split on the first whitespace character, then trim leading and
	     * trailing whitespace from key and value.
	     */
	    key = STR(line_buffer);
	    value = key + strcspn(key, CHARS_SPACE);
	    if (*value)
		*value++ = 0;
	    while (ISSPACE(*value))
		value++;
	    trimblanks(key, 0)[0] = 0;
	    trimblanks(value, 0)[0] = 0;

	    /*
	     * Enforce the "key whitespace value" format. Disallow missing
	     * keys or missing values.
	     */
	    if (*key == 0 || *value == 0) {
		msg_warn("%s, line %d: expected format: key whitespace value",
			 VSTREAM_PATH(source_fp), lineno);
		continue;
	    }
	    if (key[strlen(key) - 1] == ':')
		msg_warn("%s, line %d: record is in \"key: value\" format; is this an alias file?",
			 VSTREAM_PATH(source_fp), lineno);

	    /*
	     * Store the value under a case-insensitive key.
	     */
	    mkmap_append(mkmap, key, value);
	    if (mkmap->dict->error)
		msg_fatal("table %s:%s: write error: %m",
			  mkmap->dict->type, mkmap->dict->name);
	}
	break;
    }

    /*
     * Close the mapping database, and release the lock.
     */
    mkmap_close(mkmap);

    /*
     * Cleanup. We're about to terminate, but it is a good sanity check.
     */
    vstring_free(line_buffer);
    if (source_fp != VSTREAM_IN)
	vstream_fclose(source_fp);
}