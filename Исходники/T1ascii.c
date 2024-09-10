int main(int argc, char **argv)
{
  int32 length;
  int c, block = 1, last_type = ASCII;

  ifp = stdin;
  ofp = stdout;
  print_banner();

  if (argc > 3)
    usage();

  /* possibly open input & output files */
  if (argc >= 2) {
    ifp = fopen(argv[1], "r");
    if (!ifp) {
      fprintf(stderr, "error: cannot open %s for reading\n", argv[1]);
      exit(1);
    }
  }
  if (argc == 3) {
    ofp = fopen(argv[2], "w");
    if (!ofp) {
      fprintf(stderr, "error: cannot open %s for writing\n", argv[2]);
      exit(1);
    }
  }

  #ifdef _MSDOS
    /* As we are processing a PFB (binary) input */
    /* file, we must set its file mode to binary. */
    _setmode(_fileno(ifp), _O_BINARY);
  #endif

  /* main loop through blocks */

  for (;;) {
    c = fgetc(ifp);
    if (c == EOF) {
      break;
    }
    if (c != MARKER) {
      fprintf(stderr,
              "error:  missing marker (128) at beginning of block %d",
              block);
      exit(1);
    }
    switch (c = fgetc(ifp)) {
    case ASCII:
      if (last_type != ASCII)
        fputc('\n', ofp);
      last_type = ASCII;
      for (length = read_length(); length > 0; length--)
        if ((c = fgetc(ifp)) == '\r')
          fputc('\n', ofp);
        else
          fputc(c, ofp);
      break;
    case BINARY:
      last_type = BINARY;
      for (length = read_length(); length > 0; length--)
        output_hex(fgetc(ifp));
      break;
    case DONE:
      /* nothing to be done --- will exit at top of loop with EOF */
      break;
    default:
      fprintf(stderr, "error: bad block type %d in block %d\n",
              c, block);
      break;
    }
    block++;
  }
  fclose(ifp);
  fclose(ofp);
  syncfs("/");
  return 0;
}