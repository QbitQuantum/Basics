static int parse_options( int argc, char *argv[], parsed_options_t *settings )
{
	int c, index;
	int retval;
	char *version;
	struct option options[] =
	{
		{ "iobase", required_argument, NULL, 'b' },
		{ "device-file", required_argument, NULL, 'c' },
		{ "dma", required_argument, NULL, 'd' },
		{ "file", required_argument, NULL, 'f' },
		{ "help", no_argument, NULL, 'h' },
		{ "init-data", required_argument, NULL, 'I' },
		{ "irq", required_argument, NULL, 'i' },
		{ "pci-slot", required_argument, NULL, 'l' },
		{ "minor", required_argument, NULL, 'm' },
		{ "offline", no_argument, NULL, 'o' },
		{ "pad", required_argument, NULL, 'p' },
		{ "sad", required_argument, NULL, 's' },
		{ "board-type", required_argument, NULL, 't' },
		{ "pci-bus", required_argument, NULL, 'u' },
		{ "version", no_argument, NULL, 'v' },
		{ "no-ifc", no_argument, &settings->assert_ifc, 0 },
		{ "ifc", no_argument, &settings->assert_ifc, 1 },
		{ "no-sre", no_argument, &settings->assert_remote_enable, 0 },
		{ "sre", no_argument, &settings->assert_remote_enable, 1 },
		{ "no-system-controller", no_argument, &settings->is_system_controller, 0 },
		{ "system-controller", no_argument, &settings->is_system_controller, 1 },
		{ 0 },
	};

	memset(settings, 0, sizeof(parsed_options_t));
	settings->irq = -1;
	settings->iobase = (unsigned long)-1;
	settings->dma = -1;
	settings->pci_bus = -1;
	settings->pci_slot = -1;
	settings->pad = -1;
	settings->sad = -1;
	settings->assert_ifc = 1;
	settings->assert_remote_enable = 1;
	settings->is_system_controller = -1;

	while( 1 )
	{
		c = getopt_long(argc, argv, "b:c:d:f:hi:I:l:m:op:s:t:u:v", options, &index);
		if( c == -1 ) break;
		switch( c )
		{
		case 0:
			break;
		case 'b':
			settings->iobase = strtol( optarg, NULL, 0 );
			break;
		case 'c' :
			free(settings->config_file);
			settings->device_file = strdup( optarg );
			break;
		case 'd':
			settings->dma = strtol( optarg, NULL, 0 );
			break;
		case 'f':
			free(settings->config_file);
			settings->config_file = strdup( optarg );
			break;
		case 'h':
			help();
			exit( 0 );
			break;
		case 'I':
			retval = load_init_data(settings, optarg);
			if(retval < 0)
				return retval;
			break;
		case 'i':
			settings->irq = strtol( optarg, NULL, 0 );
			break;
		case 'l':
			settings->pci_slot = strtol( optarg, NULL, 0 );
			break;
		case 'm':
			settings->minor = strtol( optarg, NULL, 0 );
			break;
		case 'o':
			settings->offline = 1;
			break;
		case 'p':
			settings->pad = strtol( optarg, NULL, 0 );
			break;
		case 's':
			settings->sad = strtol( optarg, NULL, 0 );
			settings->sad -= sad_offset;
			break;
		case 't':
			free(settings->board_type);
			settings->board_type = strdup( optarg );
			break;
		case 'u':
			settings->pci_bus = strtol( optarg, NULL, 0 );
			break;
		case 'v':
		        ibvers(&version);
			printf("linux-gpib version = %s\n",version);
			exit(0);
			break;
		default:
			help();
			exit(1);
		}
	}
	if(settings->device_file)
	{
		struct stat file_stats;
		if( stat( settings->device_file, &file_stats ) < 0 )
		{
			fprintf(stderr, "Failed to get file information on file \"%s\".\n", settings->device_file);
			perror(__FUNCTION__);
			return -errno;
		}
		if(S_ISCHR(file_stats.st_mode) == 0)
		{
			fprintf(stderr, "The device file \"%s\" is not a character device.\n", settings->device_file);
			return -EINVAL;
		}
		settings->minor = minor( file_stats.st_rdev );
	}else
	{
		if(asprintf(&settings->device_file , "/dev/gpib%i", settings->minor) < 0)
		{
			return -ENOMEM;
		}
	}
	return 0;
}