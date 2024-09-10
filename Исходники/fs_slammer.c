int 
main(int argc, char *argv[])
{
	int ret;
	int i;

	if(argc < 6)
	{
		printf("Usage: fs_slammer <hddisk> <dir> <no. of files> <no-of-pages> <time in secs> <rw>\n");
		return -1;
	}
	
	time_t tt;
	time(&tt);
	srandom(tt);

	char fs_path[256];
	char *hd_name;
	struct stat stat_buf;
	char **argp =++argv;

	hd_name = (char *)malloc(10);
	strcpy(hd_name, *argp++);
	if((ret = stat(hd_name, &stat_buf))<0)
	{
		perror("stat:");
		return ret;
	}
	
	strcpy(fs_path, *argp++);
	if((ret = stat(fs_path, &stat_buf))<0)
	{
		perror("stat:");
		return ret;
	}
	
	if((ret=chdir(fs_path))<0)
	{
		printf("%s:\n", fs_path);
		perror("chdir:");
		return ret;
	}
	
	int no_threads = 0;

	sscanf(*argp++, "%d", &no_threads);

	sscanf(*argp++, "%d", &max_pages);

	int slam_time;
	sscanf(*argp++, "%d", &slam_time);

	char rw[4];
	sscanf(*argp++, "%s", rw);

	pthread_t *read_threads;
	pthread_t *slam_threads;

	if(strchr(rw, 'w'))
	{
		slam_threads = (pthread_t*)malloc(sizeof(pthread_t)*no_threads);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


		for(i = 0; i < no_threads; i++)
		{
			if((ret = pthread_create(slam_threads+i, &attr, slam_junk, NULL)))
			{
				perror("pthread_create:");
				return ret;
			}
		}
	}
	
	if(strchr(rw, 'r'))
	{
		read_threads = (pthread_t*)malloc(sizeof(pthread_t)*no_threads);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


		for(i = 0; i < no_threads; i++)
		{
			if((ret = pthread_create(read_threads+i, &attr, raw_reader, hd_name)))
			{
				perror("pthread_create:");
				return ret;
			}
		}
	}
	

	signal(SIGINT, termination_hdlr);
	signal(SIGTERM, termination_hdlr);
	signal(SIGQUIT, termination_hdlr);
	if(slam_time <0)
		pause();
	else
		sleep(slam_time);

	for(i = 0; i < no_threads; i++)
	{
		if(strchr(rw, 'w'))
			pthread_cancel(slam_threads[i]);
		if(strchr(rw, 'r'))
			pthread_cancel(read_threads[i]);
	}

	printf("Total bytes written = %lu\n", total_bytes_written);
	printf("Total bytes raw read = %lu\n", total_bytes_read);
	pthread_exit(NULL);

}