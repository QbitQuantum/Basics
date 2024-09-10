int
main(int argc, char *argv[])
{
	int fd;
	struct stat stbuf;
	void *dest;
	void *src;
	off_t dest_off = 0;
	off_t src_off = 0;
	uint64_t bytes = 0;
	int who = 0;
	off_t overlap = 0;

	START(argc, argv, "pmem_memmove");

	fd = OPEN(argv[1], O_RDWR);
	FSTAT(fd, &stbuf);

	if (argc < 3)
		USAGE();

	for (int arg = 2; arg < argc; arg++) {
		if (strchr("dsboS",
		    argv[arg][0]) == NULL || argv[arg][1] != ':')
			FATAL("op must be d: or s: or b: or o: or S:");

		off_t val = strtoul(&argv[arg][2], NULL, 0);

		switch (argv[arg][0]) {
		case 'd':
			if (val <= 0)
				FATAL("bad offset (%lu) with d: option", val);
			dest_off = val;
			break;

		case 's':
			if (val <= 0)
				FATAL("bad offset (%lu) with s: option", val);
			src_off = val;
			break;

		case 'b':
			if (val <= 0)
				FATAL("bad length (%lu) with b: option", val);
			bytes = val;
			break;

		case 'o':
			if (val != 1 && val != 2)
				FATAL("bad val (%lu) with o: option", val);
			who = (int)val;
			break;

		case 'S':
			overlap = val;
			break;
		}
	}

	if (who == 0 && overlap != 0)
		USAGE();

	/* for overlap the src and dest must be created differently */
	if (who == 0) {
		/* src > dest */
		dest = pmem_map(fd);
		if (dest == NULL)
			FATAL("!could not mmap dest file %s", argv[1]);

		src = MMAP(dest + stbuf.st_size, stbuf.st_size,
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
			-1, 0);
		/*
		 * Its very unlikely that src would not be > dest. pmem_map
		 * chooses the first unused address >= 1TB, large
		 * enough to hold the give range, and 1GB aligned. Log
		 * the error if the mapped addresses cannot be swapped
		 * but allow the test to continue.
		 */
		if (src <= dest) {
			swap_mappings(&dest, &src, stbuf.st_size, fd);
			if (src <= dest)
				ERR("cannot map files in memory order");
		}

		do_memmove(fd, dest, src, argv[1], dest_off, src_off,
			0, bytes);

		/* dest > src */
		swap_mappings(&dest, &src, stbuf.st_size, fd);

		if (dest <= src)
			ERR("cannot map files in memory order");

		do_memmove(fd, dest, src, argv[1], dest_off, src_off, 0,
			bytes);
		MUNMAP(dest, stbuf.st_size);
		MUNMAP(src, stbuf.st_size);
	} else if (who == 1) {
		/* src overlap with dest */
		dest = pmem_map(fd);
		if (dest == NULL)
			FATAL("!Could not mmap %s: \n", argv[1]);

		src = dest + overlap;
		memset(dest, 0, bytes);
		do_memmove(fd, dest, src, argv[1], dest_off, src_off,
			overlap, bytes);
		MUNMAP(dest, stbuf.st_size);
	} else {
		/* dest overlap with src */
		dest = pmem_map(fd);
		if (dest == NULL) {
			FATAL("!Could not mmap %s: \n", argv[1]);
		}
		src = dest;
		dest = src + overlap;
		memset(src, 0, bytes);
		do_memmove(fd, dest, src, argv[1], dest_off, src_off,
			overlap, bytes);
		MUNMAP(src, stbuf.st_size);
	}

	CLOSE(fd);

	DONE(NULL);
}