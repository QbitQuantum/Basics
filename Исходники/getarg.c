ROKEN_LIB_FUNCTION void ROKEN_LIB_CALL
arg_printusage_i18n (struct getargs *args,
		     size_t num_args,
		     const char *usage,
		     const char *progname,
		     const char *extra_string,
		     char *(*i18n)(const char *))
{
    size_t i, max_len = 0;
    char buf[128];
    int col = 0, columns;

    if (progname == NULL)
	progname = getprogname();

    if (i18n == NULL)
	i18n = builtin_i18n;

    if(getenv("GETARGMANDOC")){
	mandoc_template(args, num_args, progname, extra_string, i18n);
	return;
    }
    if(get_window_size(2, NULL, &columns) == -1)
	columns = 80;
    col = 0;
    col += fprintf (stderr, "%s: %s", usage, progname);
    buf[0] = '\0';
    for (i = 0; i < num_args; ++i) {
	if(args[i].short_name && ISFLAG(args[i])) {
	    char s[2];
	    if(buf[0] == '\0')
		strlcpy(buf, "[-", sizeof(buf));
	    s[0] = args[i].short_name;
	    s[1] = '\0';
	    strlcat(buf, s, sizeof(buf));
	}
    }
    if(buf[0] != '\0') {
	strlcat(buf, "]", sizeof(buf));
	col = check_column(stderr, col, strlen(buf) + 1, columns);
	col += fprintf(stderr, " %s", buf);
    }

    for (i = 0; i < num_args; ++i) {
	size_t len = 0;

	if (args[i].long_name) {
	    buf[0] = '\0';
	    strlcat(buf, "[--", sizeof(buf));
	    len += 2;
	    if(args[i].type == arg_negative_flag) {
		strlcat(buf, "no-", sizeof(buf));
		len += 3;
	    }
	    strlcat(buf, args[i].long_name, sizeof(buf));
	    len += strlen(args[i].long_name);
	    len += print_arg(buf + strlen(buf), sizeof(buf) - strlen(buf),
			     0, 1, &args[i], i18n);
	    strlcat(buf, "]", sizeof(buf));
	    if(args[i].type == arg_strings)
		strlcat(buf, "...", sizeof(buf));
	    col = check_column(stderr, col, strlen(buf) + 1, columns);
	    col += fprintf(stderr, " %s", buf);
	}
	if (args[i].short_name && !ISFLAG(args[i])) {
	    snprintf(buf, sizeof(buf), "[-%c", args[i].short_name);
	    len += 2;
	    len += print_arg(buf + strlen(buf), sizeof(buf) - strlen(buf),
			     0, 0, &args[i], i18n);
	    strlcat(buf, "]", sizeof(buf));
	    if(args[i].type == arg_strings)
		strlcat(buf, "...", sizeof(buf));
	    col = check_column(stderr, col, strlen(buf) + 1, columns);
	    col += fprintf(stderr, " %s", buf);
	}
	if (args[i].long_name && args[i].short_name)
	    len += 2; /* ", " */
	max_len = max(max_len, len);
    }
    if (extra_string) {
	check_column(stderr, col, strlen(extra_string) + 1, columns);
	fprintf (stderr, " %s\n", extra_string);
    } else
	fprintf (stderr, "\n");
    for (i = 0; i < num_args; ++i) {
	if (args[i].help) {
	    size_t count = 0;

	    if (args[i].short_name) {
		count += fprintf (stderr, "-%c", args[i].short_name);
		print_arg (buf, sizeof(buf), 0, 0, &args[i], i18n);
		count += fprintf(stderr, "%s", buf);
	    }
	    if (args[i].short_name && args[i].long_name)
		count += fprintf (stderr, ", ");
	    if (args[i].long_name) {
		count += fprintf (stderr, "--");
		if (args[i].type == arg_negative_flag)
		    count += fprintf (stderr, "no-");
		count += fprintf (stderr, "%s", args[i].long_name);
		print_arg (buf, sizeof(buf), 0, 1, &args[i], i18n);
		count += fprintf(stderr, "%s", buf);
	    }
	    while(count++ <= max_len)
		putc (' ', stderr);
	    fprintf (stderr, "%s\n", (*i18n)(args[i].help));
	}
    }
}