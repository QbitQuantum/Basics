static int wait_evt_running(int seconds, int exists)
{
	int i;
	if (event_exists(EVT_RUNNING) == exists)
		return 0;
	for (i = 0; ; ) {
		Sleep(1000);
		if (event_exists(EVT_RUNNING) == exists)
			return 0;
		if (++i >= seconds)
			return -1;
		fputchar('.'); fflush(stdout);
	}
}