int
tinytest_main(int c, const char **v, struct testgroup_t *groups)
{
	int i, j, n=0;

#ifdef _WIN32
	const char *sp = strrchr(v[0], '.');
	const char *extension = "";
	if (!sp || stricmp(sp, ".exe"))
		extension = ".exe"; /* Add an exe so CreateProcess will work */
	snprintf(commandname, sizeof(commandname), "%s%s", v[0], extension);
	commandname[MAX_PATH]='\0';
#endif
	for (i=1; i<c; ++i) {
		if (v[i][0] == '-') {
			if (!strcmp(v[i], "--RUNNING-FORKED")) {
				opt_forked = 1;
			} else if (!strcmp(v[i], "--no-fork")) {
				opt_nofork = 1;
			} else if (!strcmp(v[i], "--quiet")) {
				opt_verbosity = -1;
				verbosity_flag = "--quiet";
			} else if (!strcmp(v[i], "--verbose")) {
				opt_verbosity = 2;
				verbosity_flag = "--verbose";
			} else if (!strcmp(v[i], "--terse")) {
				opt_verbosity = 0;
				verbosity_flag = "--terse";
			} else if (!strcmp(v[i], "--help")) {
				usage(groups, 0);
			} else if (!strcmp(v[i], "--list-tests")) {
				usage(groups, 1);
			} else {
				printf("Unknown option %s.  Try --help\n",v[i]);
				return -1;
			}
		} else {
			int r = process_test_option(groups, v[i]);
			if (r<0)
				return -1;
			n += r;
		}
	}
	if (!n)
		tinytest_set_flag_(groups, "..", 1, TT_ENABLED_);

#ifdef _IONBF
	setvbuf(stdout, NULL, _IONBF, 0);
#endif

	++in_tinytest_main;
	for (i=0; groups[i].prefix; ++i)
		for (j=0; groups[i].cases[j].name; ++j)
			if (groups[i].cases[j].flags & TT_ENABLED_)
				testcase_run_one(&groups[i],
						 &groups[i].cases[j]);

	--in_tinytest_main;

	if (opt_verbosity==0)
		puts("");

	if (n_bad)
		printf("%d/%d TESTS FAILED. (%d skipped)\n", n_bad,
		       n_bad+n_ok,n_skipped);
	else if (opt_verbosity >= 1)
		printf("%d tests ok.  (%d skipped)\n", n_ok, n_skipped);

	return (n_bad == 0) ? 0 : 1;
}