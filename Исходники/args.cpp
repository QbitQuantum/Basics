void Args::initRandom() {
	/*
	Initialize pseudo-random number generator,
	using process' PID.
	*/
	srand( (int)_getpid() );
}