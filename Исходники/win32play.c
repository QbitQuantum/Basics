static void purge_output (void)
	{
	waveOutReset (dev);
	wait ();
	}           