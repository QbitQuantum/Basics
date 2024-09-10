int do_wcs_stuff(fitsfile *fptr, struct wcsprm *wcs)

{
  int    i1, i2, i3, k, naxis1, naxis2, naxis3, stat[8], status;
  double phi[8], pixcrd[8][4], imgcrd[8][4], theta[8], world[8][4],
         x1, x2, x3;

  /* Initialize the wcsprm struct, also taking control of memory allocated by
   * fits_read_wcstab(). */
  if ((status = wcsset(wcs))) {
    fprintf(stderr, "wcsset ERROR %d: %s.\n", status, wcs_errmsg[status]);
    return 1;
  }

  /* Print the struct. */
  if ((status = wcsprt(wcs))) return status;

  /* Compute coordinates in the corners. */
  fits_read_key(fptr, TINT, "NAXIS1", &naxis1, NULL, &status);
  fits_read_key(fptr, TINT, "NAXIS2", &naxis2, NULL, &status);
  fits_read_key(fptr, TINT, "NAXIS3", &naxis3, NULL, &status);

  k = 0;
  x3 = 1.0f;
  for (i3 = 0; i3 < 2; i3++) {
    x2 = 0.5f;

    for (i2 = 0; i2 < 2; i2++) {
      x1 = 0.5f;

      for (i1 = 0; i1 < 2; i1++) {
        pixcrd[k][0] = x1;
        pixcrd[k][1] = x2;
        pixcrd[k][2] = x3;
        pixcrd[k][3] = 1.0f;

        k++;
        x1 = naxis1 + 0.5f;
      }

      x2 = naxis2 + 0.5f;
    }

    x3 = naxis3;
  }

  if ((status = wcsp2s(wcs, 8, 4, pixcrd[0], imgcrd[0], phi, theta, world[0],
                       stat))) {
    fprintf(stderr, "\n\nwcsp2s ERROR %d: %s.\n", status,
            wcs_errmsg[status]);

    /* Invalid pixel coordinates. */
    if (status == 8) status = 0;
  }

  if (status == 0) {
    printf("\n\nCorner world coordinates:\n"
           "            Pixel                              World\n");
    for (k = 0; k < 8; k++) {
      printf("  (%5.1f,%6.1f,%4.1f,%4.1f) -> (%7.3f,%8.3f,%9g,%11.5f)",
             pixcrd[k][0], pixcrd[k][1], pixcrd[k][2], pixcrd[k][3],
             world[k][0],  world[k][1],  world[k][2],  world[k][3]);
      if (stat[k]) printf("  (BAD)");
      printf("\n");
    }
  }

  return 0;
}