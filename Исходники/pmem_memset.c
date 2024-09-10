int
main(int argc, char *argv[])
{
	int fd;
	size_t mapped_len;
	char *dest;
	char *dest1;
	char *ret;

	START(argc, argv, "pmem_memset");

	if (argc != 4)
		UT_FATAL("usage: %s file offset length", argv[0]);

	fd = OPEN(argv[1], O_RDWR);

	/* open a pmem file and memory map it */
	if ((dest = pmem_map_file(argv[1], 0, 0, 0, &mapped_len, NULL)) == NULL)
		UT_FATAL("!Could not mmap %s\n", argv[1]);

	int dest_off = atoi(argv[2]);
	size_t bytes = strtoul(argv[3], NULL, 0);

	char *buf = MALLOC(bytes);

	memset(dest, 0, bytes);
	util_persist_auto(util_fd_is_device_dax(fd), dest, bytes);
	dest1 = MALLOC(bytes);
	memset(dest1, 0, bytes);

	/*
	 * This is used to verify that the value of what a non persistent
	 * memset matches the outcome of the persistent memset. The
	 * persistent memset will match the file but may not be the
	 * correct or expected value.
	 */
	memset(dest1 + dest_off, 0x5A, bytes / 4);
	memset(dest1 + dest_off  + (bytes / 4), 0x46, bytes / 4);

	/* Test the corner cases */
	ret = pmem_memset_persist(dest + dest_off, 0x5A, 0);
	UT_ASSERTeq(ret, dest + dest_off);
	UT_ASSERTeq(*(char *)(dest + dest_off), 0);

	/*
	 * Do the actual memset with persistence.
	 */
	ret = pmem_memset_persist(dest + dest_off, 0x5A, bytes / 4);
	UT_ASSERTeq(ret, dest + dest_off);
	ret = pmem_memset_persist(dest + dest_off  + (bytes / 4),
					0x46, bytes / 4);
	UT_ASSERTeq(ret, dest + dest_off + (bytes / 4));

	if (memcmp(dest, dest1, bytes / 2))
		UT_ERR("%s: first %zu bytes do not match",
			argv[1], bytes / 2);

	LSEEK(fd, (os_off_t)0, SEEK_SET);
	if (READ(fd, buf, bytes / 2) == bytes / 2) {
		if (memcmp(buf, dest, bytes / 2))
			UT_ERR("%s: first %zu bytes do not match",
				argv[1], bytes / 2);
	}

	UT_ASSERTeq(pmem_unmap(dest, mapped_len), 0);

	FREE(dest1);
	FREE(buf);
	CLOSE(fd);

	DONE(NULL);
}