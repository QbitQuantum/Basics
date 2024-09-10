int main(int argc, char **argv)
{
	pthread_t *pthreads;
	int pids[16];
	int i, j;
	long long time, time1;
	size_t len;
	char c = 'a';
	char unit;
	struct timespec start, end;
	struct timeval start1, end1;
	int size;
	unsigned long long count;
	FILE *output;
	char fs_type[20];
	char quill_enabled[40];
	char file_size_num[20];
	char filename[60];
	unsigned long long offset;

	if (argc < 7) {
		printf("Usage: ./pthread_test $FS $QUILL $fops $num_threads $FILE_SIZE $filename\n");
		return 0;
	}

	strcpy(fs_type, argv[1]);
	strcpy(quill_enabled, argv[2]);

	if (!strcmp(argv[3], "read"))
		fops = read;
	else if (!strcmp(argv[3], "pread"))
		fops = pread;
	else if (!strcmp(argv[3], "write"))
		fops = write;
	else if (!strcmp(argv[3], "pwrite"))
		fops = pwrite;
	else {
		printf("fops error!\n");
		return 0;
	}

	num_threads = atoi(argv[4]);
	if (num_threads <= 0 || num_threads > 16)
		num_threads = 1;

	strcpy(file_size_num, argv[5]);
	len = strlen(file_size_num);
	unit = file_size_num[len - 1];
	file_size_num[len - 1] = '\0';
	FILE_SIZE = atoll(file_size_num);
	switch (unit) {
	case 'K':
	case 'k':
		FILE_SIZE *= 1024;
		break;
	case 'M':
	case 'm':
		FILE_SIZE *= 1048576;
		break;
	case 'G':
	case 'g':
		FILE_SIZE *= 1073741824;
		break;
	default:
		printf("ERROR: FILE_SIZE should be #K/M/G format.\n");
		return 0;
		break;
	}

	if (FILE_SIZE < END_SIZE)
		FILE_SIZE = END_SIZE;
	if (FILE_SIZE > 2147483648) // RAM disk size
		FILE_SIZE = 2147483648;

	strcpy(filename, argv[6]);
	output = fopen(filename, "a");

	printf("# pthreads: %d\n", num_threads);
	buf = (char **)malloc(num_threads * sizeof(char *));
	for (i = 0; i < num_threads; i++) { 
		if (posix_memalign((void **)(buf + i), END_SIZE, END_SIZE)) { // up to 64MB
			printf("ERROR - POSIX NOMEM!\n");
			return 0;
		}
	}

	printf("# fds: ");
	fd = malloc(num_threads * sizeof(int));
	for (i = 0; i < num_threads; i++) {
		fd[i] = open("/mnt/ramdisk/test1", O_CREAT | O_RDWR, 0640); 
		printf("%d ", fd[i]);
	}
	printf("\n");

	//Warm up
	printf("warm up...\n");
	size = 4096;
	count = FILE_SIZE / (size * num_threads);
	for (i = 0; i < num_threads; i++) {
		offset = FILE_SIZE / num_threads * i;
		if (fops == read || fops == write)
			lseek(fd[i], offset, SEEK_SET);
		for (j = 0; j < count; j++) { 
//			pwrite(fd, buf[i], size, offset);
			if (fops == read || fops == write)
				fops(fd[i], buf[i], size);
			else
				fops(fd[i], buf[i], size, offset);
			offset += size;
		}
	}
	printf("warm up finished\n");

	//Allocate the threads
	pthreads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
	for (i = 0; i < num_threads; i++) {
		pids[i] = i;
		pthread_create(pthreads + i, NULL, pthread_transfer, (void *)(pids + i)); 
	}

	for (size = start_size; size <= END_SIZE; size <<= 1) {
		count = FILE_SIZE / (size * num_threads);
		for (i = 0; i < num_threads; i++)
			memset(buf[i], c, size);
		c++;
		for (i = 0; i < num_threads; i++)
			lseek(fd[i], 0, SEEK_SET);

		clock_gettime(CLOCK_MONOTONIC, &start);
		gettimeofday(&start1, NULL);
		start_all_pthreads();

		while (!all_pthreads_finished())
			;
		clock_gettime(CLOCK_MONOTONIC, &end);
		gettimeofday(&end1, NULL);

		time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		time1 = (end1.tv_sec - start1.tv_sec) * 1e6 + (end1.tv_usec - start1.tv_usec);
		printf("%s: Size %d bytes,\t %lld times,\t %lld nanoseconds, \t %lld us, \t Bandwidth %f MB/s, latency %lld nanoseconds.\n", argv[3], size, count, time, time1, FILE_SIZE * 1024.0 / time, time / count);
		fprintf(output, "%s,%s,%s,%d,%d,%lld,%lld,%lld,%f\n", fs_type, quill_enabled, argv[3], num_threads, size, FILE_SIZE, count, time, FILE_SIZE * 1.0 / time);
	}

	fclose(output);
	for (i = 0; i < num_threads; i++) {
		pthread_join(pthreads[i], NULL);
		free(buf[i]);
		close(fd[i]);
	}
	free(buf);
	free(fd);
	free(pthreads);
	return 0;
}