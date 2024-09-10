static void *barrier_func(void *parameter)
{
	int id = (int)parameter;
	int status;

	printf("barrier_func: Thread %d started\n",  id);
#ifndef CONFIG_DISABLE_SIGNALS
	usleep(HALF_SECOND);
#endif

	/* Wait at the barrier until all threads are synchronized. */

	printf("barrier_func: Thread %d calling pthread_barrier_wait()\n", id);
	FFLUSH();
	status = pthread_barrier_wait(&barrier);
	if (status == 0) {
		printf("barrier_func: Thread %d, back with status=0 (I am not special)\n", id);
	} else if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
		printf("barrier_func: Thread %d, back with status=PTHREAD_BARRIER_SERIAL_THREAD (I AM SPECIAL)\n", id);
	} else {
		printf("barrier_func: ERROR thread %d could not get semaphore value\n", id);
	}
	FFLUSH();

#ifndef CONFIG_DISABLE_SIGNALS
	usleep(HALF_SECOND);
#endif
	printf("barrier_func: Thread %d done\n",  id);
	FFLUSH();
	return NULL;
}