int main(int argc, char *argv[]) {

    /* XXX Checking how well the two clocks track each other
    unsigned long    lsec, lusec;
    unsigned long    fsec, fusec;
    long    dsec, dusec;
    int	    i;
    for (i = 0; i < 10; i++) {
	get_time_using_GetLocalTime(lsec, lusec);
	get_time_using_ftime(fsec, fusec);
	dsec = lsec - fsec;
	dusec = lusec - fusec;

	printf("L: %u:%u, F: %u:%u, Difference: %u:%ld\n",
	    lsec, lusec, fsec, fusec, dsec, dusec);

	Sleep(1000);
    }
    */

	/* Check the behavior of the clock */
	SYSTEMTIME sstart, stime;               // System time in funky structure
	FILETIME ftime;     // Time in 100-nsec intervals since Jan 1 1601
	LARGE_INTEGER tics; // ftime stored into a 64-bit quantity
	GetLocalTime(&sstart);
	stime = sstart;
	while (stime.wSecond - sstart.wSecond < 2) {
		GetLocalTime(&stime);
		printf("Seconds %2d, Milliseconds %4d\n", static_cast<int>(stime.wSecond),
			static_cast<int>(stime.wMilliseconds));

		SystemTimeToFileTime(&stime, &ftime);

		// Copy the data into a structure that can be treated as a 64-bit
		// integer
		tics.HighPart = ftime.dwHighDateTime;
		tics.LowPart = ftime.dwLowDateTime;
		printf("  Converted to 64-bit: %llu\n", tics.QuadPart);

		// Convert the 64-bit time into seconds and microseconds since July 1
		// 1601
		unsigned long sec, usec;
		sec = (long)(tics.QuadPart / 10000000L);
		usec = (long)((tics.QuadPart - (((LONGLONG)(sec)) * 10000000L)) / 10);
		printf("  Converted to secs and usecs: %6lu:%6lu\n", sec, usec);
	}

  /* Checking the vrpn_gettimeofday() function for monotonicity and step size */
  struct timeval last_time, this_time;
  double skip;
  vrpn_gettimeofday(&last_time, NULL);
  printf("Checking for monotonicity and step size\n");
  printf(" (should be no further output if things are working perfectly)\n");
  while (true) {
    vrpn_gettimeofday(&this_time, NULL);
	skip = vrpn_TimevalDurationSeconds(this_time, last_time);
    if (skip > 200e-6) {
      printf("Skipped forward %lg microseconds\n", skip*1e6);
    }
    if (skip < 0) {
  		printf("** Backwards %lg microseconds\n", skip*1e6);
    }
    last_time = this_time;
  }

  return 0;
}