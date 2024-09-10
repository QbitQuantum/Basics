/*{{{  void ccsp_default_exit_handler (int status, bool core)*/
void ccsp_default_exit_handler (int status, bool core)
{
	#if defined(GENERATE_CORES)
	if (core) {
		MESSAGE ("fatal error code %d, core dumped\n", exit_status);
		FFLUSH (stderr);
		abort ();
	}
	#endif

	#if !defined(RMOX_BUILD)
	_exit (status);
	#else
	panic ("exiting CCSP");
	#endif
}