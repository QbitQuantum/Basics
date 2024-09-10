void dump2file (int signum) {
	static char filename[1024];
	if (!activevents) goto end;
	makename(filename);
	E("creat", creat(filename, 0666));
	// TODO I think creat() will always return 1 here.  Be sure.
	writefile();
	close(1);
	activevents = 0; // Removes all events.
 end:
	alarm(timeout);
	signal(SIGALRM, dump2file); }