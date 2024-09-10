void mbadblocks(int argc, char **argv, int type)
{
	unsigned int i;
	unsigned int startSector=2;
	unsigned int endSector=0;
	struct MainParam_t mp;
	Fs_t *Fs;
	Stream_t *Dir;
	int ret;
	char *filename = NULL;
	char c;
	unsigned int badClus;
	int sectorMode=0;
	int writeMode=0;

	while ((c = getopt(argc, argv, "i:s:cwS:E:")) != EOF) {
		switch(c) {
		case 'i':
			set_cmd_line_image(optarg, 0);
			break;
		case 'c':
			checkListTwice(filename);
			filename = strdup(optarg);
			break;
		case 's':
			checkListTwice(filename);
			filename = strdup(optarg);
			sectorMode = 1;
			break;
		case 'S':
			startSector = atol(optarg); 
			break;
		case 'E':
			endSector = atol(optarg); 
			break;
		case 'w':
			writeMode = 1;
			break;
		case 'h':
			usage(0);
		default:
			usage(1);
		}
	}

	if (argc != optind+1 ||
	    !argv[optind][0] || argv[optind][1] != ':' || argv[optind][2]) {
		usage(1);
	}

	init_mp(&mp);

	Dir = open_root_dir(argv[optind][0], O_RDWR, NULL);
	if (!Dir) {
		fprintf(stderr,"%s: Cannot initialize drive\n", argv[0]);
		exit(1);
	}

	Fs = (Fs_t *)GetFs(Dir);
	in_len = Fs->cluster_size * Fs->sector_size;
	in_buf = malloc(in_len);
	if(!in_buf) {
		printOom();
		ret = 1;
		goto exit_0;
	}
	if(writeMode) {
		int i;
		pat_buf=malloc(in_len * N_PATTERN);
		if(!pat_buf) {
			printOom();
			ret = 1;
			goto exit_0;
		}
		srandom(time(NULL));
		for(i=0; i < in_len * N_PATTERN; i++) {
			pat_buf[i] = random();
		}
	}
	for(i=0; i < Fs->clus_start; i++ ){
		ret = READS(Fs->Next, in_buf, 
			    sectorsToBytes((Stream_t*)Fs, i), Fs->sector_size);
		if( ret < 0 ){
			perror("early error");
			goto exit_0;
		}
		if(ret < (signed int) Fs->sector_size){
			fprintf(stderr,"end of file in file_read\n");
			ret = 1;
			goto exit_0;
		}
	}
	ret = 0;

	badClus = Fs->last_fat + 1;

	if(startSector < 2)
		startSector = 2;
	if(endSector > Fs->num_clus + 2 || endSector <= 0) 
		endSector = Fs->num_clus + 2;

	if(filename) {
		char line[80];

		FILE *f = fopen(filename, "r");
		if(f == NULL) {
			fprintf(stderr, "Could not open %s (%s)\n",
				filename, strerror(errno));
			ret = 1;
			goto exit_0;
		}
		while(fgets(line, sizeof(line), f)) {
			char *ptr = line + strspn(line, " \t");
			long offset = strtoul(ptr, 0, 0);
			if(sectorMode)
				offset = (offset-Fs->clus_start)/Fs->cluster_size + 2;
			if(offset < 2) {
				fprintf(stderr, "Sector before start\n");
			} else if(offset >= Fs->num_clus) {
				fprintf(stderr, "Sector beyond end\n");
			} else {
				mark(Fs, offset, badClus);
				ret = 1;
			}
		}
	} else {
		Stream_t *dev;
		dev = Fs->Next;
		if(dev->Next)
			dev = dev->Next;

		in_len = Fs->cluster_size * Fs->sector_size;
		if(writeMode) {
			/* Write pattern */
			for(i=startSector; i< endSector; i++){
				if(got_signal)
					break;
				progress(i, Fs->num_clus);
				ret |= scan(Fs, dev, i, badClus, 
					    pat_buf + in_len * (i % N_PATTERN),
					    1);
			}

			/* Flush cache, so that we are sure we read the data
			   back from disk, rather than from the cache */
			if(!got_signal)
				DISCARD(dev);

			/* Read data back, and compare to pattern */
			for(i=startSector; i< endSector; i++){
				if(got_signal)
					break;
				progress(i, Fs->num_clus);
				ret |= scan(Fs, dev, i, badClus, 
					    pat_buf + in_len * (i % N_PATTERN),
					    0);
			}

		} else {

			for(i=startSector; i< endSector; i++){
				if(got_signal)
					break;
				progress(i, Fs->num_clus);
				ret |= scan(Fs, dev, i, badClus, NULL, 0);
			}
		}
	}
 exit_0:
	FREE(&Dir);
	exit(ret);
}