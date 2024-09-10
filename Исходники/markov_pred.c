int main(int argc, char **argv)
{
  char *exeName = argv[0];
  char *seqA;
  int lenA;
  int markovOrder = 0;
  char *markovFile = NULL;
  char *markovSaveFile = NULL;

  while (1) {
    int c = getopt(argc, argv, "m:f:s:h");
    if (c==-1)
      break;
    switch (c) {
    case 'm':
      markovOrder = atoi(optarg);
      break;
    case 'f':
      markovFile = optarg;
      break;
    case 's':
      markovSaveFile = optarg;
      break;
    case 'h':
    default:
      usage(exeName);
    }
  }
	
  argc -= optind-1;
  argv += optind-1;

  if (argc != 2) {
    usage(exeName);
  } else {
    seqA = read_fasta(argv[1]);
  } 

  lenA = strlen(seqA);

  printf("# Character prediction probability for FASTA file '%s'\n", argv[1]);
  printf("# Markov order = %d\n", markovOrder);
  printf("# Column order = [%s]\n", alphabet);

  {
    int i,j;
    unsigned char seqA_i[lenA];
    DOUBLE seqA_enc[lenA][ALPHA_SIZE];

    // Convert DNA sequence to only an A G C or T
    strict_DNA_seq(seqA, lenA);

    // First convert strings to numbers representing the characters
    for (i=0; i<lenA; i++) seqA_i[i] = char2int(seqA[i]);
  

    markov_init(ALPHA_SIZE, markovOrder);
    if (markovFile)
      markov_load(markovFile);
    else
      markov_fit(lenA, seqA_i);
    
    markov_predict(lenA, seqA_i, (DOUBLE*)seqA_enc);


    for (i=0; i<lenA; i++) {
      for (j=0; j<ALPHA_SIZE; j++) {
	printf("%f ", exp2(-seqA_enc[i][j]));
      }
      printf("\n");
    }

    if (markovSaveFile) {
      FILE *f = fopen(markovSaveFile, "w");
      if (!f) {
        fprintf(stderr, "Unable to open file '%s' for writing.\n", markovSaveFile);
      } else {
        fprintf(stderr, "Saving Markov Model parameters to file '%s'\n", markovSaveFile);
        markov_save(f);
      }
    }

  }

  return 0;
}