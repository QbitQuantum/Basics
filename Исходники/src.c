int main(int argc, char **argv)
{
	FILE *file;
	int i, j;
	unsigned file_size;
	pthread_mutex_init(&mutex, NULL);
	j = 0;
	hash_sum = 1;
	unsigned short cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
	struct sysinfo si;
	sysinfo(&si);
	printf("Free RAM\t=\t%lu B or %f MB\n", si.freeram,
			((double)si.freeram * (double)si.mem_unit) / 1048576.0);
	printf("Core(s) avaible =\t%u\n", cpu_count);
	file = fopen(argv[1], "rb");
	if (file < 0) {
		perror("Cant open file");
		print("Usage: chsum /full/path/to/file [force_num_threads]");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	printf("Size of file\t=\t%u\n", file_size);
	unsigned num_size = ceil(file_size / (0.3 * si.freeram));
	unsigned free_size = file_size;
	struct timespec t_before, t_after;
	clock_gettime(CLOCK_BOOTTIME, &t_before);
	printf("Start time\t=\t%lu sec and %lu nsec\n",
			t_before.tv_sec, t_before.tv_nsec);
	while (j < num_size) {
		if (free_size < 0.3 * si.freeram) {
			n = ceil(free_size / sizeof(short));
			mas = (short *)malloc(n * sizeof(short));
			sum_exp = (float *)malloc(n * sizeof(float));
		} else {
			n = ceil(0.3 * si.freeram / sizeof(short));
			mas = (short *)malloc(n * sizeof(short));
			sum_exp = (float *)malloc(n * sizeof(float));
			free_size = free_size - 0.3 * si.freeram;
		}
		fread(mas, n * sizeof(short), 1, file);
		fseek(file, n * sizeof(short), SEEK_CUR);
		if (argc == 3)
			cpu_count = atoi(argv[2]);
		printf("Threads number\t=\t%d\n", cpu_count);
		pthread_t id[cpu_count];
		for (i = 0; i < cpu_count; i++) {
			if (pthread_create(&id[i], NULL, work, NULL)) {
					printf("Thread creating error\n");
					exit(EXIT_FAILURE);
			}
		}
		for (i = 0; i < cpu_count; i++)
			pthread_join(id[i], NULL);
		j++;
	}
	clock_gettime(CLOCK_BOOTTIME, &t_after);
	printf("End time\t=\t%lu sec and %lu nsec\n",
			t_after.tv_sec, t_after.tv_nsec);
	long long start, end, diff, res_in_microsec;
	start = t_before.tv_sec*NANOS + t_before.tv_nsec;
	end = t_after.tv_sec*NANOS + t_after.tv_nsec;
	diff = end - start;
	res_in_microsec = diff / 1000 + (diff % 1000 >= 500);
	printf("Elapse time\t=\t%lld microsec\n", res_in_microsec);
	printf("Hash\t\t=\t%.20f\n", hash_sum);
	fclose(file);
	return 0;
}