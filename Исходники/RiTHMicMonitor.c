int main(int argc, char** argv)
{
	pthread_t thread1, thread2;  /* thread variables */
	cpu_set_t  mask;
    program_thread_args *args = malloc(sizeof(program_thread_args));
    args->argc = argc;
    args->argv = argv;

	CPU_ZERO(&mask);
    	CPU_SET(0, &mask);
    	int result = sched_setaffinity(0, sizeof(mask), &mask);	
	if (result != 0)
	{
		printf("Cannot set affinity to monitor..\n");
		exit(0);
	}
	
	// This is just a switch to run the program in hi-res timer evaluation mode
	// If checktimers() is called it will output the average of a timer with a given interval
	if (argc >= 2 && !strcmp(argv[1],"-test")) {
		printf("%s\n", argv[1]);
	}
	else {
		/* create monitor and main thread */
		pthread_create(&thread1, NULL, (void *) &monitor_thread, 0);
		pthread_create(&thread2, NULL, (void *) &main_thread, (void *)args);

		/* Main block now waits for both threads to terminate, before it exits
   If main block exits, both threads exit, even if the threads have not
   finished their work */
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}

	/* exit */

	report(); 
	destroyContext(); 


    free(args);
	exit(0);