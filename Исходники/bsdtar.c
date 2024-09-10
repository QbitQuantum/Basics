int
main(int argc, char **argv)
{
	struct bsdtar		*bsdtar;
	int			 opt;
	char			 possible_help_request;
	char			 buff[16];
	char			 cachedir[PATH_MAX + 1];
	struct passwd		*pws;
	char			*conffile;
	const char		*missingkey;
	time_t			 now;
	size_t 			 i;

	WARNP_INIT;

	/* Use a pointer for consistency. */
	bsdtar = bsdtar_init();

#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure open() function will be used with a binary mode. */
	/* on cygwin, we need something similar, but instead link against */
	/* a special startup object, binmode.o */
	_set_fmode(_O_BINARY);
#endif

	/* Need bsdtar->progname before calling bsdtar_warnc. */
	if (*argv == NULL)
		bsdtar->progname = "tarsnap";
	else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		bsdtar->progname = strrchr(*argv, '\\');
#else
		bsdtar->progname = strrchr(*argv, '/');
#endif
		if (bsdtar->progname != NULL)
			bsdtar->progname++;
		else
			bsdtar->progname = *argv;
	}

	/* We don't have a machine # yet. */
	bsdtar->machinenum = (uint64_t)(-1);

	/* Allocate space for archive names; at most argc of them. */
	if ((bsdtar->tapenames = malloc(argc * sizeof(const char *))) == NULL)
		bsdtar_errc(bsdtar, 1, ENOMEM, "Cannot allocate memory");
	bsdtar->ntapes = 0;

	/* Allocate space for config file names; at most argc of them. */
	if ((bsdtar->configfiles = malloc(argc * sizeof(const char *))) == NULL)
		bsdtar_errc(bsdtar, 1, ENOMEM, "Cannot allocate memory");
	bsdtar->nconfigfiles = 0;

	time(&now);
	bsdtar->creationtime = now;

	if (setlocale(LC_ALL, "") == NULL)
		bsdtar_warnc(bsdtar, 0, "Failed to set default locale");
#if defined(HAVE_NL_LANGINFO) && defined(HAVE_D_MD_ORDER)
	bsdtar->day_first = (*nl_langinfo(D_MD_ORDER) == 'd');
