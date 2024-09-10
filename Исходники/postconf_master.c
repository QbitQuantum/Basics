static void pcf_normalize_daemon_args(ARGV *argv)
{
    int     field;
    char   *arg;
    char   *cp;
    char   *junk;
    int     extract_field;

    /*
     * Normalize options to simplify later processing.
     */
    for (field = PCF_MASTER_MIN_FIELDS; argv->argv[field] != 0; field++) {
	arg = argv->argv[field];
	if (arg[0] != '-' || strcmp(arg, "--") == 0)
	    break;
	for (cp = arg + 1; *cp; cp++) {
	    if (strchr(pcf_daemon_options_expecting_value, *cp) != 0
		&& cp > arg + 1) {
		/* Split "-stuffozz" into "-stuff" and "-ozz". */
		junk = concatenate("-", cp, (char *) 0);
		argv_insert_one(argv, field + 1, junk);
		myfree(junk);
		*cp = 0;			/* XXX argv_replace_one() */
		break;
	    }
	}
	if (strchr(pcf_daemon_options_expecting_value, arg[1]) == 0)
	    /* Option requires no value. */
	    continue;
	if (arg[2] != 0) {
	    /* Split "-oname=value" into "-o" "name=value". */
	    argv_insert_one(argv, field + 1, arg + 2);
	    arg[2] = 0;				/* XXX argv_replace_one() */
	    field += 1;
	    extract_field = (argv->argv[field][0] == CHARS_BRACE[0]);
	} else if (argv->argv[field + 1] != 0) {
	    /* Already in "-o" "name=value" form. */
	    field += 1;
	    extract_field = (argv->argv[field][0] == CHARS_BRACE[0]);
	} else
	    extract_field = 0;
	/* Extract text inside {}, optionally convert to name=value. */
	if (extract_field) {
	    pcf_extract_field(argv, field, CHARS_BRACE);
	    if (argv->argv[field - 1][1] == 'o')
		pcf_normalize_nameval(argv, field);
	}
    }
    /* Normalize non-option arguments. */
    for ( /* void */ ; argv->argv[field] != 0; field++)
	/* Extract text inside {}. */
	if (argv->argv[field][0] == CHARS_BRACE[0])
	    pcf_extract_field(argv, field, CHARS_BRACE);
}