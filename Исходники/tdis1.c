int main(int argc, char *argv[])

{
  char *infile = "TPV7.fits";

  char keyrec[81], header[288001], *disfn;
  int  dopoly, gotend, iblock, ikeyrec, inc, itest, j, k, n, naxis[2], naxis1,
       naxis2, nClosure, nFail, nkeyrec, nsamp, nreject, nTest, nwcs, p1, p2,
       status;
  clock_t t0, tp2x, tx2p;
  double absmax, dp1, dp2, *img, *img1, *img2, pix[8], pixblc[2], pixsamp[2],
         pixtrc[2], px, *px0, *px1, pxi[8], rel, resid, relmax;
  double *avgdis, *avgtot, *maxdis, *maxtot, *rmsdis, *rmstot, stats[9];
  FILE   *fptr;
  struct linprm affine, *lin, *linpol, *lintpv;
  struct wcsprm *wcs, wcspol;


  wcserr_enable(1);
  wcsprintf_set(stdout);

  /* Set line buffering in case stdout is redirected to a file, otherwise
   * stdout and stderr messages will be jumbled (stderr is unbuffered). */
  setvbuf(stdout, NULL, _IOLBF, 0);

  wcsprintf("Testing closure of WCSLIB distortion routines (tdis1.c)\n"
            "-------------------------------------------------------\n");

  /* List status return messages. */
  wcsprintf("\nList of dis status return values:\n");
  for (status = 1; status <= 5; status++) {
    wcsprintf("%4d: %s.\n", status, dis_errmsg[status]);
  }
  wcsprintf("\n");

  /* Optional file name specified? */
  if (1 < argc) {
    infile = argv[1];
  }


  /* Read in the FITS header, excluding COMMENT and HISTORY keyrecords. */
  if ((fptr = fopen(infile, "r")) == 0) {
    wcsprintf("ERROR opening %s\n", infile);
    return 1;
  }

  memset(naxis, 0, 2*sizeof(int));

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

      if (strncmp(keyrec, "NAXIS", 5) == 0) {
        if (keyrec[5] == ' ') {
          sscanf(keyrec+10, "%d", &n);
          if (n != 2) {
            wcsprintf("ERROR, expecting a 2D image.\n");
            return 1;
          }
          continue;
        }

        sscanf(keyrec+5, "%d = %d", &j, &n);
        naxis[j-1] = n;
        continue;
      }

      strncpy(header+k, keyrec, 80);
      k += 80;
      nkeyrec++;

      if (strncmp(keyrec, "END       ", 10) == 0) {
        /* An END keyrecord was read, but read the rest of the block. */
        gotend = 1;
      }
    }

    if (gotend) break;
  }
  fclose(fptr);


  /* Parse the header. */
  if ((wcspih(header, nkeyrec, WCSHDR_none, 2, &nreject, &nwcs, &wcs))) {
    wcsperr(wcs, 0x0);
    return 1;
  }

  /* Is it TPV? */
  dopoly = 0;
  if (strcmp(wcs->ctype[0], "RA---TPV") == 0) {
    /* Copy it and translate to Polynomial for later use. */
    wcspol.flag = -1;
    if (wcscopy(1, wcs, &wcspol)) {
      wcsperr(wcs, 0x0);
      return 1;
    }

    /* Translate TPV to Polynomial. */
    tpv2poly(&wcspol);

    wcspol.flag = -1;
    if (wcsset(&wcspol)) {
      wcsperr(&wcspol, 0x0);
      return 1;
    }

    dopoly = 1;
  }


  /* wcsset() translates the TPV "projection" into a sequent distortion. */
  if (wcsset(wcs)) {
    wcsperr(wcs, 0x0);
    return 1;
  }

  /* Henceforth, we will work with linprm. */
  lin = &(wcs->lin);

  /* Get statistics on the distortion in the inner quarter of the image. */
  maxdis = stats;
  maxtot = maxdis + 2;
  avgdis = maxtot + 1;
  avgtot = avgdis + 2;
  rmsdis = avgtot + 1;
  rmstot = rmsdis + 2;

  pixblc[0]  = 0.25 * naxis[0];
  pixblc[1]  = 0.25 * naxis[1];
  pixtrc[0]  = 0.75 * naxis[0];
  pixtrc[1]  = 0.75 * naxis[1];
  pixsamp[0] = (pixtrc[0] - pixblc[0])/512.0;
  pixsamp[1] = (pixtrc[1] - pixblc[1])/512.0;
  if (pixsamp[0] < 1.0) pixsamp[0] = 1.0;
  if (pixsamp[1] < 1.0) pixsamp[1] = 1.0;

  if (linwarp(lin, pixblc, pixtrc, pixsamp, &nsamp,
              maxdis, maxtot, avgdis, avgtot, rmsdis, rmstot)) {
    linperr(lin, 0x0);
    return 1;
  }

  for (k = 0; k < 9; k++) {
    if (fabs(stats[k]) < 0.0005) stats[k] = 0.0;
  }

  wcsprintf("linwarp() statistics computed over %d sample points:\n"
            "  Max distortion, axis 1: %8.3f pixels\n"
            "                  axis 2: %8.3f pixels\n"
            "                   total: %8.3f pixels\n"
            " Mean distortion, axis 1: %8.3f pixels\n"
            "                  axis 2: %8.3f pixels\n"
            "                   total: %8.3f pixels\n"
            "  RMS distortion, axis 1: %8.3f pixels\n"
            "                  axis 2: %8.3f pixels\n"
            "                   total: %8.3f pixels\n",
            nsamp, maxdis[0], maxdis[1], *maxtot,
                   avgdis[0], avgdis[1], *avgtot,
                   rmsdis[0], rmsdis[1], *rmstot);

  if (lin->disseq) {
    /* Exercise diswarp() as well. */
    wcsprintf("\n");

    /* Define a rectangle in intermediate pixel coordinates that just */
    /* encompasses the inner quarter of the image.  For this we need  */
    /* to switch off CDELTia scaling and all distortions.             */
    affine.flag = -1;
    if ((status = lincpy(1, lin, &affine))) {
      linperr(lin, 0x0);
      return 1;
    }

    affine.cdelt[0] = 1.0;
    affine.cdelt[1] = 1.0;
    if ((status = (lindis(1, &affine, 0x0) ||
                   lindis(2, &affine, 0x0) ||
                   linset(&affine)))) {
      linperr(&affine, 0x0);
      return 1;
    }

    pix[0] = pixblc[0];
    pix[1] = pixblc[1];
    pix[2] = pixtrc[0];
    pix[3] = pixblc[1];
    pix[4] = pixtrc[0];
    pix[5] = pixtrc[1];
    pix[6] = pixblc[0];
    pix[7] = pixtrc[1];
    if (linp2x(&affine, 4, 2, pix, pxi)) {
      linperr(&affine, 0x0);
      return 1;
    }

    linfree(&affine);

    pixblc[0] = pxi[0];
    pixblc[1] = pxi[1];
    pixtrc[0] = pxi[0];
    pixtrc[1] = pxi[1];
    k = 2;
    for (j = 1; j < 4; j++) {
      if (pixblc[0] > pxi[k]) pixblc[0] = pxi[k];
      if (pixtrc[0] < pxi[k]) pixtrc[0] = pxi[k];
      k++;
      if (pixblc[1] > pxi[k]) pixblc[1] = pxi[k];
      if (pixtrc[1] < pxi[k]) pixtrc[1] = pxi[k];
      k++;
    }

    pixsamp[0] = (pixtrc[0] - pixblc[0])/512.0;
    pixsamp[1] = (pixtrc[1] - pixblc[1])/512.0;

    if (diswarp(lin->disseq, pixblc, pixtrc, pixsamp, &nsamp,
                maxdis, maxtot, avgdis, avgtot, rmsdis, rmstot)) {
      wcserr_prt(lin->disseq->err, 0x0);
      return 1;
    }

    for (k = 0; k < 9; k++) {
      if (fabs(stats[k]) < 0.0005) stats[k] = 0.0;
    }

    wcsprintf("diswarp() statistics computed over %d sample points:\n"
              "  Max distortion, axis 1: %8.3f units\n"
              "                  axis 2: %8.3f units\n"
              "                   total: %8.3f units\n"
              " Mean distortion, axis 1: %8.3f units\n"
              "                  axis 2: %8.3f units\n"
              "                   total: %8.3f units\n"
              "  RMS distortion, axis 1: %8.3f units\n"
              "                  axis 2: %8.3f units\n"
              "                   total: %8.3f units\n",
              nsamp, maxdis[0], maxdis[1], *maxtot,
                     avgdis[0], avgdis[1], *avgtot,
                     rmsdis[0], rmsdis[1], *rmstot);
  }


  /* The image size determines the test domain. */
  if ((naxis1 = naxis[0]) == 0) {
    naxis1 = 2*wcs->crpix[0] + 1;
  }
  if ((naxis2 = naxis[1]) == 0) {
    naxis2 = 2*wcs->crpix[1] + 1;
  }

  /* Limit the number of tests. */
  inc = 1;
  while ((naxis1/inc)*(naxis2/inc) > 800000) {
    inc *= 2;
  }

  n   = naxis1 / inc;
  px0 = calloc(4*(2*n), sizeof(double));
  px1 = px0 + 2*n ;
  img = px1 + 2*n ;
  img1 = img;
  img2 = img + 2*n;

  for (itest = 0; itest < 2; itest++) {
    if (itest) {
      if (!dopoly) break;

      lin = &(wcspol.lin);
    }

    if (lin->dispre) {
      disfn = lin->dispre->dtype[0];
    } else if (lin->disseq) {
      disfn = lin->disseq->dtype[0];
    }

    wcsprintf("\n");

    /* Now the closure test. */
    tp2x  = 0;
    tx2p  = 0;
    nTest = 0;
    nFail = 0;
    nClosure = 0;
    absmax = 0.0;
    relmax = 0.0;
    for (p2 = 1; p2 <= naxis2; p2 += inc) {
      k = 0;
      for (p1 = 1; p1 <= naxis1; p1 += inc) {
        px0[k++] = (double)p1;
        px0[k++] = (double)p2;
      }

      t0 = clock();
      if (linp2x(lin, n, 2, px0, img)) {
        linperr(lin, 0x0);
        nFail = 1;
        break;
      }
      tp2x += clock() - t0;

      t0 = clock();
      if (linx2p(lin, n, 2, img, px1)) {
        linperr(lin, 0x0);
        nFail = 1;
        break;
      }
      tx2p += clock() - t0;

      /* Check closure. */
      k = 0;
      for (k = 0; k < 2*n ; k += 2) {
        dp1 = fabs(px1[k]   - px0[k]);
        dp2 = fabs(px1[k+1] - px0[k+1]);

        resid = (dp1 > dp2) ? dp1 : dp2;
        if (resid > absmax) absmax = resid;

        if (resid > ATOL) {
          nClosure++;
          wcsprintf("Absolute closure error:\n");
          wcsprintf("    pix: %18.12f %18.12f\n", px0[k], px0[k+1]);
          wcsprintf(" -> img: %18.12f %18.12f\n", img[k], img[k+1]);
          wcsprintf(" -> pix: %18.12f %18.12f\n", px1[k], px1[k+1]);
          wcsprintf("\n");
          continue;
        }

        resid = 0.0;
        if ((px = fabs(px0[k]))   > 1.0) resid = dp1/px;
        if ((px = fabs(px0[k+1])) > 1.0) {
          if ((rel = dp2/px) > resid) resid = rel;
        }
        if (resid > relmax) relmax = resid;

        if (resid > FTOL) {
          nClosure++;
          wcsprintf("Relative closure error:\n");
          wcsprintf("    pix: %18.12f %18.12f\n", px0[k], px0[k+1]);
          wcsprintf(" -> img: %18.12f %18.12f\n", img[k], img[k+1]);
          wcsprintf(" -> pix: %18.12f %18.12f\n", px1[k], px1[k+1]);
          wcsprintf("\n");
        }
      }

      nTest += n;
    }

    if (nFail) {
      wcsprintf("\nFAIL: The %s test failed to complete.\n", disfn);

    } else {
      wcsprintf("linp2x/linx2p with %s distortions:\n"
        "  Completed %d closure tests.\n"
        "  Maximum absolute closure residual = %.2e pixel.\n"
        "  Maximum relative closure residual = %.2e.\n", disfn,
        nTest, absmax, relmax);
      wcsprintf("\n");

      wcsprintf("  linp2x time (ns): %6.0f\n  linx2p time (ns): %6.0f\n\n",
        1.0e9*((double)tp2x/CLOCKS_PER_SEC)/nTest,
        1.0e9*((double)tx2p/CLOCKS_PER_SEC)/nTest);

      if (nClosure) {
        wcsprintf("FAIL: %d closure residuals exceed reporting tolerance.\n",
          nClosure);

      } else {
        wcsprintf("PASS: All %s closure residuals are within reporting "
          "tolerance.\n", disfn);
      }
    }
  }


  /* Compare TPV with Polynomial over the test domain. */
  if (dopoly) {
    wcsprintf("\n");

    nTest  = 0;
    nFail  = 0;
    absmax = 0.0;
    lintpv = &(wcs->lin);
    linpol = &(wcspol.lin);
    for (p2 = 1; p2 <= naxis2; p2 += inc) {
      k = 0;
      for (p1 = 1; p1 <= naxis1; p1 += inc) {
        px0[k++] = (double)p1;
        px0[k++] = (double)p2;
      }

      if (linp2x(lintpv, n, 2, px0, img1)) {
        linperr(lintpv, 0x0);
        break;
      }

      if (linp2x(linpol, n, 2, px0, img2)) {
        linperr(linpol, 0x0);
        break;
      }

      /* Check agreement. */
      k = 0;
      for (k = 0; k < 2*n ; k += 2) {
        dp1 = fabs(img2[k]   - img1[k]);
        dp2 = fabs(img2[k+1] - img1[k+1]);

        resid = (dp1 > dp2) ? dp1 : dp2;
        if (resid > absmax) absmax = resid;

        if (resid > ATOL) {
          nFail++;
          wcsprintf("TPV - Polynomial disagreement:\n");
          wcsprintf("    pix: %18.12f %18.12f\n", px0[k],  px0[k+1]);
          wcsprintf(" -> TPV: %18.12f %18.12f\n", img1[k], img1[k+1]);
          wcsprintf(" -> Pol: %18.12f %18.12f\n", img2[k], img2[k+1]);
          wcsprintf("\n");
          continue;
        }
      }

      nTest += n;
    }

    wcsprintf("linp2x, TPV vs Polynomial distortions:\n"
      "  Completed %d comparisons.\n"
      "  Maximum absolute disagreement = %.2e units.\n", nTest, absmax);
    wcsprintf("\n");

    if (nFail) {
      wcsprintf("FAIL: %d comparisons exceed reporting tolerance.\n", nFail);

    } else {
      wcsprintf("PASS: All TPV vs Polynomial comparisons are within "
                "reporting tolerance.\n");
    }
  }


  free(px0);
  wcsvfree(&nwcs, &wcs);
  wcsfree(&wcspol);

  return nFail || nClosure;
}