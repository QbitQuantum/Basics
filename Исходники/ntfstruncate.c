/**
 * parse_options
 */
static void parse_options(int argc, char *argv[])
{
	long long ll;
	char *s, *s2;
	int c;

	if (argc && *argv)
		EXEC_NAME = *argv;
	fprintf(stderr, "%s v%s (libntfs-3g)\n", EXEC_NAME, VERSION);
	while ((c = getopt(argc, argv, "fh?nqvVl")) != EOF)
		switch (c) {
		case 'f':
			opts.force = 1;
			break;
		case 'n':
			opts.no_action = 1;
			break;
		case 'q':
			opts.quiet = 1;
			ntfs_log_clear_levels(NTFS_LOG_LEVEL_QUIET);
			break;
		case 'v':
			opts.verbose++;
			ntfs_log_set_levels(NTFS_LOG_LEVEL_VERBOSE);
			break;
		case 'V':
			/* Version number already printed, so just exit. */
			exit(0);
		case 'l':
			copyright();
			license();
			exit(0);
		case 'h':
		case '?':
		default:
			usage();
		}
	if (optind == argc)
		usage();

	if (opts.verbose > 1)
		ntfs_log_set_levels(NTFS_LOG_LEVEL_DEBUG | NTFS_LOG_LEVEL_TRACE |
			NTFS_LOG_LEVEL_VERBOSE | NTFS_LOG_LEVEL_QUIET);

	/* Get the device. */
	dev_name = argv[optind++];
	ntfs_log_verbose("device name = %s\n", dev_name);

	if (optind == argc)
		usage();

	/* Get the inode. */
	ll = strtoll(argv[optind++], &s, 0);
	if (*s || !ll || (ll >= LLONG_MAX && errno == ERANGE))
		err_exit("Invalid inode number: %s\n", argv[optind - 1]);
	inode = ll;
	ntfs_log_verbose("inode = %lli\n", (long long)inode);

	if (optind == argc)
		usage();

	/* Get the attribute type, if specified. */
	s = argv[optind++];
	if (optind == argc) {
		attr_type = AT_DATA;
		attr_name = AT_UNNAMED;
		attr_name_len = 0;
	} else {
		unsigned long ul;

		ul = strtoul(s, &s2, 0);
		if (*s2 || !ul || (ul >= ULONG_MAX && errno == ERANGE))
			err_exit("Invalid attribute type %s: %s\n", s,
					strerror(errno));
		attr_type = ul;

		/* Get the attribute name, if specified. */
		s = argv[optind++];
		if (optind != argc) {
			/* Convert the string to little endian Unicode. */
			attr_name_len = ntfs_mbstoucs(s, &attr_name);
			if ((int)attr_name_len < 0)
				err_exit("Invalid attribute name \"%s\": %s\n",
						s, strerror(errno));

			/* Keep hold of the original string. */
			s2 = s;

			s = argv[optind++];
			if (optind != argc)
				usage();
		} else {
			attr_name = AT_UNNAMED;
			attr_name_len = 0;
		}
	}
	ntfs_log_verbose("attribute type = 0x%x\n", (unsigned int)attr_type);
	if (attr_name == AT_UNNAMED)
		ntfs_log_verbose("attribute name = \"\" (UNNAMED)\n");
	else
		ntfs_log_verbose("attribute name = \"%s\" (length %u Unicode "
				"characters)\n", s2,
				(unsigned int)attr_name_len);

	/* Get the new length. */
	ll = strtoll(s, &s2, 0);
	if (*s2 || ll < 0 || (ll >= LLONG_MAX && errno == ERANGE))
		err_exit("Invalid new length: %s\n", s);
	new_len = ll;
	ntfs_log_verbose("new length = %lli\n", (long long)new_len);
}