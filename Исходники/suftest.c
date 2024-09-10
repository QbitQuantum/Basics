int
main(int argc, const char *argv[]) {
  FILE *fp;
  sauchar_t *T;
  saidx_t *SA;
  saidx_t n;
  clock_t start, finish;
#if HAVE_SYS_STAT_H
  struct stat s;
#endif

  /* Check argument. */
  if((argc != 2) ||
     (strcmp(argv[1], "-h") == 0) ||
     (strcmp(argv[1], "--help") == 0)) {
    fprintf(stderr,
      "suftest, a suffixsort tester, version %s.\n"
      , divsufsort_version());
    fprintf(stderr,
      "usage: %s FILE\n\n"
      , argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Get a file's status information. */
#if HAVE_SYS_STAT_H
  if(stat(argv[1], &s) != 0) {
    fprintf(stderr, "%s: Cannot stat file `%s': ", argv[0], argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  n = s.st_size;
#endif

  /* Open a file for reading. */
  if((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "%s: Cannot open file `%s': ", argv[0], argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

#if !HAVE_SYS_STAT_H
  fseek(fp, 0, SEEK_END);
  n = ftell(fp);
  rewind(fp);
#endif

  /* Allocate n+4(n+1) bytes of memory. */
  if(((T = malloc(n * sizeof(sauchar_t))) == NULL) ||
     ((SA = malloc((n + 1) * sizeof(saidx_t))) == NULL)) {
    fprintf(stderr, "%s: Cannot allocate memory.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Read n bytes of data. */
  if(fread(T, sizeof(sauchar_t), n, fp) != n) {
    fprintf(stderr, "%s: %s `%s': ",
      argv[0],
      (ferror(fp) || !feof(fp)) ? "Cannot read from" : "Unexpected EOF in",
      argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  fclose(fp);

  /* Construct the suffix array. */
  fprintf(stderr, "%s: %d bytes ... ", argv[1], (int)n);
  start = clock();
  divsufsort(T, SA, n);
  finish = clock();
  fprintf(stderr, "%.4f sec\n",
    (double)(finish - start) / (double)CLOCKS_PER_SEC);

  /* Check the suffix array. */
  if(sufcheck(T, SA, n, 3) != 0) {
    exit(EXIT_FAILURE);
  }

  /* Deallocate memory. */
  free(SA);
  free(T);

  return 0;
}