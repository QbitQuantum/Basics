_Noreturn void serv_error(const char *fmt, ...) {
	va_list fmt_args;
	fprintf(stderr, "Server error: ");
	va_start(fmt_args, fmt);
	vfprintf(stderr, fmt, fmt_args);
	va_end(fmt_args);
	fprintf(stderr, " (%d; %s)\n", errno, strerror(errno));

	if(interrupted) {
		fprintf(stderr, "An error has occured during error handling. Exiting");
		quick_exit(EXIT_FAILURE);
	}

	interrupted = true;
	// If an error has occurred in the main thread, call the signal handler
	if(pthread_equal(main_thread, pthread_self()))
		exit_server(interrupted);
	else {
		// Otherwise, report the error to the main thread
		if(-1 == kill(getpid(), SIGINT)) {
			fprintf(stderr, "Fatal error. Unable to kill\n");
			quick_exit(EXIT_FAILURE);;
		}
		else
			exit_thread();
	}
}