static void
seed_random(void)
{
	SEED_T seed;
	struct timeval tv;

	/*
	 * Seed from time of day and process id multiplied by small primes.
	 */
	(void) gettimeofday(&tv, NULL);
	seed = (tv.tv_sec % 10000) * 523 + tv.tv_usec * 13 +
	    (getpid() % 1000) * 983;
	SRAND(seed);
}