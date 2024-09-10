///////////////////////////////////////////////////////////////////////////////
//  MAIN: collect input parameters and run benchmarks
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

	int info_flag = 0;
	int usage_flag = 0;
	int csv_flag = 0;
    int type_flag = 0;
	int c;
	char *sizes_str = NULL;
	char *devices_str = NULL;
    char *vector_str = NULL;
	char *repeat_str = NULL;
	char *iterations_str = NULL;
	
	while (1)
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"info", no_argument,       &info_flag, 1},
			{"help", no_argument,       &usage_flag, 1},
			{"csv",  no_argument,       &csv_flag, 1},
            {"private", no_argument,       &type_flag, 1},
            {"global", no_argument,       &type_flag, 2},
            {"local", no_argument,       &type_flag, 0},
			/* These options don't set a flag.
			 We distinguish them by their indices. */
			{"sizes",    optional_argument, 0, 'a'},
			{"device",  optional_argument, 0, 'b'},
			{"repeats",  optional_argument, 0, 'c'},
			{"iterations",  optional_argument, 0, 'd'},
			{"vector",  optional_argument, 0, 'e'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;
		
		c = getopt_long (argc, argv, "a:", long_options, &option_index);
		
		/* Detect the end of the options. */
		if (c == -1)
			break;
		
		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				break;
			case 'a':
				sizes_str = optarg;
				break;
			case 'b':
				devices_str = optarg;
				break;
			case 'c':
				repeat_str = optarg;
				break;
			case 'd':
				iterations_str = optarg;
				break;
			case 'e':
				vector_str = optarg;
				break;
			case '?':
				/* getopt_long already printed an error message. */
				break;
			default:
				abort ();
		}
	}
	
	
	// retrieve devices
	unsigned int num_devices = 0, num_platforms;

    cl_platform_id* platforms = get_all_platforms(&num_platforms, NULL);
	cl_device_id* devices = get_all_devices(platforms, num_platforms, &num_devices);
    free(platforms);
	if(devices == NULL) {
		printf("Error: Failed to create a device group!\n");
		return 1;
	}
		
	if (info_flag) {
		print_device_list(devices, num_devices);
		return 0;
	}
	
	if (usage_flag) {
		print_usage();
		return 0;
	}
	
	// retrieve devices to be benchmarked
	cl_device_id *used_devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
	unsigned int used_num_devices = 0;
	if((devices_str == '\0') || (strcmp(devices_str, "all") == 0)) {
		// nothing specified, run benchmark for all devices
		for(unsigned int i = 0; i < num_devices; i++) used_devices[i] = devices[i];
		used_num_devices = num_devices;
	} else {
		// check the given device-numbers and fill up the device-array
		char* ptr;
		used_num_devices = 0;
		ptr = strtok(devices_str, ",");
		while(ptr != NULL) {
			unsigned int id = 0;
			if(sscanf(ptr, "%i", &id) > 0) {
				if(id >= 0 && id < num_devices) {
					used_devices[used_num_devices] = devices[id];
					used_num_devices++;
				}
			} else {
				printf("invalid device-number given (%d)\n", id);
				return 1;
			}
			ptr = strtok(NULL, ",");
		}
	}
	
	// retrieve memory-sizes to run the benchmark with  -- momentary unused
	unsigned long* sizes = (unsigned long*) malloc(sizeof(unsigned long) * MAX_SIZES * used_num_devices);
	for (unsigned int i = 0; i < MAX_SIZES * used_num_devices; i++) {
		sizes[i] = 0;
	}
	unsigned int num_sizes = 0;
	if(sizes_str == '\0') {
		// nothing specified, test for maximum
		num_sizes = 1;
		for (unsigned int i = 0; i < used_num_devices; i++) {
			sizes[i * MAX_SIZES] = 10 * 1024 * 1024;
		}
	} else {
		// check given numbers and fill up the device-array
		char* ptr;
		ptr = strtok(sizes_str, ",");
		while(ptr != NULL) {
			unsigned long size = 0;
			unsigned long _s;
			char _m;
			if (sscanf(ptr, "%lu%c", &_s, &_m) == 2) {
				switch (_m) {
					case 'K': case 'k':
						size = _s * 1024;
						break;
					case 'M': case 'm':
						size = _s * 1024 * 1024;
						break;
					default:
						printf("invalid size given (%s)\n", ptr);
						return 1;
				}
			} else if (sscanf(ptr, "%lu", &_s) > 0) {
				size = _s;
			} else {
				printf("invalid size given (%s)\n", ptr);
				return 1;
			}
			for (unsigned int i = 0; i < used_num_devices; i++) {
				sizes[num_sizes + i * MAX_SIZES] = size;
			}
			num_sizes ++;
			ptr = strtok(NULL, ",");
		}		
	}
	
	// retrieve amount of repeats for each data-point
	unsigned int repeats = 0;
	if (repeat_str == '\0') {
		repeats = DEFAULT_REPEATS;
	} else {
		if (sscanf(repeat_str, "%d", &repeats) > 0) {
			// nothing more to do
		} else {
			printf("invalid number of repeats given (%s)\n", repeat_str);
			return 1;
		}
	}
	
	// retrieve amount of iterations used for each data-point
	unsigned int iterations = 0;
	if (iterations_str== '\0') {
		iterations = DEFAULT_ITERATIONS;
	} else {
		if (sscanf(iterations_str, "%d", &iterations) > 0) {
			// nothing more to do
		} else {
			printf("invalid number of iterations given (%s)\n", iterations_str);
			return 1;
		}
	}

    int f4 = 0;
    char vec[16];
    if (vector_str== '\0') {
        f4 = 0;
    } else {
        if (sscanf(vector_str, "%d", &f4) < 0 || f4 < 0 || f4 > 4) {
            printf("Request for unsupported vector type! Supported are:\n \
                   \t0 -> float\n \
                   \t1 -> float2\n \
                   \t2 -> float4\n \
                   \t3 -> float8\n \
                   \t4 -> float16\n");
            return 1;
        }
    }