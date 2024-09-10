int celfix(struct wcsprm *wcs)

{
  static const char *function = "celfix";

  int k, status;
  struct celprm *wcscel = &(wcs->cel);
  struct prjprm *wcsprj = &(wcscel->prj);
  struct wcserr **err;

  if (wcs == 0x0) return FIXERR_NULL_POINTER;
  err = &(wcs->err);

  /* Initialize if required. */
  if (wcs->flag != WCSSET) {
    if ((status = wcsset(wcs))) return status;
  }

  /* Was an NCP or GLS projection code translated? */
  if (wcs->lat >= 0) {
    /* Check ctype. */
    if (strcmp(wcs->ctype[wcs->lat]+5, "NCP") == 0) {
      strcpy(wcs->ctype[wcs->lng]+5, "SIN");
      strcpy(wcs->ctype[wcs->lat]+5, "SIN");

      if (wcs->npvmax < wcs->npv + 2) {
        /* Allocate space for two more PVi_ja keyvalues. */
        if (wcs->m_flag == WCSSET && wcs->pv == wcs->m_pv) {
          if (!(wcs->pv = calloc(wcs->npv+2, sizeof(struct pvcard)))) {
            wcs->pv = wcs->m_pv;
            return wcserr_set(WCSFIX_ERRMSG(FIXERR_MEMORY));
          }

          wcs->npvmax = wcs->npv + 2;
          wcs->m_flag = WCSSET;

          for (k = 0; k < wcs->npv; k++) {
            wcs->pv[k] = wcs->m_pv[k];
          }

          if (wcs->m_pv) free(wcs->m_pv);
          wcs->m_pv = wcs->pv;

        } else {
          return wcserr_set(WCSFIX_ERRMSG(FIXERR_MEMORY));
        }
      }

      wcs->pv[wcs->npv].i = wcs->lat + 1;
      wcs->pv[wcs->npv].m = 1;
      wcs->pv[wcs->npv].value = wcsprj->pv[1];
      (wcs->npv)++;

      wcs->pv[wcs->npv].i = wcs->lat + 1;
      wcs->pv[wcs->npv].m = 2;
      wcs->pv[wcs->npv].value = wcsprj->pv[2];
      (wcs->npv)++;

      return FIXERR_SUCCESS;

    } else if (strcmp(wcs->ctype[wcs->lat]+5, "GLS") == 0) {
      strcpy(wcs->ctype[wcs->lng]+5, "SFL");
      strcpy(wcs->ctype[wcs->lat]+5, "SFL");

      if (wcs->crval[wcs->lng] != 0.0 || wcs->crval[wcs->lat] != 0.0) {
        /* In the AIPS convention, setting the reference longitude and
         * latitude for GLS does not create an oblique graticule.  A non-zero
         * reference longitude introduces an offset in longitude in the normal
         * way, whereas a non-zero reference latitude simply translates the
         * reference point (i.e. the map as a whole) to that latitude.  This
         * might be effected by adjusting CRPIXja but that is complicated by
         * the linear transformation and instead is accomplished here by
         * setting theta_0. */
        if (wcs->npvmax < wcs->npv + 2) {
          /* Allocate space for three more PVi_ja keyvalues. */
          if (wcs->m_flag == WCSSET && wcs->pv == wcs->m_pv) {
            if (!(wcs->pv = calloc(wcs->npv+3, sizeof(struct pvcard)))) {
              wcs->pv = wcs->m_pv;
              return wcserr_set(WCSFIX_ERRMSG(FIXERR_MEMORY));
            }

            wcs->npvmax = wcs->npv + 3;
            wcs->m_flag = WCSSET;

            for (k = 0; k < wcs->npv; k++) {
              wcs->pv[k] = wcs->m_pv[k];
            }

            if (wcs->m_pv) free(wcs->m_pv);
            wcs->m_pv = wcs->pv;

          } else {
            return wcserr_set(WCSFIX_ERRMSG(FIXERR_MEMORY));
          }
        }

        wcs->pv[wcs->npv].i = wcs->lng + 1;
        wcs->pv[wcs->npv].m = 0;
        wcs->pv[wcs->npv].value = 1.0;
        (wcs->npv)++;

        /* Note that the reference longitude is still zero. */
        wcs->pv[wcs->npv].i = wcs->lng + 1;
        wcs->pv[wcs->npv].m = 1;
        wcs->pv[wcs->npv].value = 0.0;
        (wcs->npv)++;

        wcs->pv[wcs->npv].i = wcs->lng + 1;
        wcs->pv[wcs->npv].m = 2;
        wcs->pv[wcs->npv].value = wcs->crval[wcs->lat];
        (wcs->npv)++;
      }

      return FIXERR_SUCCESS;
    }
  }

  return FIXERR_NO_CHANGE;
}