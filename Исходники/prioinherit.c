static void *medpri_thread(void *parameter)
{
	printf("medpri_thread: Started ... I won't let go of the CPU!\n");
	g_middlestate = RUNNING;
	FFLUSH();

	/* The following loop will completely block lowpri_thread from running.
	 * UNLESS priority inheritance is working.  In that case, its priority
	 * will be boosted.
	 */

	while (nhighpri_running() > 0) {
		hog_cpu();
	}

	printf("medpri_thread: Okay... I'm done!\n");
	FFLUSH();
	g_middlestate = DONE;
	return NULL;
}