#endif
	possible_help_request = 0;

	/* Initialize key cache.  We don't have any keys yet. */
	if (crypto_keys_init())
		exit(1);

	/*
	 * Make stdout line-buffered (if possible) so that operations such as
	 * "tarsnap --list-archives | more" will run more smoothly.  The only
	 * downside to this is a slight performance cost; but we don't write
	 * enough data to stdout for that to matter.
	 */
	setvbuf(stdout, NULL, _IONBF, 0);

	/*
	 * Unless specified otherwise, we consider ourselves to be
	 * constructing a snapshot of the disk as it is right now.
	 */
	/*
	 * POSIX doesn't provide any mechanism for distinguishing between
	 * an error and the time (time_t)(-1).  Since we only use this to
	 * avoid race conditions in the chunkification cache (i.e., so
	 * that we can determine if a file has been modified since it was
	 * last backed up), and hopefully nobody will have any files with
	 * negative last-modified dates, an error return of (-1) can be
	 * handled the same was as a legitimate return of (-1): Nothing
	 * gets cached.
	 */
	bsdtar->snaptime = time(NULL);

	/* Store original argument vector. */
	bsdtar->argc_orig = argc;
	bsdtar->argv_orig = argv;

	/* Look up the current user and his home directory. */
	if ((pws = getpwuid(geteuid())) != NULL)
		if ((bsdtar->homedir = strdup(pws->pw_dir)) == NULL)
			bsdtar_errc(bsdtar, 1, ENOMEM, "Cannot allocate memory");

	/* Look up uid of current user for future reference */
	bsdtar->user_uid = geteuid();

	/* Default: preserve mod time on extract */
	bsdtar->extract_flags = ARCHIVE_EXTRACT_TIME;

	/* Default: Perform basic security checks. */
	bsdtar->extract_flags |= SECURITY;

	/* Defaults for root user: */
	if (bsdtar_is_privileged(bsdtar)) {
		/* --same-owner */
		bsdtar->extract_flags |= ARCHIVE_EXTRACT_OWNER;
		/* -p */
		bsdtar->extract_flags |= ARCHIVE_EXTRACT_PERM;
		bsdtar->extract_flags |= ARCHIVE_EXTRACT_ACL;
		bsdtar->extract_flags |= ARCHIVE_EXTRACT_XATTR;
		bsdtar->extract_flags |= ARCHIVE_EXTRACT_FFLAGS;
	}

	bsdtar->argv = argv;
	bsdtar->argc = argc;

	/* We gather some options in a 'delayed options queue'. */
	bsdtar->delopt = NULL;
	bsdtar->delopt_tail = &bsdtar->delopt;

	/*
	 * Comments following each option indicate where that option
	 * originated:  SUSv2, POSIX, GNU tar, star, etc.  If there's
	 * no such comment, then I don't know of anyone else who
	 * implements that option.
	 */
	while ((opt = bsdtar_getopt(bsdtar)) != -1) {
		switch (opt) {
		case OPTION_AGGRESSIVE_NETWORKING: /* tarsnap */
			optq_push(bsdtar, "aggressive-networking", NULL);
			break;
		case 'B': /* GNU tar */
			/* libarchive doesn't need this; just ignore it. */
			break;
		case 'C': /* GNU tar */
			if (strlen(bsdtar->optarg) == 0)
				bsdtar_errc(bsdtar, 1, 0,
				    "Meaningless option: -C ''");

			set_chdir(bsdtar, bsdtar->optarg);
			break;
		case 'c': /* SUSv2 */
			set_mode(bsdtar, opt, "-c");
			break;
		case OPTION_CACHEDIR: /* multitar */
			optq_push(bsdtar, "cachedir", bsdtar->optarg);
			break;
		case OPTION_CHECK_LINKS: /* GNU tar */
			bsdtar->option_warn_links = 1;
			break;
		case OPTION_CHECKPOINT_BYTES: /* tarsnap */
			optq_push(bsdtar, "checkpoint-bytes", bsdtar->optarg);
			break;
		case OPTION_CHROOT: /* NetBSD */
			bsdtar->option_chroot = 1;
			break;
		case OPTION_CONFIGFILE:
			bsdtar->configfiles[bsdtar->nconfigfiles++] =
			    bsdtar->optarg;
			break;
		case OPTION_CREATIONTIME: /* tarsnap */
			errno = 0;
			bsdtar->creationtime = strtol(bsdtar->optarg,
			    NULL, 0);
			if ((errno) || (bsdtar->creationtime == 0))
				bsdtar_errc(bsdtar, 1, 0,
				    "Invalid --creationtime argument: %s",
				    bsdtar->optarg);
			break;
		case OPTION_CSV_FILE: /* tarsnap */
			if (bsdtar->option_csv_filename != NULL)
				bsdtar_errc(bsdtar, 1, errno,
				    "Two --csv-file options given.\n");
			if ((bsdtar->option_csv_filename = strdup(
			    bsdtar->optarg)) == NULL)
				bsdtar_errc(bsdtar, 1, errno, "Out of memory");
			break;
		case 'd': /* multitar */
			set_mode(bsdtar, opt, "-d");
			break;
		case OPTION_DISK_PAUSE: /* tarsnap */
			optq_push(bsdtar, "disk-pause", bsdtar->optarg);
			break;
		case OPTION_DRYRUN: /* tarsnap */
			bsdtar->option_dryrun = 1;
			break;
		case OPTION_EXCLUDE: /* GNU tar */
			optq_push(bsdtar, "exclude", bsdtar->optarg);
			break;
		case 'f': /* multitar */
			bsdtar->tapenames[bsdtar->ntapes++] = bsdtar->optarg;
			break;
		case OPTION_FSCK: /* multitar */
			set_mode(bsdtar, opt, "--fsck");
			break;
		case OPTION_FSCK_PRUNE: /* multitar */
			set_mode(bsdtar, opt, "--fsck-prune");
			break;
		case 'H': /* BSD convention */
			bsdtar->symlink_mode = 'H';
			break;
		case 'h': /* Linux Standards Base, gtar; synonym for -L */
			bsdtar->symlink_mode = 'L';
			/* Hack: -h by itself is the "help" command. */
			possible_help_request = 1;
			break;
		case OPTION_HELP: /* GNU tar, others */
			long_help(bsdtar);
			exit(0);
			break;
		case OPTION_HUMANIZE_NUMBERS: /* tarsnap */
			optq_push(bsdtar, "humanize-numbers", NULL);
			break;
		case 'I': /* GNU tar */
			/*
			 * TODO: Allow 'names' to come from an archive,
			 * not just a text file.  Design a good UI for
			 * allowing names and mode/owner to be read
			 * from an archive, with contents coming from
			 * disk.  This can be used to "refresh" an
			 * archive or to design archives with special
			 * permissions without having to create those
			 * permissions on disk.
			 */
			bsdtar->names_from_file = bsdtar->optarg;
			break;
		case OPTION_INCLUDE:
			optq_push(bsdtar, "include", bsdtar->optarg);
			break;
		case OPTION_INSANE_FILESYSTEMS:
			optq_push(bsdtar, "insane-filesystems", NULL);
			break;
		case 'k': /* GNU tar */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_NO_OVERWRITE;
			break;
		case OPTION_KEEP_GOING: /* tarsnap */
			bsdtar->option_keep_going = 1;
			break;
		case OPTION_KEEP_NEWER_FILES: /* GNU tar */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_NO_OVERWRITE_NEWER;
			break;
		case OPTION_KEYFILE: /* tarsnap */
			optq_push(bsdtar, "keyfile", bsdtar->optarg);
			break;
		case 'L': /* BSD convention */
			bsdtar->symlink_mode = 'L';
			break;
	        case 'l': /* SUSv2 and GNU tar beginning with 1.16 */
			/* GNU tar 1.13  used -l for --one-file-system */
			bsdtar->option_warn_links = 1;
			break;
		case OPTION_LIST_ARCHIVES: /* multitar */
			set_mode(bsdtar, opt, "--list-archives");
			break;
		case OPTION_LOWMEM: /* tarsnap */
			optq_push(bsdtar, "lowmem", NULL);
			break;
		case 'm': /* SUSv2 */
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_TIME;
			break;
		case OPTION_MAXBW: /* tarsnap */
			optq_push(bsdtar, "maxbw", bsdtar->optarg);
			break;
		case OPTION_MAXBW_RATE: /* tarsnap */
			optq_push(bsdtar, "maxbw-rate", bsdtar->optarg);
			break;
		case OPTION_MAXBW_RATE_DOWN: /* tarsnap */
			optq_push(bsdtar, "maxbw-rate-down", bsdtar->optarg);
			break;
		case OPTION_MAXBW_RATE_UP: /* tarsnap */
			optq_push(bsdtar, "maxbw-rate-up", bsdtar->optarg);
			break;
		case 'n': /* GNU tar */
			bsdtar->option_no_subdirs = 1;
			break;
	        /*
		 * Selecting files by time:
		 *    --newer-?time='date' Only files newer than 'date'
		 *    --newer-?time-than='file' Only files newer than time
		 *         on specified file (useful for incremental backups)
		 * TODO: Add corresponding "older" options to reverse these.
		 */
		case OPTION_NEWER_CTIME: /* GNU tar */
			bsdtar->newer_ctime_sec = get_date(now, bsdtar->optarg);
			break;
		case OPTION_NEWER_CTIME_THAN:
			{
				struct stat st;
				if (stat(bsdtar->optarg, &st) != 0)
					bsdtar_errc(bsdtar, 1, 0,
					    "Can't open file %s", bsdtar->optarg);
				bsdtar->newer_ctime_sec = st.st_ctime;
				bsdtar->newer_ctime_nsec =
				    ARCHIVE_STAT_CTIME_NANOS(&st);
			}
			break;
		case OPTION_NEWER_MTIME: /* GNU tar */
			bsdtar->newer_mtime_sec = get_date(now, bsdtar->optarg);
			break;
		case OPTION_NEWER_MTIME_THAN:
			{
				struct stat st;
				if (stat(bsdtar->optarg, &st) != 0)
					bsdtar_errc(bsdtar, 1, 0,
					    "Can't open file %s", bsdtar->optarg);
				bsdtar->newer_mtime_sec = st.st_mtime;
				bsdtar->newer_mtime_nsec =
				    ARCHIVE_STAT_MTIME_NANOS(&st);
			}
			break;
		case OPTION_NODUMP: /* star */
			optq_push(bsdtar, "nodump", NULL);
			break;
		case OPTION_NOISY_WARNINGS: /* tarsnap */
			tarsnap_opt_noisy_warnings = 1;
			break;
		case OPTION_NORMALMEM:
			optq_push(bsdtar, "normalmem", NULL);
			break;
		case OPTION_NO_AGGRESSIVE_NETWORKING:
			optq_push(bsdtar, "no-aggressive-networking", NULL);
			break;
		case OPTION_NO_CONFIG_EXCLUDE:
			optq_push(bsdtar, "no-config-exclude", NULL);
			break;
		case OPTION_NO_CONFIG_INCLUDE:
			optq_push(bsdtar, "no-config-include", NULL);
			break;
		case OPTION_NO_DEFAULT_CONFIG:
			bsdtar->option_no_default_config = 1;
			break;
		case OPTION_NO_DISK_PAUSE:
			optq_push(bsdtar, "no-disk-pause", NULL);
			break;
		case OPTION_NO_HUMANIZE_NUMBERS:
			optq_push(bsdtar, "no-humanize-numbers", NULL);
			break;
		case OPTION_NO_INSANE_FILESYSTEMS:
			optq_push(bsdtar, "no-insane-filesystems", NULL);
			break;
		case OPTION_NO_MAXBW:
			optq_push(bsdtar, "no-maxbw", NULL);
			break;
		case OPTION_NO_MAXBW_RATE_DOWN:
			optq_push(bsdtar, "no-maxbw-rate-down", NULL);
			break;
		case OPTION_NO_MAXBW_RATE_UP:
			optq_push(bsdtar, "no-maxbw-rate-up", NULL);
			break;
		case OPTION_NO_NODUMP:
			optq_push(bsdtar, "no-nodump", NULL);
			break;
		case OPTION_NO_PRINT_STATS:
			optq_push(bsdtar, "no-print-stats", NULL);
			break;
		case OPTION_NO_QUIET:
			optq_push(bsdtar, "no-quiet", NULL);
			break;
		case OPTION_NO_RETRY_FOREVER:
			optq_push(bsdtar, "no-retry-forever", NULL);
			break;
		case OPTION_NO_SAME_OWNER: /* GNU tar */
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_OWNER;
			break;
		case OPTION_NO_SAME_PERMISSIONS: /* GNU tar */
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_PERM;
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_ACL;
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_XATTR;
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_FFLAGS;
			break;
		case OPTION_NO_SNAPTIME:
			optq_push(bsdtar, "no-snaptime", NULL);
			break;
		case OPTION_NO_STORE_ATIME:
			optq_push(bsdtar, "no-store-atime", NULL);
			break;
		case OPTION_NO_TOTALS:
			optq_push(bsdtar, "no-totals", NULL);
			break;
		case OPTION_NUKE: /* tarsnap */
			set_mode(bsdtar, opt, "--nuke");
			break;
		case OPTION_NULL: /* GNU tar */
			bsdtar->option_null++;
			break;
		case OPTION_NUMERIC_OWNER: /* GNU tar */
			bsdtar->option_numeric_owner++;
			break;
		case 'O': /* GNU tar */
			bsdtar->option_stdout = 1;
			break;
		case 'o':
			bsdtar->option_no_owner = 1;
			bsdtar->extract_flags &= ~ARCHIVE_EXTRACT_OWNER;
			break;
		case OPTION_ONE_FILE_SYSTEM: /* GNU tar */
			bsdtar->option_dont_traverse_mounts = 1;
			break;
		case 'P': /* GNU tar */
			bsdtar->extract_flags &= ~SECURITY;
			bsdtar->option_absolute_paths = 1;
			break;
		case 'p': /* GNU tar, star */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_PERM;
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_ACL;
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_XATTR;
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_FFLAGS;
			break;
		case OPTION_PRINT_STATS: /* multitar */
			bsdtar->option_print_stats = 1;
			break;
		case 'q': /* FreeBSD GNU tar --fast-read, NetBSD -q */
			bsdtar->option_fast_read = 1;
			break;
		case OPTION_QUIET:
			optq_push(bsdtar, "quiet", NULL);
			break;
		case 'r': /* multitar */
			set_mode(bsdtar, opt, "-r");
			break;
		case OPTION_RECOVER:
			set_mode(bsdtar, opt, "--recover");
			break;
		case OPTION_RETRY_FOREVER:
			optq_push(bsdtar, "retry-forever", NULL);
			break;
		case OPTION_SNAPTIME: /* multitar */
			optq_push(bsdtar, "snaptime", bsdtar->optarg);
			break;
		case OPTION_STORE_ATIME: /* multitar */
			optq_push(bsdtar, "store-atime", NULL);
			break;
		case 'S': /* NetBSD pax-as-tar */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_SPARSE;
			break;
		case 's': /* NetBSD pax-as-tar */
#if HAVE_REGEX_H
			add_substitution(bsdtar, bsdtar->optarg);
#else
			bsdtar_warnc(bsdtar, 0,
			    "-s is not supported by this version of tarsnap");
			usage(bsdtar);
#endif
			break;
		case OPTION_SAME_OWNER: /* GNU tar */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_OWNER;
			break;
		case OPTION_STRIP_COMPONENTS: /* GNU tar 1.15 */
			errno = 0;
			bsdtar->strip_components = strtol(bsdtar->optarg,
			    NULL, 0);
			if (errno)
				bsdtar_errc(bsdtar, 1, 0,
				    "Invalid --strip-components argument: %s",
				    bsdtar->optarg);
			break;
		case 'T': /* GNU tar */
			bsdtar->names_from_file = bsdtar->optarg;
			break;
		case 't': /* SUSv2 */
			set_mode(bsdtar, opt, "-t");
			bsdtar->verbose++;
			break;
		case OPTION_TOTALS: /* GNU tar */
			optq_push(bsdtar, "totals", NULL);
			break;
		case 'U': /* GNU tar */
			bsdtar->extract_flags |= ARCHIVE_EXTRACT_UNLINK;
			bsdtar->option_unlink_first = 1;
			break;
		case 'v': /* SUSv2 */
			bsdtar->verbose++;
			break;
		case OPTION_VERSION: /* GNU convention */
			version();
			break;
		case OPTION_VERYLOWMEM: /* tarsnap */
			optq_push(bsdtar, "verylowmem", NULL);
			break;
#if 0
		/*
		 * The -W longopt feature is handled inside of
		 * bsdtar_getopt(), so -W is not available here.
		 */
		case 'W': /* Obscure GNU convention. */
			break;
#endif
		case 'w': /* SUSv2 */
			bsdtar->option_interactive = 1;
			break;
		case 'X': /* GNU tar */
			if (exclude_from_file(bsdtar, bsdtar->optarg))
				bsdtar_errc(bsdtar, 1, 0,
				    "failed to process exclusions from file %s",
				    bsdtar->optarg);
			break;
		case 'x': /* SUSv2 */
			set_mode(bsdtar, opt, "-x");
			break;
		default:
			usage(bsdtar);
		}
	}

	/*
	 * Sanity-check options.
	 */

	/*
	 * If --print-stats was specified but no mode was set, then
	 * --print-stats *is* the mode.
	 */
	if ((bsdtar->mode == '\0') && (bsdtar->option_print_stats == 1))
		set_mode(bsdtar, OPTION_PRINT_STATS, "--print-stats");

	/* If no "real" mode was specified, treat -h as --help. */
	if ((bsdtar->mode == '\0') && possible_help_request) {
		long_help(bsdtar);
		exit(0);
	}

	/*
	 * If we're doing a dry run and the user hasn't specified an archive
	 * name via -f, use a fake name.  This will result in the statistics
	 * printed by --print-stats being a few bytes off, since the archive
	 * name is included in the metadata block... but we're going to be a
	 * few bytes off anyway since the command line, including "--dry-run"
	 * is included in the metadata.
	 */
	if (bsdtar->option_dryrun && (bsdtar->ntapes == 0))
		bsdtar->tapenames[bsdtar->ntapes++] = "(dry-run)";

	/* At this point we must have a mode set. */
	if (bsdtar->mode == '\0')
		bsdtar_errc(bsdtar, 1, 0,
		    "Must specify one of -c, -d, -r, -t, -x,"
		    " --list-archives, --print-stats,"
		    " --fsck, --fsck-prune, or --nuke");

	/* Process "delayed" command-line options which we queued earlier. */
	while (bsdtar->delopt != NULL) {
		dooption(bsdtar, bsdtar->delopt->opt_name,
		    bsdtar->delopt->opt_arg, 0);
		optq_pop(bsdtar);
	}

	/* Process config files passed on the command line. */
	for (i = 0; i < bsdtar->nconfigfiles; i++)
		configfile(bsdtar, bsdtar->configfiles[i]);

	/* If we do not have --no-default-config, process default configs. */
	if (bsdtar->option_no_default_config == 0) {
		/* Process options from ~/.tarsnaprc. */
		if (bsdtar->homedir != NULL) {
			if (asprintf(&conffile, "%s/.tarsnaprc",
			    bsdtar->homedir) == -1)
				bsdtar_errc(bsdtar, 1, errno, "No memory");

			configfile(bsdtar, conffile);

			/* Free string allocated by asprintf. */
			free(conffile);
		}

		/* Process options from system-wide tarsnap.conf. */
		configfile(bsdtar, ETC_TARSNAP_CONF);
	}

	/* Continue with more sanity-checking. */
	if ((bsdtar->ntapes == 0) &&
	    (bsdtar->mode != OPTION_PRINT_STATS &&
	     bsdtar->mode != OPTION_LIST_ARCHIVES &&
	     bsdtar->mode != OPTION_RECOVER &&
	     bsdtar->mode != OPTION_FSCK &&
	     bsdtar->mode != OPTION_FSCK_PRUNE &&
	     bsdtar->mode != OPTION_NUKE))
		bsdtar_errc(bsdtar, 1, 0,
		    "Archive name must be specified");
	if ((bsdtar->ntapes > 1) &&
	    (bsdtar->mode != OPTION_PRINT_STATS &&
	     bsdtar->mode != 'd'))
		bsdtar_errc(bsdtar, 1, 0,
		    "Option -f may only be specified once in mode %s",
		    bsdtar->modestr);
	if ((bsdtar->mode == 'c') &&
	    (strlen(bsdtar->tapenames[0]) > 1023))
		bsdtar_errc(bsdtar, 1, 0,
		    "Cannot create an archive with a name > 1023 characters");
	if ((bsdtar->mode == 'c') &&
	    (strlen(bsdtar->tapenames[0]) == 0))
		bsdtar_errc(bsdtar, 1, 0,
		    "Cannot create an archive with an empty name");
	if ((bsdtar->cachedir == NULL) &&
	    (((bsdtar->mode == 'c') && (!bsdtar->option_dryrun)) ||
	     bsdtar->mode == 'd' ||
	     bsdtar->mode == OPTION_RECOVER ||
	     bsdtar->mode == OPTION_FSCK ||
	     bsdtar->mode == OPTION_FSCK_PRUNE ||
	     bsdtar->mode == OPTION_PRINT_STATS))
		bsdtar_errc(bsdtar, 1, 0,
		    "Cache directory must be specified for %s",
		    bsdtar->modestr);
	if (tarsnap_opt_aggressive_networking != 0) {
		if ((bsdtar->bwlimit_rate_up != 0) ||
		    (bsdtar->bwlimit_rate_down != 0)) {
			bsdtar_warnc(bsdtar, 0,
			    "--aggressive-networking is incompatible with"
			    " --maxbw-rate options;\n"
			    "         disabling --aggressive-networking");
			tarsnap_opt_aggressive_networking = 0;
		}
	}

	/*
	 * The -f option doesn't make sense for --list-archives, --fsck,
	 * --fsck-prune, or --nuke.
	 */
	if ((bsdtar->ntapes > 0) &&
	    (bsdtar->mode != OPTION_PRINT_STATS))
		only_mode(bsdtar, "-f", "cxtdr");

	/*
	 * These options don't make sense for the "delete" and "convert to
	 * tar" modes.
	 */
	if (bsdtar->pending_chdir)
		only_mode(bsdtar, "-C", "cxt");
	if (bsdtar->names_from_file)
		only_mode(bsdtar, "-T", "cxt");
	if (bsdtar->newer_ctime_sec || bsdtar->newer_ctime_nsec)
		only_mode(bsdtar, "--newer", "cxt");
	if (bsdtar->newer_mtime_sec || bsdtar->newer_mtime_nsec)
		only_mode(bsdtar, "--newer-mtime", "cxt");
	if (bsdtar->option_absolute_paths)
		only_mode(bsdtar, "-P", "cxt");
	if (bsdtar->option_null)
		only_mode(bsdtar, "--null", "cxt");

	/* Check options only permitted in certain modes. */
	if (bsdtar->option_dont_traverse_mounts)
		only_mode(bsdtar, "--one-file-system", "c");
	if (bsdtar->option_fast_read)
		only_mode(bsdtar, "--fast-read", "xt");
	if (bsdtar->option_no_subdirs)
		only_mode(bsdtar, "-n", "c");
	if (bsdtar->option_no_owner)
		only_mode(bsdtar, "-o", "x");
	if (bsdtar->option_stdout)
		only_mode(bsdtar, "-O", "xt");
	if (bsdtar->option_unlink_first)
		only_mode(bsdtar, "-U", "x");
	if (bsdtar->option_warn_links)
		only_mode(bsdtar, "--check-links", "c");
	if (bsdtar->option_dryrun)
		only_mode(bsdtar, "--dry-run", "c");

	/* Check other parameters only permitted in certain modes. */
	if (bsdtar->symlink_mode != '\0') {
		strcpy(buff, "-?");
		buff[1] = bsdtar->symlink_mode;
		only_mode(bsdtar, buff, "c");
	}
	if (bsdtar->strip_components != 0)
		only_mode(bsdtar, "--strip-components", "xt");

	/*
	 * If the keyfile in the config file is invalid but we're doing a
	 * dryrun, continue anyway (and don't use a cachedir).
	 */
	if (bsdtar->config_file_keyfile_failed && bsdtar->option_dryrun &&
	    bsdtar->cachedir != NULL) {
		bsdtar_warnc(bsdtar, 0,
		    "Ignoring cachedir due to missing or invalid "
		    "keyfile in config file.");
		free(bsdtar->cachedir);
		bsdtar->cachedir = NULL;
	}

	/*
	 * Canonicalize the path to the cache directories.  This is
	 * necessary since the tar code can change directories.
	 */
	if (bsdtar->cachedir != NULL) {
		build_dir(bsdtar, bsdtar->cachedir, "--cachedir");
		if (realpath(bsdtar->cachedir, cachedir) == NULL)
			bsdtar_errc(bsdtar, 1, errno, "realpath(%s)",
			    bsdtar->cachedir);
		free(bsdtar->cachedir);
		if ((bsdtar->cachedir = strdup(cachedir)) == NULL)
			bsdtar_errc(bsdtar, 1, errno, "Out of memory");
	}

	/* If we're running --fsck, figure out which key to use. */
	if (bsdtar->mode == OPTION_FSCK) {
		if (crypto_keys_missing(CRYPTO_KEYMASK_AUTH_PUT) == NULL)
			bsdtar->mode = OPTION_FSCK_WRITE;
		else if (crypto_keys_missing(CRYPTO_KEYMASK_AUTH_DELETE) == NULL)
			bsdtar->mode = OPTION_FSCK_DELETE;
		else
			bsdtar_errc(bsdtar, 1, 0,
			    "The write or delete authorization key is"
			    " required for --fsck but is not available");
	}

	/* If we're running --recover, figure out which key to use. */
	if (bsdtar->mode == OPTION_RECOVER) {
		if (crypto_keys_missing(CRYPTO_KEYMASK_AUTH_PUT) == NULL)
			bsdtar->mode = OPTION_RECOVER_WRITE;
		else if (crypto_keys_missing(CRYPTO_KEYMASK_AUTH_DELETE) == NULL)
			bsdtar->mode = OPTION_RECOVER_DELETE;
		else
			bsdtar_errc(bsdtar, 1, 0,
			    "The write or delete authorization key is"
			    " required for --recover but is not available");
	}

	/* Make sure we have whatever keys we're going to need. */
	if (bsdtar->have_keys == 0) {
		if (!bsdtar->option_dryrun) {
			bsdtar_errc(bsdtar, 1, 0,
			    "Keys must be provided via --keyfile option");
		} else {
			if (bsdtar->cachedir != NULL) {
				bsdtar_errc(bsdtar, 1, 0,
				    "Option mismatch for --dry-run: cachedir"
				    " specified but no keyfile");
			}
			if (crypto_keys_generate(CRYPTO_KEYMASK_USER))
				bsdtar_errc(bsdtar, 1, 0,
				    "Error generating keys");
			if (bsdtar->option_print_stats)
				bsdtar_warnc(bsdtar, 0,
				    "Performing dry-run archival without keys\n"
				    "         (sizes may be slightly "
				    "inaccurate)");
		}
	}

	missingkey = NULL;
	switch (bsdtar->mode) {
	case 'c':
		if (argv_has_archive_directive(bsdtar))
			missingkey = crypto_keys_missing(CRYPTO_KEYMASK_WRITE | CRYPTO_KEYMASK_READ);
		else
			missingkey = crypto_keys_missing(CRYPTO_KEYMASK_WRITE);
		break;
	case OPTION_RECOVER_WRITE:
		missingkey = crypto_keys_missing(CRYPTO_KEYMASK_WRITE);
		break;
	case 'd':
	case OPTION_FSCK_PRUNE:
	case OPTION_FSCK_DELETE:
		missingkey = crypto_keys_missing(CRYPTO_KEYMASK_READ |
		    CRYPTO_KEYMASK_AUTH_DELETE);
		break;
	case OPTION_FSCK_WRITE:
		missingkey = crypto_keys_missing(CRYPTO_KEYMASK_READ |
		    CRYPTO_KEYMASK_AUTH_PUT);
		break;
	case OPTION_NUKE:
	case OPTION_RECOVER_DELETE:
		missingkey = crypto_keys_missing(CRYPTO_KEYMASK_AUTH_DELETE);
		break;
	case OPTION_PRINT_STATS:
		/* We don't need keys for printing global stats. */
		if (bsdtar->ntapes == 0)
			break;

		/* FALLTHROUGH */
	case OPTION_LIST_ARCHIVES:
	case 'r':
	case 't':
	case 'x':
		missingkey = crypto_keys_missing(CRYPTO_KEYMASK_READ);
		break;
	}
	if (missingkey != NULL)
		bsdtar_errc(bsdtar, 1, 0,
		    "The %s key is required for %s but is not available",
		    missingkey, bsdtar->modestr);

	/* Tell the network layer how much bandwidth to use. */
	if (bsdtar->bwlimit_rate_up == 0)
		bsdtar->bwlimit_rate_up = 1000000000.;
	if (bsdtar->bwlimit_rate_down == 0)
		bsdtar->bwlimit_rate_down = 1000000000.;
	network_bwlimit(bsdtar->bwlimit_rate_down, bsdtar->bwlimit_rate_up);

	/* Perform the requested operation. */
	switch(bsdtar->mode) {
	case 'c':
		tarsnap_mode_c(bsdtar);
		break;
	case 'd':
		tarsnap_mode_d(bsdtar);
		break;
	case OPTION_FSCK_DELETE:
		tarsnap_mode_fsck(bsdtar, 0, 1);
		break;
	case OPTION_FSCK_PRUNE:
		tarsnap_mode_fsck(bsdtar, 1, 1);
		break;
	case OPTION_FSCK_WRITE:
		tarsnap_mode_fsck(bsdtar, 0, 0);
		break;
	case OPTION_PRINT_STATS:
		tarsnap_mode_print_stats(bsdtar);
		break;
	case OPTION_RECOVER_DELETE:
		tarsnap_mode_recover(bsdtar, 1);
		break;
	case OPTION_RECOVER_WRITE:
		tarsnap_mode_recover(bsdtar, 0);
		break;
	case OPTION_LIST_ARCHIVES:
		tarsnap_mode_list_archives(bsdtar);
		break;
	case OPTION_NUKE:
		tarsnap_mode_nuke(bsdtar);
		break;
	case 'r':
		tarsnap_mode_r(bsdtar);
		break;
	case 't':
		tarsnap_mode_t(bsdtar);
		break;
	case 'x':
		tarsnap_mode_x(bsdtar);
		break;
	}

#ifdef DEBUG_SELECTSTATS
	double N, mu, va, max;

	network_getselectstats(&N, &mu, &va, &max);
	fprintf(stderr, "Time-between-select-calls statistics:\n");
	fprintf(stderr, "N = %6g   mu = %12g ms  "
	    "va = %12g ms^2  max = %12g ms\n",
	    N, mu * 1000, va * 1000000, max * 1000);
#endif

#ifdef PROFILE
	/*
	 * If we're compiling with profiling turned on, chdir to a directory
	 * into which we're likely to be able to write to before exiting.
	 */
	if (bsdtar->cachedir != NULL)
		chdir(cachedir);
#endif

	if (bsdtar->return_value != 0)
		bsdtar_warnc(bsdtar, 0,
		    "Error exit delayed from previous errors.");
	return (bsdtar->return_value);
}