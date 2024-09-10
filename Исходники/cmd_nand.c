static int raw_access(nand_info_t *nand, ulong addr, loff_t off, ulong count,
			int read)
{
	int ret = 0;

	while (count--) {
		/* Raw access */
		mtd_oob_ops_t ops = {
			.datbuf = (u8 *)addr,
			.oobbuf = ((u8 *)addr) + nand->writesize,
			.len = nand->writesize,
			.ooblen = nand->oobsize,
			.mode = MTD_OOB_RAW
		};

		if (read)
			ret = nand->read_oob(nand, off, &ops);
		else
			ret = nand->write_oob(nand, off, &ops);

		if (ret) {
			printf("%s: error at offset %llx, ret %d\n",
				__func__, (long long)off, ret);
			break;
		}

		addr += nand->writesize + nand->oobsize;
		off += nand->writesize;
	}

	return ret;
}

int do_nand(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	int i, ret = 0;
	ulong addr;
	loff_t off, size;
	char *cmd, *s;
	nand_info_t *nand;
#ifdef CONFIG_SYS_NAND_QUIET
	int quiet = CONFIG_SYS_NAND_QUIET;
#else
	int quiet = 0;
#endif
	const char *quiet_str = getenv("quiet");
	int dev = nand_curr_device;
	int repeat = flag & CMD_FLAG_REPEAT;

	/* at least two arguments please */
	if (argc < 2)
		goto usage;

	if (quiet_str)
		quiet = simple_strtoul(quiet_str, NULL, 0) != 0;

	cmd = argv[1];

	/* Only "dump" is repeatable. */
	if (repeat && strcmp(cmd, "dump"))
		return 0;

	if (strcmp(cmd, "info") == 0) {

		putc('\n');
		for (i = 0; i < CONFIG_SYS_MAX_NAND_DEVICE; i++) {
			if (nand_info[i].name)
				nand_print_and_set_info(i);
		}
		return 0;
	}

	if (strcmp(cmd, "device") == 0) {
		if (argc < 3) {
			putc('\n');
			if (dev < 0 || dev >= CONFIG_SYS_MAX_NAND_DEVICE)
				puts("no devices available\n");
			else
				nand_print_and_set_info(dev);
			return 0;
		}

		dev = (int)simple_strtoul(argv[2], NULL, 10);
		set_dev(dev);

		return 0;
	}

#ifdef CONFIG_ENV_OFFSET_OOB
	/* this command operates only on the first nand device */
	if (strcmp(cmd, "env.oob") == 0)
		return do_nand_env_oob(cmdtp, argc - 1, argv + 1);
#endif

	/* The following commands operate on the current device, unless
	 * overridden by a partition specifier.  Note that if somehow the
	 * current device is invalid, it will have to be changed to a valid
	 * one before these commands can run, even if a partition specifier
	 * for another device is to be used.
	 */
	if (dev < 0 || dev >= CONFIG_SYS_MAX_NAND_DEVICE ||
	    !nand_info[dev].name) {
		puts("\nno devices available\n");
		return 1;
	}
	nand = &nand_info[dev];

	if (strcmp(cmd, "bad") == 0) {
		printf("\nDevice %d bad blocks:\n", dev);
		for (off = 0; off < nand->size; off += nand->erasesize)
			if (nand_block_isbad(nand, off))
				printf("  %08llx\n", (unsigned long long)off);
		return 0;
	}

	/*
	 * Syntax is:
	 *   0    1     2       3    4
	 *   nand erase [clean] [off size]
	 */
	if (strncmp(cmd, "erase", 5) == 0 || strncmp(cmd, "scrub", 5) == 0) {
		nand_erase_options_t opts;
		/* "clean" at index 2 means request to write cleanmarker */
		int clean = argc > 2 && !strcmp("clean", argv[2]);
		int scrub_yes = argc > 2 && !strcmp("-y", argv[2]);
		int o = (clean || scrub_yes) ? 3 : 2;
		int scrub = !strncmp(cmd, "scrub", 5);
		int spread = 0;
		int args = 2;
		const char *scrub_warn =
			"Warning: "
			"scrub option will erase all factory set bad blocks!\n"
			"         "
			"There is no reliable way to recover them.\n"
			"         "
			"Use this command only for testing purposes if you\n"
			"         "
			"are sure of what you are doing!\n"
			"\nReally scrub this NAND flash? <y/N>\n";

		if (cmd[5] != 0) {
			if (!strcmp(&cmd[5], ".spread")) {
				spread = 1;
			} else if (!strcmp(&cmd[5], ".part")) {
				args = 1;
			} else if (!strcmp(&cmd[5], ".chip")) {
				args = 0;
			} else {
				goto usage;
			}
		}

		/*
		 * Don't allow missing arguments to cause full chip/partition
		 * erases -- easy to do accidentally, e.g. with a misspelled
		 * variable name.
		 */
		if (argc != o + args)
			goto usage;

		printf("\nNAND %s: ", cmd);
		/* skip first two or three arguments, look for offset and size */
		if (arg_off_size(argc - o, argv + o, &dev, &off, &size) != 0)
			return 1;

		nand = &nand_info[dev];

		memset(&opts, 0, sizeof(opts));
		opts.offset = off;
		opts.length = size;
		opts.jffs2  = clean;
		opts.quiet  = quiet;
		opts.spread = spread;

		if (scrub) {
			if (!scrub_yes)
				puts(scrub_warn);

			if (scrub_yes)
				opts.scrub = 1;
			else if (getc() == 'y') {
				puts("y");
				if (getc() == '\r')
					opts.scrub = 1;
				else {
					puts("scrub aborted\n");
					return -1;
				}
			} else {
				puts("scrub aborted\n");
				return -1;
			}
		}
		ret = nand_erase_opts(nand, &opts);
		printf("%s\n", ret ? "ERROR" : "OK");

		return ret == 0 ? 0 : 1;
	}

	if (strncmp(cmd, "dump", 4) == 0) {
		if (argc < 3)
			goto usage;

		off = (int)simple_strtoul(argv[2], NULL, 16);
		ret = nand_dump(nand, off, !strcmp(&cmd[4], ".oob"), repeat);

		return ret == 0 ? 1 : 0;
	}

	if (strncmp(cmd, "read", 4) == 0 || strncmp(cmd, "write", 5) == 0) {
		size_t rwsize;
		ulong pagecount = 1;
		int read;
		int raw;

		if (argc < 4)
			goto usage;

		addr = (ulong)simple_strtoul(argv[2], NULL, 16);

		read = strncmp(cmd, "read", 4) == 0; /* 1 = read, 0 = write */
		printf("\nNAND %s: ", read ? "read" : "write");

		nand = &nand_info[dev];

		s = strchr(cmd, '.');

		if (s && !strcmp(s, ".raw")) {
			raw = 1;

			if (arg_off(argv[3], &dev, &off, &size))
				return 1;

			if (argc > 4 && !str2long(argv[4], &pagecount)) {
				printf("'%s' is not a number\n", argv[4]);
				return 1;
			}

			if (pagecount * nand->writesize > size) {
				puts("Size exceeds partition or device limit\n");
				return -1;
			}

			rwsize = pagecount * (nand->writesize + nand->oobsize);
		} else {
			if (arg_off_size(argc - 3, argv + 3, &dev,
						&off, &size) != 0)
				return 1;

			rwsize = size;
		}

		if (!s || !strcmp(s, ".jffs2") ||
		    !strcmp(s, ".e") || !strcmp(s, ".i")) {
			if (read)
				ret = nand_read_skip_bad(nand, off, &rwsize,
							 (u_char *)addr);
			else
				ret = nand_write_skip_bad(nand, off, &rwsize,
							  (u_char *)addr, 0);
#ifdef CONFIG_CMD_NAND_TRIMFFS
		} else if (!strcmp(s, ".trimffs")) {
			if (read) {
				printf("Unknown nand command suffix '%s'\n", s);
				return 1;
			}
			ret = nand_write_skip_bad(nand, off, &rwsize,
						(u_char *)addr,
						WITH_DROP_FFS);
#endif
		} else if (!read && s !=NULL && (!strcmp(s, ".uboot")) && nand->writesize == 4096) {
			rwsize = 4096;
			nand_write(nand, off, &rwsize, (u_char *)addr);

			off += 4096;
			addr += 2048;
			nand_write(nand, off, &rwsize, (u_char *)addr);

			off += 4096;
			addr += 2048;
			nand_write(nand, off, &rwsize, (u_char *)addr);

			off += 4096;
			addr += 2048;
			nand_write(nand, off, &rwsize, (u_char *)addr);

#ifdef CONFIG_CMD_NAND_YAFFS
		} else if (!strcmp(s, ".yaffs")) {
			if (read) {
				printf("Unknown nand command suffix '%s'.\n", s);
				return 1;
			}
			ret = nand_write_skip_bad(nand, off, &rwsize,
						(u_char *)addr,
						WITH_INLINE_OOB);
#endif
		} else if (!strcmp(s, ".oob")) {
			/* out-of-band data */
			mtd_oob_ops_t ops = {
				.oobbuf = (u8 *)addr,
				.ooblen = rwsize,
				.mode = MTD_OOB_RAW
			};

			if (read)
				ret = nand->read_oob(nand, off, &ops);
			else
				ret = nand->write_oob(nand, off, &ops);
		} else if (raw) {