void Main ()
{
	int i, p, c, r;

	for (i = 0, p = Getpid (); i < NUMPROCS; i++, p = c) {
		Printf ("%d about to fork\n", Getpid ());
		if ((c = Fork ()) == 0) {
			Printf ("%d starting\n", Getpid ());
			handoff (p);
			Printf ("%d exiting\n", Getpid ());
			Exit ();
		}
		Printf ("%d just forked %d\n", Getpid (), c);
	}

	Printf ("%d yielding to %d\n", Getpid (), c);
	r = Yield (c);
	Printf ("%d resumed by %d, yielding to %d\n", Getpid (), r, c);
	Yield (c);
	Printf ("%d exiting\n", Getpid ());
}