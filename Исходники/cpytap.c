/*++
 *      main
 *
 *  Entry point for cpytap program.
 *
 * Inputs:
 *
 *      argc            - # of supplied arguments
 *      argv            - Array of argument strings
 *
 * Outputs:
 *
 *      None
 *
 * Returns:
 *
 *      Exit status for cpytap
 *
 --*/
int main(
  int argc,
  char *argv[]
)
{
  int ch, i, filenumber = 1, filenum;
  char *filename;

  if (argc < 3)
    usage();

  srcfile = argv[1];
  dstfile = argv[2];
  argc -= 2;
  argv += 2;

  memset(fileops, 0, sizeof(fileops));
  memset(&appendops, 0, sizeof(appendops));

  while ((ch = getopt(argc, argv, "r:A:I:R:S:")) != -1) {
    switch (ch) {
      case 'r':
        reclen = strtoul(optarg, NULL, 0);
        if (reclen < MINRECLEN)
          reclen = MINRECLEN;
        if (reclen > MAXRECLEN)
          reclen = MAXRECLEN;
    done:
        break;

      case 'A':
        for (i = 0; i < APPFILES; i++) {
          if (appendops.insfiles[i].filename == NULL) {
            appendops.insfiles[i].reclen = reclen;
            appendops.insfiles[i].filename = argv[optind];
            goto done;
          }
        }
        fprintf(stderr, "No space for appending file - %s\n", argv[optind]);
        return 5;

      case 'I':
        if (parse(optarg, &filenum, &filename) != 0) {
          fprintf(stderr, "Invalid argument - -I %s\n", optarg);
          return 7;
        }

        for (i = 0; i < APPFILES; i++) {
          if (fileops[filenum].insfiles[i].filename == NULL) {
            fileops[filenum].insfiles[i].reclen = reclen;
            fileops[filenum].insfiles[i].filename = filename;
            goto done;
          }
        }
        fprintf(stderr, "No space for inserting file - %s\n", filename);
        return 5;

      case 'R':
        if (parse(optarg, &filenum, &filename) != 0) {
          fprintf(stderr, "Invalid argument - -R %s\n", optarg);
          return 7;
        }
        if (fileops[filenum].repfile.filename != NULL) {
          fprintf(stderr, "File %u is already being replaced.\n", filenum);
          return 8;
        }
        fileops[filenum].repfile.reclen = reclen;
        fileops[filenum].repfile.filename = filename;
        break;

      case 'S':
        filenum = strtoul(optarg, NULL, 0);
        if ((filenum == 0) || (filenum > MAXFILES)) {
          fprintf(stderr, "Invalid file number - -D %u\n", filenum);
          return 6;
        }
        fileops[filenum].skipfile = 1;
        break;

      case '?':
      default:
        usage();
    }
  }

  /*
   * Begin processing the source tape.
   */
  switch (OpenTapeForRead(&src, srcfile)) {
    case TIO_SUCCESS:
      break;

    case TIO_ERROR:
      fprintf(stderr, "%s has errors and may not copy correctly\n", srcfile);
      break;

    case TIO_CORRUPT:
      fprintf(stderr, "%s is not a SIMH .tap container file\n", srcfile);
      exit(2);

    case TIO_OPENFAIL:
      fprintf(stderr, "%s open failed\n", srcfile);
      exit(3);
  }

  /*
   * Begin processing the destination tape.
   */
  switch (OpenTapeForWrite(&dst, dstfile)) {
    case TIO_SUCCESS:
      break;

    case TIO_IOERROR:
      fprintf(stderr, "Error writing to destination tape - %s\n", dstfile);
      exit(5);

    case TIO_CREATEFAIL:
      fprintf(stderr, "Failed to create destination tape - %s\n", dstfile);
      exit(3);
  }

  /*
   * Process the files on the tape.
   */
  for (;;) {
    if (filenumber <= MAXFILES) {
      struct fileop *op = &fileops[filenumber];

      /*
       * Process possible repalcement.
       */
      if (op->repfile.filename != NULL)
        writeFile(op->repfile.filename, op->repfile.reclen);

      /*
       * Process any insertions before the current file.
       */
      for (i = 0; i < APPFILES; i++)
        if (op->insfiles[i].filename != NULL)
          writeFile(op->insfiles[i].filename, op->insfiles[i].reclen);

      /*
       * Now either copy or skip over the next file on the source tape.
       */
      if ((op->skipfile != 0) || (op->repfile.filename != 0)) {
        if (SkipToNextTapeMark(src) == ST_EOM)
          break;
      } else {
        if (copyFile() == ST_EOM)
          break;
      }
      filenumber++;
    } else {
      /*
       * If there are more than MAXFILES files on the source tape, just copy
       * the remaining files.
       */
      if (copyFile() == ST_EOM)
        break;
    }
  }
  /*
   * Handle any appends
   */
  for (i = 0; i < APPFILES; i++)
    if (appendops.insfiles[i].filename != NULL)
      writeFile(appendops.insfiles[i].filename, appendops.insfiles[i].reclen);

  WriteTapeMark(dst, 0);
  CloseTape(src);
  CloseTape(dst);
  return 0;
}