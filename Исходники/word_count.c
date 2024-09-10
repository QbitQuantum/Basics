int main(int argc, char *argv[]) {
	int i;
	wc_data_t wc_data;

	i = map_reduce_init (&argc, &argv);
	CHECK_ERROR(i < 0);

	wc_data.fname = argv[1];

	printf("Wordcount: Running...\n");

	// Setup splitter args
	wc_data.unit_size = 5; // approx 3 bytes per word
	wc_data.fpos = 0;

	// Setup map reduce args
	map_reduce_args_t map_reduce_args;
	memset(&map_reduce_args, 0, sizeof(map_reduce_args_t));
	map_reduce_args.task_data = &wc_data;
	map_reduce_args.task_data_size = sizeof(wc_data_t);
	
	map_reduce_args.prep = wc_prep;
	map_reduce_args.cleanup = wc_cleanup;
	map_reduce_args.map = wordcount_map;
	map_reduce_args.reduce = wordcount_reduce;
	map_reduce_args.combiner = wordcount_combiner;
	map_reduce_args.splitter = wordcount_splitter;
	map_reduce_args.key_cmp = mystrcmp;
	
	map_reduce_args.unit_size = wc_data.unit_size;
	map_reduce_args.partition = NULL; // use default
	map_reduce_args.result = &wc_data.wc_vals;
	
	map_reduce_args.L1_cache_size = atoi(GETENV("MR_L1CACHESIZE"));//1024 * 1024 * 2;
	map_reduce_args.num_map_threads = atoi(GETENV("MR_NUMTHREADS"));//8;
	map_reduce_args.num_reduce_threads = atoi(GETENV("MR_NUMTHREADS"));//16;
	map_reduce_args.num_merge_threads = atoi(GETENV("MR_NUMTHREADS"));//8;
	map_reduce_args.num_procs = atoi(GETENV("MR_NUMPROCS"));//16;
	map_reduce_args.key_match_factor = (float)atof(GETENV("MR_KEYMATCHFACTOR"));//2;

	printf("Wordcount: Calling MapReduce Scheduler Wordcount\n");

	CHECK_ERROR(map_reduce (&map_reduce_args) < 0);

	map_reduce_cleanup(&map_reduce_args);
	CHECK_ERROR (map_reduce_finalize ());

	get_time (&end);

	return 0;
}