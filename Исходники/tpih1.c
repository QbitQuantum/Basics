int main()

{
  char infile[] = "pih.fits";
  char a, *hptr;
  int  alts[27], ctrl, ialt, iblock, ifix, ikeyrec, iwcs, nkeyrec, nreject,
       nwcs, relax, stat[NWCSFIX], status;
  struct wcsprm *wcs;
#if defined HAVE_CFITSIO && defined DO_CFITSIO
  char *header;
  fitsfile *fptr;
#else
  char keyrec[81], header[288001];
  int  gotend, k;
  FILE *fptr;
#endif


  /* Set line buffering in case stdout is redirected to a file, otherwise
   * stdout and stderr messages will be jumbled (stderr is unbuffered). */
  setvbuf(stdout, NULL, _IOLBF, 0);

  printf("Testing WCSLIB parser for FITS image headers (tpih1.c)\n"
         "------------------------------------------------------\n\n");

  /* Read in the FITS header, excluding COMMENT and HISTORY keyrecords. */
#if defined HAVE_CFITSIO && defined DO_CFITSIO
  status = 0;
  if (fits_open_file(&fptr, infile, READONLY, &status)) {
    fits_report_error(stderr, status);
    return 1;
  }

  if (fits_hdr2str(fptr, 1, NULL, 0, &header, &nkeyrec, &status)) {
    fits_report_error(stderr, status);
    return 1;
  }

  fits_close_file(fptr, &status);
#else
  if ((fptr = fopen(infile, "r")) == 0) {
    fprintf(stderr, "ERROR opening %s\n", infile);
    return 1;
  }

  k = 0;
  nkeyrec = 0;
  gotend = 0;
  for (iblock = 0; iblock < 100; iblock++) {
    for (ikeyrec = 0; ikeyrec < 36; ikeyrec++) {
      if (fgets(keyrec, 81, fptr) == 0) {
        break;
      }

      if (strncmp(keyrec, "        ", 8) == 0) continue;
      if (strncmp(keyrec, "COMMENT ", 8) == 0) continue;
      if (strncmp(keyrec, "HISTORY ", 8) == 0) continue;

      strncpy(header+k, keyrec, 80);
      k += 80;
      nkeyrec++;

      if (strncmp(keyrec, "END     ", 8) == 0) {
        /* An END keyrecord was read, but read the rest of the block. */
        gotend = 1;
      }
    }

    if (gotend) break;
  }
  fclose(fptr);
#endif

  fprintf(stderr, "Found %d non-comment header keyrecords.\n\n", nkeyrec);


  /* Parse the header, allowing all recognized non-standard WCS keywords and
   * usage.  All WCS keyrecords are culled from the header, illegal ones are
   * reported. */
  relax = WCSHDR_all;
  ctrl  = -2;
  fprintf(stderr, "\nIllegal or extraneous WCS header keyrecords rejected "
                  "by wcspih():\n");
  if ((status = wcspih(header, nkeyrec, relax, ctrl, &nreject, &nwcs,
                       &wcs))) {
    fprintf(stderr, "wcspih ERROR %d: %s.\n", status, wcs_errmsg[status]);
  }
  if (!nreject) fprintf(stderr, "(none)\n");


  /* List the remaining keyrecords. */
  printf("\n\nNon-WCS header keyrecords ignored by wcspih():\n");
  hptr = header;
  while (*hptr) {
    printf("%.80s\n", hptr);
    hptr += 80;
  }
#if defined HAVE_CFITSIO && defined DO_CFITSIO
  free(header);
#endif


  /* Summarize what was found. */
  status = wcsidx(nwcs, &wcs, alts);
  printf("\n\nFound %d alternate coordinate descriptions with indices:\n  ",
         nwcs);
  for (a = 'A'; a <= 'Z'; a++) {
    printf("%2c", a);
  }
  printf("\n");
  for (ialt = 0; ialt < 27; ialt++) {
    if (alts[ialt] < 0) {
      printf(" -");
    } else {
      printf("%2d", alts[ialt]);
    }
  }
  printf("\n");


  /* Fix non-standard usage and print each of the wcsprm structs.  The output
   * from wcsprt() will be written to an internal buffer and then printed just
   * to show that it can be done. */
  wcsprintf_set(0x0);
  for (iwcs = 0; iwcs < nwcs; iwcs++) {
    wcsprintf("\n------------------------------------"
              "------------------------------------\n");

    /* Fix non-standard WCS keyvalues. */
    if ((status = wcsfix(7, 0, wcs+iwcs, stat))) {
      printf("wcsfix ERROR, status returns: (");
      for (ifix = 0; ifix < NWCSFIX; ifix++) {
        printf(ifix ? ", %d" : "%d", stat[ifix]);
      }
      printf(")\n\n");
    }

    if ((status = wcsset(wcs+iwcs))) {
      fprintf(stderr, "wcsset ERROR %d: %s.\n", status, wcs_errmsg[status]);
      continue;
    }

    if ((status = wcsprt(wcs+iwcs))) {
      fprintf(stderr, "wcsprt ERROR %d: %s.\n", status, wcs_errmsg[status]);
    }
  }
  printf("%s", wcsprintf_buf());

  status = wcsvfree(&nwcs, &wcs);

  return 0;
}