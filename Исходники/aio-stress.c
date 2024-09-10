int main(int ac, char **av)
{
	int rwfd;
	int i;
	int j;
	int c;

	off_t file_size = 1 * 1024 * 1024 * 1024;
	int first_stage = WRITE;
	struct io_oper *oper;
	int status = 0;
	int num_files = 0;
	int open_fds = 0;
	struct thread_info *t;

	page_size_mask = getpagesize() - 1;

	while (1) {
		c = getopt(ac, av, "a:b:c:C:m:s:r:d:i:I:o:t:lLnhOSxvu");
		if (c < 0)
			break;

		switch (c) {
		case 'a':
			page_size_mask = parse_size(optarg, 1024);
			page_size_mask--;
			break;
		case 'c':
			num_contexts = atoi(optarg);
			break;
		case 'C':
			context_offset = parse_size(optarg, 1024 * 1024);
		case 'b':
			max_io_submit = atoi(optarg);
			break;
		case 's':
			file_size = parse_size(optarg, 1024 * 1024);
			break;
		case 'd':
			depth = atoi(optarg);
			break;
		case 'r':
			rec_len = parse_size(optarg, 1024);
			break;
		case 'i':
			io_iter = atoi(optarg);
			break;
		case 'I':
			iterations = atoi(optarg);
			break;
		case 'n':
			fsync_stages = 0;
			break;
		case 'l':
			latency_stats = 1;
			break;
		case 'L':
			completion_latency_stats = 1;
			break;
		case 'm':
			if (!strcmp(optarg, "shm")) {
				fprintf(stderr, "using ipc shm\n");
				use_shm = USE_SHM;
			} else if (!strcmp(optarg, "shmfs")) {
				fprintf(stderr, "using /dev/shm for buffers\n");
				use_shm = USE_SHMFS;
			}
			break;
		case 'o':
			i = atoi(optarg);
			stages |= 1 << i;
			fprintf(stderr, "adding stage %s\n", stage_name(i));
			break;
		case 'O':
			o_direct = O_DIRECT;
			break;
		case 'S':
			o_sync = O_SYNC;
			break;
		case 't':
			num_threads = atoi(optarg);
			break;
		case 'x':
			stonewall = 0;
			break;
		case 'u':
			unlink_files = 1;
			break;
		case 'v':
			verify = 1;
			break;
		case 'h':
		default:
			print_usage();
			exit(1);
		}
	}

	/*
	 * make sure we don't try to submit more I/O than we have allocated
	 * memory for
	 */
	if (depth < io_iter) {
		io_iter = depth;
		fprintf(stderr, "dropping io_iter to %d\n", io_iter);
	}

	if (optind >= ac) {
		print_usage();
		exit(1);
	}

	num_files = ac - optind;

	if (num_threads > (num_files * num_contexts)) {
		num_threads = num_files * num_contexts;
		fprintf(stderr,
			"dropping thread count to the number of contexts %d\n",
			num_threads);
	}

	t = malloc(num_threads * sizeof(*t));
	if (!t) {
		perror("malloc");
		exit(1);
	}
	global_thread_info = t;

	/* by default, allow a huge number of iocbs to be sent towards
	 * io_submit
	 */
	if (!max_io_submit)
		max_io_submit = num_files * io_iter * num_contexts;

	/*
	 * make sure we don't try to submit more I/O than max_io_submit allows
	 */
	if (max_io_submit < io_iter) {
		io_iter = max_io_submit;
		fprintf(stderr, "dropping io_iter to %d\n", io_iter);
	}

	if (!stages) {
		stages =
		    (1 << WRITE) | (1 << READ) | (1 << RREAD) | (1 << RWRITE);
	} else {
		for (i = 0; i < LAST_STAGE; i++) {
			if (stages & (1 << i)) {
				first_stage = i;
				fprintf(stderr, "starting with %s\n",
					stage_name(i));
				break;
			}
		}
	}

	if (file_size < num_contexts * context_offset) {
		fprintf(stderr, "file size %ld too small for %d contexts\n",
			(long)file_size, num_contexts);
		exit(1);
	}

	fprintf(stderr, "file size %ldMB, record size %ldKB, depth %d, "
		"I/O per iteration %d\n",
		(long)(file_size / (1024 * 1024)),
		rec_len / 1024, depth, io_iter);
	fprintf(stderr, "max io_submit %d, buffer alignment set to %luKB\n",
		max_io_submit, (page_size_mask + 1) / 1024);
	fprintf(stderr, "threads %d files %d contexts %d context offset %ldMB "
		"verification %s\n", num_threads, num_files, num_contexts,
		(long)(context_offset / (1024 * 1024)), verify ? "on" : "off");
	/* open all the files and do any required setup for them */
	for (i = optind; i < ac; i++) {
		int thread_index;
		for (j = 0; j < num_contexts; j++) {
			thread_index = open_fds % num_threads;
			open_fds++;

			rwfd =
			    open(av[i], O_CREAT | O_RDWR | o_direct | o_sync,
				 0600);
			if (rwfd == -1) {
				fprintf(stderr,
					"error while creating file %s: %s",
					av[i], strerror(errno));
				exit(1);
			}

			oper =
			    create_oper(rwfd, first_stage, j * context_offset,
					file_size - j * context_offset, rec_len,
					depth, io_iter, av[i]);
			if (!oper) {
				fprintf(stderr, "error in create_oper\n");
				exit(-1);
			}
			oper_list_add(oper, &t[thread_index].active_opers);
			t[thread_index].num_files++;
		}
	}
	if (setup_shared_mem(num_threads, num_files * num_contexts,
			     depth, rec_len, max_io_submit)) {
		exit(1);
	}
	for (i = 0; i < num_threads; i++) {
		if (setup_ious
		    (&t[i], t[i].num_files, depth, rec_len, max_io_submit))
			exit(1);
	}
	if (num_threads > 1) {
		printf("Running multi thread version num_threads:%d\n",
		       num_threads);
		run_workers(t, num_threads);
	} else {
		printf("Running single thread version \n");
		status = worker(t);
	}
	if (unlink_files) {
		for (i = optind; i < ac; i++) {
			printf("Cleaning up file %s \n", av[i]);
			unlink(av[i]);
		}
	}

	if (status) {
		exit(1);
	}
	return status;
}