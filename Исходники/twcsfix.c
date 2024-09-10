int main()

{
  char ctypeS[9];
  int i, stat[NWCSFIX], status;
  struct wcsprm wcs;
  struct wcserr info[NWCSFIX];

  wcsprintf("Testing WCSLIB translator for non-standard usage (twcsfix.c)\n"
          "------------------------------------------------------------\n\n");

  wcs.flag = -1;
  parser(&wcs);

  /* Note: to print the unfixed wcsprm struct using wcsprt() the struct
     would first have to be initialized by wcsset().  However, if the struct
     contains non-standard keyvalues then wcsset() will either fix them
     itself or else fail (e.g. for non-standard units).  Thus, in general,
     wcsprt() cannot be used to print the unmodified struct. */

  /* Fix non-standard WCS keyvalues. */
  wcserr_enable(1);
  status = wcsfixi(7, 0, &wcs, stat, info);
  wcsprintf("wcsfix status returns: (");
  for (i = 0; i < NWCSFIX; i++) {
    wcsprintf(i ? ", %d" : "%d", stat[i]);
  }
  wcsprintf(")\n");

  for (i = 0; i < NWCSFIX; i++) {
    if (info[i].status < -1 || 0 < info[i].status) {
      wcsprintf("\n");
      wcserr_prt(info+i, 0x0);
    }
  }

  if (status) {
    wcsprintf("\nwcsfix error %d", status);
    return 1;
  }

  /* Extract information from the FITS header. */
  if (wcsset(&wcs)) {
    wcsprintf("\n");
    wcserr_prt(wcs.err, 0x0);
  }

  wcsprintf("\n");
  wcsprt(&wcs);
  wcsprintf("\n------------------------------------"
            "------------------------------------\n");

  /* Should now have a 'VOPT-F2W' axis, translate it to frequency. */
  strcpy(ctypeS, "FREQ-???");
  i = -1;
  if (wcssptr(&wcs, &i, ctypeS)) {
    wcserr_prt(wcs.err, 0x0);
    return 1;
  }

  if (wcsset(&wcs)) {
    wcserr_prt(wcs.err, 0x0);
    return 1;
  }

  wcsprt(&wcs);

  wcsfree(&wcs);

  return 0;
}