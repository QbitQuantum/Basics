int main(int argc, char *argv[])
{
	int r;
	int fd;
	struct stat sb;
	char *addr;
	u64 gcov_list_addr;

	printf("sizes: %zu %zu %zu %zu\n",
	       sizeof(gcov_unsigned_int),
	       sizeof(struct gcov_ctr_info),
	       sizeof(struct gcov_fn_info),
	       sizeof(struct gcov_info));

	if (argc < 3) {
		fprintf(stderr, "Usage:\n"
			"\t%s skiboot.dump gcov_offset\n\n",
			argv[0]);
		return -1;
	}

	/* argv[1] = skiboot.dump */
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Cannot open dump: %s (error %d %s)\n",
			argv[1], errno, strerror(errno));
		exit(-1);
	}

	r = fstat(fd, &sb);
	if (r < 0) {
		fprintf(stderr, "Cannot stat dump, %d %s\n",
			errno, strerror(errno));
		exit(-1);
	}

	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	assert(addr != NULL);
	skiboot_dump_size = sb.st_size;

	printf("Skiboot memory dump %p - %p\n",
	       (void*)SKIBOOT_OFFSET, (void*)SKIBOOT_OFFSET+sb.st_size);

	gcov_list_addr = strtoll(argv[2], NULL, 0);
	gcov_list_addr = (u64)(addr + (gcov_list_addr - SKIBOOT_OFFSET));
	gcov_list_addr = be64toh(*(u64*)gcov_list_addr);

	printf("Skiboot gcov_info_list at %p\n", (void*)gcov_list_addr);

	do {
		gcov_info_list = (struct gcov_info *)(addr + (gcov_list_addr - SKIBOOT_OFFSET));
		write_gcda(addr, gcov_info_list);
		gcov_list_addr = be64toh((u64)gcov_info_list->next);

	} while(gcov_list_addr);

	munmap(addr, sb.st_size);
	close(fd);

	return 0;
}