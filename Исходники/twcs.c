int main()

{
#define NELEM 9

  char   ok[] = "", mismatch[] = " (WARNING, mismatch)", *s;
  int    i, k, lat, lng, nFail1 = 0, nFail2 = 0, stat[361], status;
  double freq, img[361][NELEM], lat1, lng1, phi[361], pixel1[361][NELEM],
         pixel2[361][NELEM], r, resid, residmax, theta[361], time,
         world1[361][NELEM], world2[361][NELEM];
  struct wcsprm *wcs;


  printf("Testing closure of WCSLIB world coordinate transformation "
         "routines (twcs.c)\n"
         "----------------------------------------------------------"
         "-----------------\n");

  /* List status return messages. */
  printf("\nList of wcs status return values:\n");
  for (status = 1; status <= 13; status++) {
    printf("%4d: %s.\n", status, wcs_errmsg[status]);
  }

  printf("\nSize of data types (bytes):\n");
  printf("           char:%5"MODZ"u\n", sizeof(char));
  printf("      short int:%5"MODZ"u\n", sizeof(short int));
  printf("            int:%5"MODZ"u\n", sizeof(int));
  printf("       long int:%5"MODZ"u\n", sizeof(long int));
  printf("          float:%5"MODZ"u\n", sizeof(float));
  printf("         double:%5"MODZ"u\n", sizeof(double));
  printf("         char *:%5"MODZ"u\n", sizeof(char *));
  printf("   char (*)[72]:%5"MODZ"u\n", sizeof(char (*)[72]));
  printf("          int *:%5"MODZ"u\n", sizeof(int *));
  printf("        float *:%5"MODZ"u\n", sizeof(float *));
  printf("       double *:%5"MODZ"u\n", sizeof(double *));
  printf("struct pvcard *:%5"MODZ"u\n", sizeof(struct pvcard *));
  printf("struct pscard *:%5"MODZ"u\n", sizeof(struct pscard *));

  printf("\nSize of structs (bytes/ints):\n");

  s = (sizeof(struct celprm) == sizeof(int)*CELLEN) ? ok : mismatch;
  printf("         celprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct celprm),
         CELLEN, s);

  s = (sizeof(struct fitskey) == sizeof(int)*KEYLEN) ? ok : mismatch;
  printf("        fitskey:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct fitskey),
         KEYLEN, s);

  s = (sizeof(struct fitskeyid) == sizeof(int)*KEYIDLEN) ? ok : mismatch;
  printf("      fitskeyid:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct fitskeyid),
         KEYIDLEN, s);

  s = (sizeof(struct linprm) == sizeof(int)*LINLEN) ? ok : mismatch;
  printf("         linprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct linprm),
         LINLEN, s);

  s = (sizeof(struct prjprm) == sizeof(int)*PRJLEN) ? ok : mismatch;
  printf("         prjprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct prjprm),
         PRJLEN, s);

  s = (sizeof(struct spcprm) == sizeof(int)*SPCLEN) ? ok : mismatch;
  printf("         spcprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct spcprm),
         SPCLEN, s);

  s = (sizeof(struct spxprm) == sizeof(int)*SPXLEN) ? ok : mismatch;
  printf("         spxprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct spxprm),
         SPXLEN, s);

  s = (sizeof(struct tabprm) == sizeof(int)*TABLEN) ? ok : mismatch;
  printf("         tabprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct tabprm),
         TABLEN, s);

  s = (sizeof(struct wcserr) == sizeof(int)*ERRLEN) ? ok : mismatch;
  printf("         wcserr:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct wcserr),
         ERRLEN, s);

  s = (sizeof(struct wcsprm) == sizeof(int)*WCSLEN) ? ok : mismatch;
  printf("         wcsprm:%5"MODZ"u /%4"MODZ"u%s\n", sizeof(struct wcsprm),
         WCSLEN, s);


  /* Set the PVi_ma keyvalues for the longitude axis.         */
  /*----------------------------------------------------------*/
  /* For test purposes, these are set so that the fiducial    */
  /* native coordinates are at the native pole, i.e. so that  */
  /* (phi0,theta0) = (0,90), but without any fiducial offset, */
  /* i.e. iwith PVi_0a == 0 (by default).                     */
  /*----------------------------------------------------------*/
  PV[0].i = 4;			/* Longitude is on axis 4.     */
  PV[0].m = 1;			/* Parameter number 1.         */
  PV[0].value =  0.0;		/* Fiducial native longitude.  */

  PV[1].i = 4;			/* Longitude is on axis 4.     */
  PV[1].m = 2;			/* Parameter number 2.         */
  PV[1].value = 90.0;		/* Fiducial native latitude.   */

  /* Set the PVi_m keyvaluess for the latitude axis.          */
  PV[2].i = 2;			/* Latitude is on axis 2.      */
  PV[2].m = 1;			/* Parameter number 1.         */
  PV[2].value = -30.0;		/* PVi_1.                      */


  /* The following routine simulates the actions of a FITS header parser. */
  wcs = malloc(sizeof(struct wcsprm));
  wcs->flag = -1;
  parser(wcs);

  printf("\nReporting tolerance %5.1g pixel.\n", tol);


  /* Initialize non-celestial world coordinates. */
  time = 1.0;
  freq = 1.42040595e9 - 180.0 * 62500.0;
  for (k = 0; k < 361; k++) {
    world1[k][0] = 0.0;
    world1[k][1] = 0.0;
    world1[k][2] = 0.0;
    world1[k][3] = 0.0;

    world1[k][2] = time;
    time *= 1.01;

    world1[k][wcs->spec] = 2.99792458e8 / freq;
    freq += 62500.0;
  }

  residmax = 0.0;
  for (lat = 90; lat >= -90; lat--) {
    lat1 = (double)lat;

    for (lng = -180, k = 0; lng <= 180; lng++, k++) {
      lng1 = (double)lng;

      world1[k][wcs->lng] = lng1;
      world1[k][wcs->lat] = lat1;
    }

    if (wcss2p(wcs, 361, NELEM, world1[0], phi, theta, img[0], pixel1[0],
               stat)) {
      printf("  At wcss2p#1 with lat1 == %f\n", lat1);
      wcsperr(wcs, "  ");
      continue;
    }

    if (wcsp2s(wcs, 361, NELEM, pixel1[0], img[0], phi, theta, world2[0],
               stat)) {
      printf("  At wcsp2s with lat1 == %f\n", lat1);
      wcsperr(wcs, "  ");
      continue;
    }

    if (wcss2p(wcs, 361, NELEM, world2[0], phi, theta, img[0], pixel2[0],
               stat)) {
      printf("  At wcss2p#2 with lat1 == %f\n", lat1);
      wcsperr(wcs, "  ");
      continue;
    }

    for (k = 0; k < 361; k++) {
      resid = 0.0;
      for (i = 0; i < NAXIS; i++) {
        r = pixel2[k][i] - pixel1[k][i];
        resid += r*r;
      }

      resid = sqrt(resid);
      if (resid > residmax) residmax = resid;

      if (resid > tol) {
        nFail1++;
        printf("\nClosure error:\n"
               "world1:%18.12f%18.12f%18.12f%18.12f\n"
               "pixel1:%18.12f%18.12f%18.12f%18.12f\n"
               "world2:%18.12f%18.12f%18.12f%18.12f\n"
               "pixel2:%18.12f%18.12f%18.12f%18.12f\n",
          world1[k][0], world1[k][1], world1[k][2], world1[k][3],
          pixel1[k][0], pixel1[k][1], pixel1[k][2], pixel1[k][3],
          world2[k][0], world2[k][1], world2[k][2], world2[k][3],
          pixel2[k][0], pixel2[k][1], pixel2[k][2], pixel2[k][3]);
       }
    }
  }

  printf("wcsp2s/wcss2p: Maximum closure residual = %.1e pixel.\n", residmax);


  /* Test wcserr and wcsprintf() as well. */
  nFail2 = 0;
  wcsprintf_set(stdout);
  wcsprintf("\n\nIGNORE messages marked with 'OK', they test wcserr "
    "(and wcsprintf):\n");

  wcserr_enable(1);

  /* Test 1. */
  wcs->pv[2].value = UNDEFINED;
  status = wcsset(wcs);
  nFail2 += check_error(wcs, status, WCSERR_BAD_PARAM,
                        "Invalid parameter value");

  nFail2 += test_errors();


  if (nFail1 || nFail2) {
    if (nFail1) {
      printf("\nFAIL: %d closure residuals exceed reporting tolerance.\n",
        nFail1);
    }

    if (nFail2) {
      printf("FAIL: %d error messages differ from that expected.\n", nFail2);
    }
  } else {
    printf("\nPASS: All closure residuals are within reporting tolerance.\n");
    printf("PASS: All error messages reported as expected.\n");
  }


  /* Clean up. */
  wcsfree(wcs);
  free(wcs);

  return nFail1 + nFail2;
}