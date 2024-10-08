int main(int argc, char **argv) {

	int arg, refresh_interval, i;
	struct timeval t1, t2;
	time_t elapsed_time;

	first_run = 1;
	refresh_interval = 1000;

	while((arg = getopt(argc, argv, "t:h"))!=-1) {
		switch(arg) {
			case 't':
				if((sscanf(optarg, "%d", &refresh_interval))) refresh_interval = refresh_interval*1000;
				else {
					fprintf(stderr, "Update interval must be an integer value\n");
					print_usage(1);
					return 1;
				}
				break;
			case 'h':
				print_usage(0);
				return 0;
				break;
			case '?':
				if(isprint(optopt)) {
					print_usage(1);
					return 1;
				}
				else printf("Unknown error parsing command line arguments: 0x%08x\n", optopt);
				break;
			default:
				break;
		}
	}

	for(i=optind; i<argc; i++) printf("Useless command line argument: %s\n", argv[i]);

	printf("{\"version\":1}\n");
	printf("[[],\n");

	conf();

	while(1) {
		gettimeofday(&t1, NULL);

		fflush(stdout);
		printf("[\n");

		update();

		printf("{\"full_text\":\"\"}");

		printf("],\n");

		gettimeofday(&t2, NULL);
		elapsed_time = ((t2.tv_sec-t1.tv_sec)*1000)+((t2.tv_usec-t1.tv_usec)/1000);
		if(elapsed_time<refresh_interval) usleep((useconds_t)(refresh_interval-elapsed_time)*1000);
	}

	return 0;
}