int
main(int argc, char *argv[])
{
  int i, j, k;
  int sets = 0, countsets = 0, minlen = 0, maxlen = MAXLENGTH, count = 0;
  int set_low = 0, set_up = 0, set_no = 0, set_print = 0, set_other = 0;
  FILE *in = stdin, *out = stdout;
  char buf[MAXLENGTH + 1];

  prg = argv[0];
  if (argc < 2)
    help();

  while ((i = getopt(argc, argv, "i:o:m:M:c:lunps")) >= 0) {
    switch (i) {
    case 'i':
      if ((in = fopen(optarg, "r")) == NULL) {
        fprintf(stderr, "Error: unable to open input file %s\n", optarg);
        exit(-1);
      }
      break;
    case 'o':
      if ((out = fopen(optarg, "w")) == NULL) {
        fprintf(stderr, "Error: unable to open output file %s\n", optarg);
        exit(-1);
      }
      break;
    case 'm':
      minlen = atoi(optarg);
      break;
    case 'M':
      maxlen = atoi(optarg);
      break;
    case 'c':
      countsets = atoi(optarg);
      break;
    case 'l':
      if (set_low == 0) {
        set_low = 1;
        sets++;
      }
      break;
    case 'u':
      if (set_up == 0) {
        set_up = 1;
        sets++;
      }
      break;
    case 'n':
      if (set_no == 0) {
        set_no = 1;
        sets++;
      }
      break;
    case 'p':
      if (set_print == 0) {
        set_print = 1;
        sets++;
      }
      break;
    case 's':
      if (set_other == 0) {
        set_other = 1;
        sets++;
      }
      break;
    default:
      help();
    }
  }
  if (minlen > maxlen) {
    fprintf(stderr, "Error: -m MINLEN is greater than -M MAXLEN\n");
    exit(-1);
  }
  if (countsets > sets) {
    fprintf(stderr, "Error: -c MINSETS is larger than the sets defined\n");
    exit(-1);
  }
  if (countsets == 0)
    countsets = sets;

  while (fgets(buf, sizeof(buf), in) != NULL) {
    i = -1;
    if (buf[0] == 0)
      continue;
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;
    if (strlen(buf) >= minlen && strlen(buf) <= maxlen) {
      i = 0;
      if (countsets > 0) {
        if (set_low)
          if (strpbrk(buf, "abcdefghijklmnopqrstuvwxyz") != NULL)
            i++;
        if (set_up)
          if (strpbrk(buf, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL)
            i++;
        if (set_no)
          if (strpbrk(buf, "0123456789") != NULL)
            i++;
        if (set_print) {
          j = 0;
          for (k = 0; k < strlen(buf); k++)
            if (isprint(buf[k]) && isalnum(buf[k]) == 0)
              j = 1;
          if (j)
            i++;
        }
        if (set_other) {
          j = 0;
          for (k = 0; k < strlen(buf); k++)
            if (isprint(buf[k]) == 0 && isalnum(buf[k]) == 0)
              j = 1;
          if (j)
            i++;
        }
      }
      if (i >= countsets) {
        fprintf(out, "%s\n", buf);
        count++;
      }
    }
    /* fprintf(stderr, "[DEBUG] i: %d  minlen: %d  maxlen: %d  len: %d\n", i, minlen, maxlen, strlen(buf)); */
  }

  return count;
}