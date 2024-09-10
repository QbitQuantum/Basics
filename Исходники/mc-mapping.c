void access_bank(uint64_t gpu_mask, int shift, uint64_t iter){

	int oft = 0;
	if(gpu_mask > 0){ 
		g_mem_size += gpu_mask;
		oft +=  gpu_mask / 4;
	}
	if(shift >= 0){
		g_mem_size += (uint64_t)1 << shift;
		oft += ((uint64_t)1 << shift) / 4;
	}

	g_mem_size +=  farest_dist;
	g_mem_size = CEIL(g_mem_size, min_interval);

	/* alloc memory. align to a page boundary */
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	void *addr = (void *) 0x1000000080000000;
	int *memchunk = NULL;
	
	if (fd < 0) {
		perror("Open failed");
		exit(1);
	}

	memchunk = mmap(0, g_mem_size,
			PROT_READ | PROT_WRITE, 
			MAP_SHARED, 
			fd, (off_t)addr);

	if (memchunk == MAP_FAILED) {
		perror("failed to alloc");
		exit(1);
	}

	list = &memchunk[oft];

	next = 0; 
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);

	/* access banks */
	uint64_t naccess = run(iter);

	clock_gettime(CLOCK_REALTIME, &end);

	uint64_t nsdiff = get_elapsed(&start, &end);
	//printf("bandwidth %.2f MB/s\n", 64.0*1000.0*(double)naccess/(double)nsdiff);
	if(shift >= 0)
		bandwidth[shift] = 64.0 * 1000.0 * (double)naccess/(double)nsdiff;
	else
		bandwidth[MAX_SHIFT_NUM - 1] = 64.0 * 1000.0 * (double)naccess/(double)nsdiff;

		munmap(memchunk, g_mem_size);
		close(fd);
}