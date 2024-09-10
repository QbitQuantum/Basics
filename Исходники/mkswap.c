int
main(int argc, char ** argv) {
	struct stat statbuf;
	struct swap_header_v1_2 *hdr;
	int i;
	unsigned long long maxpages;
	unsigned long long goodpages;
	unsigned long long sz;
	off_t offset;
	int force = 0;
	int version = 1;
	char *block_count = 0;
	char *pp;
	char *opt_label = NULL;
	unsigned char *uuid = NULL;
#ifdef HAVE_LIBUUID
	const char *opt_uuid = NULL;
	uuid_t uuid_dat;
#endif

	program_name = (argc && *argv) ? argv[0] : "mkswap";
	if ((pp = strrchr(program_name, '/')) != NULL)
		program_name = pp+1;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	if (argc == 2 &&
	    (!strcmp(argv[1], "-V") || !strcmp(argv[1], "--version"))) {
		printf(_("%s (%s)\n"), program_name, PACKAGE_STRING);
		exit(0);
	}

	for (i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'c':
					check=1;
					break;
				case 'f':
					force=1;
					break;
				case 'p':
					pp = argv[i]+2;
					if (!*pp && i+1 < argc)
						pp = argv[++i];
					if (isnzdigit(*pp))
						user_pagesize = atoi(pp);
					else
						usage();
					break;
			        case 'L':
					pp = argv[i]+2;
					if (!*pp && i+1 < argc)
						pp = argv[++i];
					opt_label = pp;
				        break;
				case 'v':
					version = atoi(argv[i]+2);
					break;
				case 'U':
#ifdef HAVE_LIBUUID
					opt_uuid = argv[i]+2;
					if (!*opt_uuid && i+1 < argc)
						opt_uuid = argv[++i];
#else
					fprintf(stderr, _("%1$s: warning: ignore -U (UUIDs are unsupported by %1$s)\n"),
						program_name);
#endif
					break;
				default:
					usage();
			}
		} else if (!device_name) {
			device_name = argv[i];
		} else if (!block_count) {
			block_count = argv[i];
		} else
			usage();
	}

	if (version != 1) {
		fprintf(stderr, _("%s: does not support swapspace version %d.\n"),
			program_name, version);
		exit(EXIT_FAILURE);
	}

#ifdef HAVE_LIBUUID
	if(opt_uuid) {
		if (uuid_parse(opt_uuid, uuid_dat) != 0)
			die(_("error: UUID parsing failed"));
	} else
		uuid_generate(uuid_dat);
	uuid = uuid_dat;
#endif

	init_signature_page();	/* get pagesize */
	atexit(deinit_signature_page);

	if (!device_name) {
		fprintf(stderr,
			_("%s: error: Nowhere to set up swap on?\n"),
			program_name);
		usage();
	}
	if (block_count) {
		/* this silly user specified the number of blocks explicitly */
		char *tmp = NULL;
		long long blks;

		errno = 0;
		blks = strtoll(block_count, &tmp, 0);
		if ((tmp == block_count) ||
		    (tmp && *tmp) ||
		    (errno != 0 && (blks == LLONG_MAX || blks == LLONG_MIN)) ||
		    blks < 0)
			usage();

		PAGES = blks / (pagesize / 1024);
	}
	sz = get_size(device_name);
	if (!PAGES) {
		PAGES = sz;
	} else if (PAGES > sz && !force) {
		fprintf(stderr,
			_("%s: error: "
			  "size %llu KiB is larger than device size %llu KiB\n"),
			program_name,
			PAGES*(pagesize/1024), sz*(pagesize/1024));
		exit(1);
	}

	if (PAGES < MIN_GOODPAGES) {
		fprintf(stderr,
			_("%s: error: swap area needs to be at least %ld KiB\n"),
			program_name, (long)(MIN_GOODPAGES * pagesize/1024));
		usage();
	}

#ifdef __linux__
	if (get_linux_version() >= KERNEL_VERSION(2,3,4))
		maxpages = UINT_MAX + 1ULL;
	else if (get_linux_version() >= KERNEL_VERSION(2,2,1))
		maxpages = V1_MAX_PAGES;
	else
