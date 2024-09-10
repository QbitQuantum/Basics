int main(int argc, char **argv)
{
	int		arg;
	char		*argp;
	giant		*g1;
	giant		*g2;		// ditto
	unsigned char	*buf;		// random data
	unsigned	numDigits;
	unsigned	i;
	unsigned	numBytes;
	unsigned	mulgElapsed;
	unsigned	sqrElapsed;
	
	int 		loops = LOOPS_DEF;
	int		seedSpec = 0;
	unsigned	seed = 0;
	unsigned	maxSize = MAX_SIZE_DEF;
	unsigned	minSize = MIN_SIZE_DEF;
	int 		useOld = 0;
	
	initCryptKit();
	
	#if	macintosh
	argc = ccommand(&argv);
	#endif
	
	for(arg=1; arg<argc; arg++) {
		argp = argv[arg];
		switch(argp[0]) {
		    case 'x':
		    	maxSize = atoi(&argp[2]);
			break;
		    case 'n':
		    	minSize = atoi(&argp[2]);
			break;
		    case 'l':
		    	loops = atoi(&argp[2]);
			break;
		    case 'o':
		    	useOld = 1;
			break;
		    case 's':
			seed = atoi(&argp[2]);
			seedSpec = 1;
			break;
		    case 'h':
		    default:
		    	usage(argv);
		}
	}
	buf = malloc(maxSize);

	if(!seedSpec) {
		unsigned long	tim;
		time(&tim);
		seed = (unsigned)tim;
	}
	SRAND(seed);

	/*
	 * Scratch giants, big enough for anything. Malloc here, init with
	 * random data before each test
	 * note these mallocs will be too big in the useOld case...
	 */
	g1 = malloc(sizeof(giant) * loops);
	g2 = malloc(sizeof(giant) * loops);
    if((g1 == NULL) || (g2 == NULL)) {
    	printf("malloc error\n");
    	exit(1);
    }
	if(useOld) {
	    numDigits = ((2 * maxSize) + 1) / 2;
	}
	else {
	    numDigits = BYTES_TO_GIANT_DIGITS(2 * maxSize);
	}
	for(i=0; i<loops; i++) {
	    g1[i] = newGiant(numDigits);
	    g2[i] = newGiant(numDigits);
	    if((g1[i] == NULL) || (g2[i] == NULL)) {
	    	printf("malloc error\n");
	    	exit(1);
	    }
	}

	printf("Starting giants test: seed %d\n", seed);
	for(numBytes=minSize; numBytes<=maxSize; numBytes*=2) {
		    
		initRandGiants(numBytes, 
			buf,
			loops,
			g1, 
			g2);

		mulgElapsed = mulgTest(loops, g1, g2);
		initRandGiants(numBytes, 
			buf,
			loops,
			g1, 
			g2);

		sqrElapsed = squareTest(loops, g1, g2);
		printf("  bits : %4d   mulg : %3d ns   gsquare : %3d ns\n", 
			numBytes * 8, 
			mulgElapsed / loops,
			sqrElapsed / loops);

	} /* for numBytes */
	return 0;
}