int
main(int argc, char *argv[])
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sigfpe;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGFPE, &sa, NULL);

	assert(rint(8.6) == 9.);
	assert(rintf(8.6F) == 9);
	assert(rintl(8.6L) == 9);
 	assert(lrint(8.6) == 9L);
 	assert(lrintf(8.6F) == 9L);
 	assert(llrint(8.6) == 9LL);
 	assert(llrintf(8.6F) == 9LL);

	assert(lrint(0.0) == 0L);
	assert(lrintf(0.0) == 0L);
	assert(lrint(-0.0) == 0L);
	assert(lrintf(-0.0) == 0L);

	assert(llrint(4503599627370496.0) == 4503599627370496LL);
	assert(llrintf(4503599627370496.0F) == 4503599627370496LL);
	assert(llrint(-4503599627370496.0) == -4503599627370496LL);
	assert(llrintf(-4503599627370496.0F) == -4503599627370496LL);

	assert(llrint(0x7ffffffffffffc00.0p0) == 0x7ffffffffffffc00LL);
	assert(llrintf(0x7fffff8000000000.0p0F) == 0x7fffff8000000000LL);
	assert(llrint(-0x8000000000000000.0p0) == -0x8000000000000000LL);
	assert(llrintf(-0x8000000000000000.0p0F) == -0x8000000000000000LL);

	fpsetround(FP_RM);
	assert(lrint(-0.1) == -1L);
	assert(lrintf(-0.1) == -1L);

	fpsetround(FP_RP);
	assert(lrint(0.1) == 1L);
	assert(lrintf(0.1) == 1L);

	exit(0);
}