/*
 - main - mostly argument parsing
 */
int main(int argc, char *argv[])
{
	int opt;
	extern int optind;
	extern char *optarg;
	int errflg = 0;
	int i;
	int nbits;
	char *oldkeyfile = NULL;

	while ((opt = getopt_long(argc, argv, "", opts, NULL)) != EOF)
		switch (opt) {
		case 'v':	/* verbose description */
			verbose = 1;
			break;
		case 'r':	/* nonstandard /dev/random */
			device = optarg;
			break;
		case 'p':	/* number of prime-check rounds */
			nrounds = atoi(optarg);
			if (nrounds <= 0) {
				fprintf(stderr, "%s: rounds must be > 0\n", me);
				exit(2);
			}
			break;
		case 'o':	/* reformat old key */
			oldkeyfile = optarg;
			break;
		case 'H':	/* set hostname for output */
			strcpy(outputhostname, optarg);
			break;
		case 'n':	/* don't optimize the private key */
			do_lcm = 0;
			break;
		case 'h':	/* help */
			printf("Usage:\t%s\n", usage);
			printf("\tor\n");
			printf("\t%s\n", usage2);
			exit(0);
			break;
		case 'V':	/* version */
			printf("%s ported from openswan 2.4.12\n", me);
			exit(0);
			break;
		case '?':
		default:
			errflg = 1;
			break;
		}
	if (errflg || optind != ((oldkeyfile != NULL) ? argc : argc-1)) {
		printf("Usage:\t%s\n", usage);
		printf("\tor\n");
		printf("\t%s\n", usage2);
		exit(2);
	}

	if (outputhostname[0] == '\0') {
		i = gethostname(outputhostname, sizeof(outputhostname));
		if (i < 0) {
			fprintf(stderr, "%s: gethostname failed (%s)\n",
				me,
				strerror(errno));
			exit(1);
		}
	}

	if (oldkeyfile == NULL) {
		assert(argv[optind] != NULL);
		nbits = atoi(argv[optind]);
	} else
		nbits = getoldkey(oldkeyfile);

	if (nbits <= 0) {
		fprintf(stderr, "%s: invalid bit count (%d)\n", me, nbits);
		exit(1);
	} else if (nbits > MAXBITS) {
		fprintf(stderr, "%s: overlarge bit count (max %d)\n", me,
								MAXBITS);
		exit(1);
	} else if (nbits % (CHAR_BIT*2) != 0) {	/* *2 for nbits/2-bit primes */
		fprintf(stderr, "%s: bit count (%d) not multiple of %d\n", me,
						nbits, (int)CHAR_BIT*2);
		exit(1);
	}

	rsasigkey(nbits, (oldkeyfile == NULL) ? 0 : 1);
	exit(0);
}