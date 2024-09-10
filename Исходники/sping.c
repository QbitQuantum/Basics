int main (int argc, char *argv[])
{
	double t,tv[2];
	int reps = DFLT_REPS;
	int doprint = 1/*0*/;
	char *progName;
	int minWords;
	int maxWords;
	int incWords, nwords, nproc, proc, peer, c, r, i;
	long *rbuf;	/* remote buffer - sink */
	long *tbuf;	/* transmit buffer - src */

	start_pes(0);
	proc = _my_pe();
	nproc = _num_pes();
	if (nproc == 1) {
		fprintf(stderr, "ERR - Requires > 1 Processing Elements\n");
		return 1;
	}

	for (progName = argv[0] + strlen(argv[0]);
		 progName > argv[0] && *(progName - 1) != '/';
		 progName--)
		;

	while ((c = getopt (argc, argv, "n:evh")) != -1)
		switch (c)
		{
		case 'n':
			if ((reps = getSize (optarg)) <= 0)
				usage (progName);
			break;
		case 'e':
			doprint++;
			break;
		case 'v':
			Verbose++;
			break;
		case 'h':
			help (progName);
		default:
			usage (progName);
		}

	if (optind == argc)
		minWords = DFLT_MIN_WORDS;
	else if ((minWords = getSize (argv[optind++])) <= 0)
		usage (progName);

	if (optind == argc)
		maxWords = minWords;
	else if ((maxWords = getSize (argv[optind++])) < minWords)
		usage (progName);

	if (optind == argc)
		incWords = 0;
	else if ((incWords = getSize (argv[optind++])) < 0)
		usage (progName);

	if (!(rbuf = (long *)shmalloc(maxWords * sizeof(long))))
	{
		perror ("Failed memory allocation");
		exit (1);
	}
	memset (rbuf, 0, maxWords * sizeof (long));

	if (!(tbuf = (long *)shmalloc(maxWords * sizeof(long))))
	{
		perror ("Failed memory allocation");
		exit (1);
	}

	for (i = 0; i < maxWords; i++)
		tbuf[i] = 1000 + (i & 255);

	if (doprint)
		printf ("%d(%d): Shmem PING reps %d minWords %d maxWords %d "
				"incWords %d\n",
				proc, nproc, reps, minWords, maxWords, incWords);

        dprint("[%d] rbuf: %ld\n", proc, (unsigned long) rbuf);

	shmem_barrier_all();

	peer = proc ^ 1;
	if (peer >= nproc)
		doprint = 0;

	for (nwords = minWords;
		 nwords <= maxWords;
		 nwords = incWords ? nwords + incWords : nwords ? 2 * nwords : 1)
	{
		r = reps;
		shmem_barrier_all();
		tv[0] = gettime();
		if (peer < nproc)
		{
			if (proc & 1)
			{
				r--;
				shmem_wait(&rbuf[nwords-1], 0);
				rbuf[nwords-1] = 0;
			}

			while (r-- > 0)
			{
				shmem_long_put(rbuf, tbuf, nwords, peer);
				shmem_wait(&rbuf[nwords-1], 0);
				rbuf[nwords-1] = 0;
			}

			if (proc & 1)
			{
				shmem_long_put(rbuf, tbuf, nwords, peer);
			}
		}
		tv[1] = gettime();
		t = dt (&tv[1], &tv[0]) / (2 * reps);

		shmem_barrier_all();

		printStats (proc, peer, doprint, nwords, t);
	}

    shfree(rbuf);
    shfree(tbuf);

	shmem_barrier_all();
	return 0;
}