#endif
		maxpages = V1_OLD_MAX_PAGES;

	if (PAGES > maxpages) {
		PAGES = maxpages;
		fprintf(stderr,
			_("%s: warning: truncating swap area to %llu KiB\n"),
			program_name, PAGES * pagesize / 1024);
	}

	if (stat(device_name, &statbuf) < 0) {
		perror(device_name);
		exit(EXIT_FAILURE);
	}
	if (S_ISBLK(statbuf.st_mode))
		DEV = open(device_name, O_RDWR | O_EXCL);
	else
		DEV = open(device_name, O_RDWR);

	if (DEV < 0) {
		perror(device_name);
		exit(1);
	}

	/* Want a block device. Probably not /dev/hda or /dev/hdb. */
	if (!S_ISBLK(statbuf.st_mode))
		check=0;
	else if (statbuf.st_rdev == 0x0300 || statbuf.st_rdev == 0x0340) {
		fprintf(stderr,
			_("%s: error: "
			  "will not try to make swapdevice on '%s'\n"),
			program_name, device_name);
		exit(1);
	} else if (check_mount()) {
		fprintf(stderr,
			_("%s: error: "
			  "%s is mounted; will not make swapspace.\n"),
			program_name, device_name);
		exit(1);
	}

	if (check)
		check_blocks();

	zap_bootbits(DEV, device_name, force, S_ISBLK(statbuf.st_mode));

	hdr = (struct swap_header_v1_2 *) signature_page;
	hdr->version = 1;
	hdr->last_page = PAGES - 1;
	hdr->nr_badpages = badpages;

	if (badpages > PAGES - MIN_GOODPAGES)
		die(_("Unable to set up swap-space: unreadable"));

	goodpages = PAGES - badpages - 1;
	printf(_("Setting up swapspace version 1, size = %llu KiB\n"),
		goodpages * pagesize / 1024);

	write_signature("SWAPSPACE2");
	write_uuid_and_label(uuid, opt_label);

	offset = 1024;
	if (lseek(DEV, offset, SEEK_SET) != offset)
		die(_("unable to rewind swap-device"));
	if (write_all(DEV, (char *) signature_page + offset,
				    pagesize - offset) == -1) {
		fprintf(stderr, _("%s: %s: unable to write signature page: %s"),
			program_name, device_name, strerror(errno));
		exit(1);
	}

	/*
	 * A subsequent swapon() will fail if the signature
	 * is not actually on disk. (This is a kernel bug.)
	 */
#ifdef HAVE_FSYNC
	if (fsync(DEV))
		 die(_("fsync failed"));
#endif

#ifdef HAVE_LIBSELINUX
	if (S_ISREG(statbuf.st_mode) && is_selinux_enabled() > 0) {
		security_context_t context_string;
		security_context_t oldcontext;
		context_t newcontext;

		if (fgetfilecon(DEV, &oldcontext) < 0) {
			if (errno != ENODATA) {
				fprintf(stderr, _("%s: %s: unable to obtain selinux file label: %s\n"),
						program_name, device_name,
						strerror(errno));
				exit(1);
			}
			if (matchpathcon(device_name, statbuf.st_mode, &oldcontext))
				die(_("unable to matchpathcon()"));
		}
		if (!(newcontext = context_new(oldcontext)))
			die(_("unable to create new selinux context"));
		if (context_type_set(newcontext, SELINUX_SWAPFILE_TYPE))
			die(_("couldn't compute selinux context"));

		context_string = context_str(newcontext);

		if (strcmp(context_string, oldcontext)!=0) {
			if (fsetfilecon(DEV, context_string)) {
				fprintf(stderr, _("%s: unable to relabel %s to %s: %s\n"),
						program_name, device_name,
						context_string,
						strerror(errno));
				exit(1);
			}
		}
		context_free(newcontext);
		freecon(oldcontext);
	}
#endif
	return 0;
}