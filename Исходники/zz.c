int 
vot_addFITSMeta (int handle, fitsfile *fp, char *meta, int index)
{
    char  *id, *nam, *val, *unit, keyw[SZ_FNAME], comment[SZ_FNAME];
    int   status = 0;


    if ( (id = vot_getAttr (handle, "id")) ) {		/* ID attribute	      */
        memset (keyw, 0, SZ_FNAME);
        memset (comment, 0, SZ_FNAME);
        sprintf (keyw, "%3.3sID%d", meta, index);
        sprintf (comment, "%s id attribute", meta);
        if (fits_update_key (fp, TSTRING, keyw, id, comment, &status))
	    printerror ( status );
    }

    if ( (nam = vot_getAttr (handle, "name")) ) {	/* NAME attribute    */
        memset (keyw, 0, SZ_FNAME);
        memset (comment, 0, SZ_FNAME);
        sprintf (keyw, "%3.3sNAM%d", meta, index);
        sprintf (comment, "%s name attribute", meta);

        if (fits_update_key (fp, TSTRING, keyw, nam, comment, &status))
	    printerror ( status );
    }

    if ( (val = vot_getAttr (handle, "value")) ) {	/* VALUE attribute   */
        memset (keyw, 0, SZ_FNAME);
        memset (comment, 0, SZ_FNAME);
        sprintf (keyw, "%3.3sVAL%d", meta, index);
        sprintf (comment, "%s val attribute", meta);

        if (fits_update_key (fp, TSTRING, keyw, val, comment, &status))
	    printerror ( status );
    }

    if ( (unit = vot_getAttr (handle, "unit")) ) {	/* UNIT attribute   */
        memset (keyw, 0, SZ_FNAME);
        memset (comment, 0, SZ_FNAME);
        sprintf (keyw, "%3.3sUNI%d", meta, index);
        sprintf (comment, "%s unit attribute", meta);

        if (fits_update_key (fp, TSTRING, keyw, unit, comment, &status))
	    printerror ( status );
    }

    return (0);
}