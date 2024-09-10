int main(int argc, char *argv[])

{
  char *header, *hptr;
  int  dohdr = 0, dopixel = 0, doworld = 0;
  int  i, nkeyrec, nreject, nwcs, stat[NWCSFIX], status = 0;
  double imgcrd[2], phi, pixcrd[2], theta, world[2];
  fitsfile *fptr;
  struct wcsprm *wcs;


  /* Parse options. */
  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (!argv[i][1]) break;

    switch (argv[i][1]) {
    case 'h':
      dohdr = 1;
      break;
    case 'p':
      dopixel = 1;
      break;
    case 'w':
      doworld = 1;
      break;
    default:
      fprintf(stderr, "Usage: twcshdr [-h | -p | -w] <file>\n");
      return 1;
    }
  }

  if (i != (argc-1)) {
    fprintf(stderr, "Usage: twcshdr [-h | -p | -w] <file>\n");
    return 1;
  }

  /* Open the FITS test file and read the primary header. */
  fits_open_file(&fptr, argv[i], READONLY, &status);
  if ((status = fits_hdr2str(fptr, 1, NULL, 0, &header, &nkeyrec, &status))) {
    fits_report_error(stderr, status);
    return 1;
  }


  /*-----------------------------------------------------------------------*/
  /* Basic steps required to interpret a FITS WCS header, including -TAB.  */
  /*-----------------------------------------------------------------------*/

  /* Parse the primary header of the FITS file. */
  if ((status = wcspih(header, nkeyrec, WCSHDR_all, 2, &nreject, &nwcs,
                       &wcs))) {
    fprintf(stderr, "wcspih ERROR %d: %s.\n", status,wcshdr_errmsg[status]);
  }

  /* Read coordinate arrays from the binary table extension. */
  if ((status = fits_read_wcstab(fptr, wcs->nwtb, (wtbarr *)wcs->wtb,
                                 &status))) {
    fits_report_error(stderr, status);
    return 1;
  }

  /* Translate non-standard WCS keyvalues. */
  if ((status = wcsfix(7, 0, wcs, stat))) {
    for (i = 0; i < NWCSFIX; i++) {
      if (stat[i] > 0) {
        fprintf(stderr, "wcsfix ERROR %d: %s.\n", status,
                wcsfix_errmsg[stat[i]]);
      }
    }

    return 1;
  }

  /*-----------------------------------------------------------------------*/
  /* The wcsprm struct is now ready for use.                               */
  /*-----------------------------------------------------------------------*/

  /* Finished with the FITS file. */
  fits_close_file(fptr, &status);
  free(header);

  /* Initialize the wcsprm struct, also taking control of memory allocated by
   * fits_read_wcstab(). */
  if ((status = wcsset(wcs))) {
    fprintf(stderr, "wcsset ERROR %d: %s.\n", status, wcs_errmsg[status]);
    return 1;
  }

  if (dohdr) {
    if ((status = wcshdo(WCSHDO_all, wcs, &nkeyrec, &header))) {
      return 1;
    }

    hptr = header;
    printf("\n\n");
    for (i = 0; i < nkeyrec; i++, hptr += 80) {
      printf("%.80s\n", hptr);
    }

    free(header);

  } else if (dopixel) {
    while (1) {
      printf("Enter pixel coordinates: ");
      if (scanf("%lf%*[ ,]%lf", pixcrd, pixcrd+1) != wcs->naxis) break;
      status = wcsp2s(wcs, 1, 2, pixcrd, imgcrd, &phi, &theta, world, stat);
      printf("  (%20.15f, %20.15f) ->\n  (%20.15f, %20.15f)\n\n",
        pixcrd[0], pixcrd[1], world[0], world[1]);
    }

  } else if (doworld) {
    while (1) {
      printf("Enter world coordinates: ");
      if (scanf("%lf%*[ ,]%lf", world, world+1) != wcs->naxis) break;
      status = wcss2p(wcs, 1, 2, world, &phi, &theta, imgcrd, pixcrd, stat);
      printf("  (%20.15f, %20.15f) ->\n  (%20.15f, %20.15f)\n\n",
        world[0], world[1], pixcrd[0], pixcrd[1]);
    }

  } else {
    /* Print the struct. */
    if ((status = wcsprt(wcs))) {
      return 1;
    }
  }

  /* Clean up. */
  status = wcsvfree(&nwcs, &wcs);

  return 0;
}