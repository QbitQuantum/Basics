int wcshdo(int relax, struct wcsprm *wcs, int *nkeyrec, char **header)

/* ::: CUBEFACE and STOKES handling? */

{
    static const char *function = "wcshdo";

    char alt, comment[72], keyvalue[72], keyword[16], obsg[8] = "OBSG?",
            obsgeo[8] = "OBSGEO-?", ptype, xtype, xyz[] = "XYZ";
    int  bintab, col0, *colax, colnum, i, j, k, naxis, pixlist, primage,
         status = 0;
    struct wcserr **err;

    *nkeyrec = 0;
    *header  = 0x0;

    if (wcs == 0x0) return WCSHDRERR_NULL_POINTER;
    err = &(wcs->err);

    if (wcs->flag != WCSSET) {
        if ((status = wcsset(wcs))) return status;
    }

    if ((naxis = wcs->naxis) == 0) {
        return 0;
    }


    /* These are mainly for convenience. */
    alt = wcs->alt[0];
    if (alt == ' ') alt = '\0';
    colnum = wcs->colnum;
    colax  = wcs->colax;

    primage = 0;
    bintab  = 0;
    pixlist = 0;
    if (colnum) {
        bintab  = 1;
        col0 = colnum;
    } else if (colax[0]) {
        pixlist = 1;
        col0 = colax[0];
    } else {
        primage = 1;
    }


    /* WCS dimension. */
    if (!pixlist) {
        sprintf(keyvalue, "%20d", naxis);
        wcshdo_util(relax, "WCSAXES", "WCAX", 0, 0x0, 0, 0, 0, alt, colnum, colax,
                    keyvalue, "Number of coordinate axes", nkeyrec, header, &status);
    }

    /* Reference pixel coordinates. */
    for (j = 0; j < naxis; j++) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->crpix[j]);
        wcshdo_util(relax, "CRPIX", "CRP", WCSHDO_CRPXna, "CRPX", 0, j+1, 0, alt,
                    colnum, colax, keyvalue, "Pixel coordinate of reference point", nkeyrec,
                    header, &status);
    }

    /* Linear transformation matrix. */
    k = 0;
    for (i = 0; i < naxis; i++) {
        for (j = 0; j < naxis; j++, k++) {
            if (i == j) {
                if (wcs->pc[k] == 1.0) continue;
            } else {
                if (wcs->pc[k] == 0.0) continue;
            }

            wcsutil_double2str(keyvalue, "%20.12G", wcs->pc[k]);
            wcshdo_util(relax, "PC", bintab ? "PC" : "P", WCSHDO_TPCn_ka,
                        bintab ? 0x0 : "PC", i+1, j+1, 0, alt, colnum, colax,
                        keyvalue, "Coordinate transformation matrix element",
                        nkeyrec, header, &status);
        }
    }

    /* Coordinate increment at reference point. */
    for (i = 0; i < naxis; i++) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->cdelt[i]);
        comment[0] = '\0';
        if (wcs->cunit[i][0]) sprintf(comment, "[%s] ", wcs->cunit[i]);
        strcat(comment, "Coordinate increment at reference point");
        wcshdo_util(relax, "CDELT", "CDE", WCSHDO_CRPXna, "CDLT", i+1, 0, 0, alt,
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* Units of coordinate increment and reference value. */
    for (i = 0; i < naxis; i++) {
        if (wcs->cunit[i][0] == '\0') continue;

        sprintf(keyvalue, "'%s'", wcs->cunit[i]);
        wcshdo_util(relax, "CUNIT", "CUN", WCSHDO_CRPXna, "CUNI", i+1, 0, 0, alt,
                    colnum, colax, keyvalue, "Units of coordinate increment and value",
                    nkeyrec, header, &status);
    }

    /* Coordinate type. */
    for (i = 0; i < naxis; i++) {
        if (wcs->ctype[i][0] == '\0') continue;

        sprintf(keyvalue, "'%s'", wcs->ctype[i]);
        strcpy(comment, "Coordinate type code");
        if (i == wcs->lng || i == wcs->lat) {
            if (strncmp(wcs->ctype[i], "RA--", 4) == 0) {
                strcpy(comment, "Right ascension, ");
            } else if (strncmp(wcs->ctype[i], "DEC-", 4) == 0) {
                strcpy(comment, "Declination, ");
            } else if (strncmp(wcs->ctype[i]+1, "LON", 3) == 0 ||
                       strncmp(wcs->ctype[i]+1, "LAT", 3) == 0) {
                switch (wcs->ctype[i][0]) {
                case 'G':
                    strcpy(comment, "galactic ");
                    break;
                case 'E':
                    strcpy(comment, "ecliptic ");
                case 'H':
                    strcpy(comment, "helioecliptic ");
                case 'S':
                    strcpy(comment, "supergalactic ");
                }

                if (i == wcs->lng) {
                    strcat(comment, "longitude, ");
                } else {
                    strcat(comment, "latitude, ");
                }

                wcs->ctype[i][0] = toupper(wcs->ctype[i][0]);
            }

            strcat(comment, wcs->cel.prj.name);
            strcat(comment, " projection");

        } else if (i == wcs->spec) {
            spctyp(wcs->ctype[i], 0x0, 0x0, comment, 0x0, &ptype, &xtype, 0x0);
            if (ptype == xtype) {
                strcat(comment, " (linear)");
            } else {
                switch (xtype) {
                case 'F':
                    strcat(comment, " (linear in frequency)");
                    break;
                case 'V':
                    strcat(comment, " (linear in velocity)");
                    break;
                case 'W':
                    strcat(comment, " (linear in wavelength)");
                    break;
                }
            }
        }

        wcshdo_util(relax, "CTYPE", "CTY", WCSHDO_CRPXna, "CTYP", i+1, 0, 0, alt,
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* Coordinate value at reference point. */
    for (i = 0; i < naxis; i++) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->crval[i]);
        comment[0] = '\0';
        if (wcs->cunit[i][0]) sprintf(comment, "[%s] ", wcs->cunit[i]);
        strcat(comment, "Coordinate value at reference point");
        wcshdo_util(relax, "CRVAL", "CRV", WCSHDO_CRPXna, "CRVL", i+1, 0, 0, alt,
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* Parameter values. */
    for (k = 0; k < wcs->npv; k++) {
        wcsutil_double2str(keyvalue, "%20.12G", (wcs->pv[k]).value);
        if ((wcs->pv[k]).i == (wcs->lng + 1)) {
            switch ((wcs->pv[k]).m) {
            case 1:
                strcpy(comment, "[deg] Native longitude of the reference point");
                break;
            case 2:
                strcpy(comment, "[deg] Native latitude  of the reference point");
                break;
            case 3:
                if (primage) {
                    sprintf(keyword, "LONPOLE%c", alt);
                } else if (bintab) {
                    sprintf(keyword, "LONP%d%c", colnum, alt);
                } else {
                    sprintf(keyword, "LONP%d%c", colax[(wcs->pv[k]).i - 1], alt);
                }
                sprintf(comment, "[deg] alias for %s (has precedence)", keyword);
                break;
            case 4:
                if (primage) {
                    sprintf(keyword, "LATPOLE%c", alt);
                } else if (bintab) {
                    sprintf(keyword, "LATP%d%c", colnum, alt);
                } else {
                    sprintf(keyword, "LATP%d%c", colax[(wcs->pv[k]).i - 1], alt);
                }
                sprintf(comment, "[deg] alias for %s (has precedence)", keyword);
                break;
            }
        } else if ((wcs->pv[k]).i == (wcs->lat + 1)) {
            sprintf(comment, "%s projection parameter", wcs->cel.prj.code);
        } else {
            strcpy(comment, "Coordinate transformation parameter");
        }

        wcshdo_util(relax, "PV", "V", WCSHDO_PVn_ma, "PV", wcs->pv[k].i, -1,
                    wcs->pv[k].m, alt, colnum, colax, keyvalue, comment,
                    nkeyrec, header, &status);
    }

    for (k = 0; k < wcs->nps; k++) {
        sprintf(keyvalue, "'%s'", (wcs->ps[k]).value);

        wcshdo_util(relax, "PS", "S", WCSHDO_PVn_ma, "PS", wcs->ps[k].i, -1,
                    wcs->ps[k].m, alt, colnum, colax, keyvalue,
                    "Coordinate transformation parameter",
                    nkeyrec, header, &status);
    }

    /* Celestial and spectral transformation parameters. */
    if (!undefined(wcs->lonpole)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->lonpole);
        wcshdo_util(relax, "LONPOLE", "LONP", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[deg] Native longitude of celestial pole",
                    nkeyrec, header, &status);
    }

    if (!undefined(wcs->latpole)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->latpole);
        wcshdo_util(relax, "LATPOLE", "LATP", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[deg] Native latitude of celestial pole",
                    nkeyrec, header, &status);
    }

    if (!undefined(wcs->restfrq)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->restfrq);
        wcshdo_util(relax, "RESTFRQ", "RFRQ", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[Hz] Line rest frequency",
                    nkeyrec, header, &status);
    }

    if (!undefined(wcs->restwav)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->restwav);
        wcshdo_util(relax, "RESTWAV", "RWAV", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[Hz] Line rest wavelength",
                    nkeyrec, header, &status);
    }

    /* Coordinate system title. */
    if (wcs->wcsname[0]) {
        sprintf(keyvalue, "'%s'", wcs->wcsname);
        if (bintab) {
            wcshdo_util(relax, "WCSNAME", "WCSN", 0, 0x0, 0, 0, 0, alt,
                        colnum, colax, keyvalue, "Coordinate system title",
                        nkeyrec, header, &status);
        } else {
            /* TWCS was a mistake. */
            wcshdo_util(relax, "WCSNAME", "TWCS", WCSHDO_WCSNna, "WCSN", 0, 0, 0,
                        alt, colnum, colax, keyvalue, "Coordinate system title",
                        nkeyrec, header, &status);
        }
    }

    /* Coordinate axis title. */
    if (wcs->cname) {
        for (i = 0; i < naxis; i++) {
            if (wcs->cname[i][0] == '\0') continue;

            sprintf(keyvalue, "'%s'", wcs->cname[i]);
            wcshdo_util(relax, "CNAME", "CNA", WCSHDO_CNAMna, "CNAM", i+1, 0, 0,
                        alt, colnum, colax, keyvalue, "Axis name for labelling purposes",
                        nkeyrec, header, &status);
        }
    }

    /* Random error in coordinate. */
    if (wcs->crder) {
        for (i = 0; i < naxis; i++) {
            if (undefined(wcs->crder[i])) continue;

            wcsutil_double2str(keyvalue, "%20.12G", wcs->crder[i]);
            comment[0] = '\0';
            if (wcs->cunit[i][0]) sprintf(comment, "[%s] ", wcs->cunit[i]);
            strcat(comment, "Random error in coordinate");
            wcshdo_util(relax, "CRDER", "CRD", WCSHDO_CNAMna, "CRDE", i+1, 0, 0,
                        alt, colnum, colax, keyvalue, comment, nkeyrec, header, &status);
        }
    }

    /* Systematic error in coordinate. */
    if (wcs->csyer) {
        for (i = 0; i < naxis; i++) {
            if (undefined(wcs->csyer[i])) continue;

            wcsutil_double2str(keyvalue, "%20.12G", wcs->csyer[i]);
            comment[0] = '\0';
            if (wcs->cunit[i][0]) sprintf(comment, "[%s] ", wcs->cunit[i]);
            strcat(comment, "Systematic error in coordinate");
            wcshdo_util(relax, "CSYER", "CSY", WCSHDO_CNAMna, "CSYE", i+1, 0, 0,
                        alt, colnum, colax, keyvalue, comment, nkeyrec, header, &status);
        }
    }

    /* Equatorial coordinate system type. */
    if (wcs->radesys[0]) {
        sprintf(keyvalue, "'%s'", wcs->radesys);
        wcshdo_util(relax, "RADESYS", "RADE", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "Equatorial coordinate system",
                    nkeyrec, header, &status);
    }

    /* Equinox of equatorial coordinate system. */
    if (!undefined(wcs->equinox)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->equinox);
        wcshdo_util(relax, "EQUINOX", "EQUI", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[yr] Equinox of equatorial coordinates",
                    nkeyrec, header, &status);
    }

    /* Reference frame of spectral coordinates. */
    if (wcs->specsys[0]) {
        sprintf(keyvalue, "'%s'", wcs->specsys);
        wcshdo_util(relax, "SPECSYS", "SPEC", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "Reference frame of spectral coordinates",
                    nkeyrec, header, &status);
    }

    /* Reference frame of spectral observation. */
    if (wcs->ssysobs[0]) {
        sprintf(keyvalue, "'%s'", wcs->ssysobs);
        wcshdo_util(relax, "SSYSOBS", "SOBS", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "Reference frame of spectral observation",
                    nkeyrec, header, &status);
    }

    /* Observer's velocity towards source. */
    if (!undefined(wcs->velosys)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->velosys);
        wcshdo_util(relax, "VELOSYS", "VSYS", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "[m/s] Velocity towards source",
                    nkeyrec, header, &status);
    }

    /* Reference frame of source redshift. */
    if (wcs->ssyssrc[0]) {
        sprintf(keyvalue, "'%s'", wcs->ssyssrc);
        wcshdo_util(relax, "SSYSSRC", "SSRC", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "Reference frame of source redshift",
                    nkeyrec, header, &status);
    }

    /* Redshift of the source. */
    if (!undefined(wcs->zsource)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->zsource);
        wcshdo_util(relax, "ZSOURCE", "ZSOU", 0, 0x0, 0, 0, 0, alt,
                    colnum, colax, keyvalue, "Redshift of the source",
                    nkeyrec, header, &status);
    }

    /* Observatory coordinates. */
    for (k = 0; k < 3; k++) {
        if (undefined(wcs->obsgeo[k])) continue;

        wcsutil_double2str(keyvalue, "%20.12G", wcs->obsgeo[k]);
        sprintf(comment, "[m] ITRF observatory %c-coordinate", xyz[k]);
        obsgeo[7] = xyz[k];
        obsg[4]   = xyz[k];
        wcshdo_util(relax, obsgeo, obsg, 0, 0x0, 0, 0, 0, ' ',
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* MJD of observation. */
    if (!undefined(wcs->mjdobs)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->mjdobs);

        strcpy(comment, "[d] MJD of observation");
        if (wcs->dateobs[0]) {
            if (primage || (relax & 1) == 0) {
                sprintf(comment+22, " matching DATE-OBS");
            } else {
                sprintf(comment+22, " matching DOBS%d", col0);
            }
        }

        wcshdo_util(relax, "MJD-OBS", "MJDOB", 0, 0x0, 0, 0, 0, ' ',
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* MJD mid-observation time. */
    if (!undefined(wcs->mjdavg)) {
        wcsutil_double2str(keyvalue, "%20.12G", wcs->mjdavg);

        strcpy(comment, "[d] MJD mid-observation");
        if (wcs->dateavg[0]) {
            if (primage) {
                sprintf(comment+23, " matching DATE-AVG");
            } else {
                sprintf(comment+23, " matching DAVG%d", col0);
            }
        }

        wcshdo_util(relax, "MJD-AVG", "MJDA", 0, 0x0, 0, 0, 0, ' ',
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    /* ISO-8601 date corresponding to MJD-OBS. */
    if (wcs->dateobs[0]) {
        sprintf(keyvalue, "'%s'", wcs->dateobs);

        strcpy(comment, "ISO-8601 observation date");
        if (!undefined(wcs->mjdobs)) {
            if (primage) {
                sprintf(comment+25, " matching MJD-OBS");
            } else {
                sprintf(comment+25, " matching MJDOB%d", col0);
            }
        }

        if (relax & 1) {
            /* Allow DOBSn. */
            wcshdo_util(relax, "DATE-OBS", "DOBS", WCSHDO_DOBSn, 0x0, 0, 0, 0,
                        ' ', colnum, colax, keyvalue, comment, nkeyrec, header, &status);
        } else {
            /* Force DATE-OBS. */
            wcshdo_util(relax, "DATE-OBS", 0x0, 0, 0x0, 0, 0, 0, ' ', 0,
                        0x0, keyvalue, comment, nkeyrec, header, &status);
        }
    }

    /* ISO-8601 date corresponding to MJD-OBS. */
    if (wcs->dateavg[0]) {
        sprintf(keyvalue, "'%s'", wcs->dateavg);

        strcpy(comment, "ISO-8601 mid-observation date");
        if (!undefined(wcs->mjdavg)) {
            if (primage) {
                sprintf(comment+29, " matching MJD-AVG");
            } else {
                sprintf(comment+29, " matching MJDA%d", col0);
            }
        }

        wcshdo_util(relax, "DATE-AVG", "DAVG", 0, 0x0, 0, 0, 0, ' ',
                    colnum, colax, keyvalue, comment, nkeyrec, header, &status);
    }

    if (status == WCSHDRERR_MEMORY) {
        wcserr_set(WCSHDR_ERRMSG(status));
    }
    return status;
}