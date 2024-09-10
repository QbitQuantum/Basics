int psrfits_write_ephem(struct psrfits *pf, FILE *parfile) {
    // Read a pulsar ephemeris (par file) and put it into
    // the psrfits PSREPHEM table.  Only minimal checking
    // is done.
   
    // Get status
    int *status = &(pf->status);

    // Save current HDU, move to psrephem table
    int hdu;
    fits_get_hdu_num(pf->fptr, &hdu);
    fits_movnam_hdu(pf->fptr, BINARY_TBL, "PSREPHEM", 0, status);

    // Loop over lines in par file
    int row=1, col, dtype;
    double dval;
    int ival;
    long double ldval;
    char line[256], *ptr, *saveptr, *key, *val;
    while (fgets(line, 256, parfile)!=NULL) {

        // Convert tabs to spaces
        while ((ptr=strchr(line,'\t'))!=NULL) { *ptr=' '; }

        // strip leading whitespace
        ptr = line;
        while (*ptr==' ') { ptr++; }

        // Identify comments or blank lines
        if (line[0]=='\n' || line[0]=='#' || 
                (line[0]=='C' && line[1]==' '))
            continue;

        // Split into key/val (ignore fit flag and error)
        key = strtok_r(line,  " ", &saveptr);
        val = strtok_r(NULL, " ", &saveptr);
        if (key==NULL || val==NULL) continue; // TODO : complain?

        // Deal with any special cases here
        if (strncmp(key, "PSR", 3)==0)  {

            // PSR(J) -> PSR_NAME
            fits_get_colnum(pf->fptr,CASEINSEN,"PSR_NAME",&col,status);
            fits_write_col(pf->fptr,TSTRING,col,row,1,1,&val,status);

        } else if (strncmp(key, "RA", 2)==0) {

            // RA -> RAJ
            fits_get_colnum(pf->fptr,CASEINSEN,"RAJ",&col,status);
            fits_write_col(pf->fptr,TSTRING,col,row,1,1,&val,status);

        } else if (strncmp(key, "DEC", 3)==0) {

            // DEC -> DECJ
            fits_get_colnum(pf->fptr,CASEINSEN,"DECJ",&col,status);
            fits_write_col(pf->fptr,TSTRING,col,row,1,1,&val,status);

        } else if (key[0]=='E' && key[1]=='\0') {

            // E -> ECC
            dval = atof(val);
            fits_get_colnum(pf->fptr,CASEINSEN,"ECC",&col,status);
            fits_write_col(pf->fptr,TDOUBLE,col,row,1,1,&dval,status);

        } else if (strncmp(key, "F0", 2)==0) {

            // F is converted to mHz and split into int/frac
            ldval = strtold(val,NULL) * 1000.0; // Hz->mHz
            ival = (int)ldval;
            dval = ldval - (long double)ival;
            fits_get_colnum(pf->fptr,CASEINSEN,"IF0",&col,status);
            fits_write_col(pf->fptr,TINT,col,row,1,1,&ival,status);
            fits_get_colnum(pf->fptr,CASEINSEN,"FF0",&col,status);
            fits_write_col(pf->fptr,TDOUBLE,col,row,1,1,&dval,status);

        } else if (strncmp(key, "TZRMJD", 6)==0) {

            // TZRMJD is split into int/frac
            ldval = strtold(val,NULL);
            ival = (int)ldval;
            dval = ldval - (long double)ival;
            fits_get_colnum(pf->fptr,CASEINSEN,"TZRIMJD",&col,status);
            fits_write_col(pf->fptr,TINT,col,row,1,1,&ival,status);
            fits_get_colnum(pf->fptr,CASEINSEN,"TZRFMJD",&col,status);
            fits_write_col(pf->fptr,TDOUBLE,col,row,1,1,&dval,status);

        } else {

            // Find column, skip/warn if this one isn't present
            fits_get_colnum(pf->fptr,CASEINSEN,key,&col,status);
            if (*status==COL_NOT_FOUND) {
#if (DEBUGOUT)
                fprintf(stderr, 
                        "psrfits_write_epherm warning: Couldn't find keyword %s "
                        "in ephemeris table.\n",
                        key);
#endif
                *status=0;
                continue;
            }

            // Need to convert string to appropriate column data type
            // and then write it to the column.  These should all be
            // either double int or string.
            fits_get_coltype(pf->fptr,col,&dtype,NULL,NULL,status);
            if (dtype==TDOUBLE || dtype==TFLOAT) { 
                dval = atof(val);
                fits_write_col(pf->fptr,TDOUBLE,col,row,1,1,&dval,status);
            } else if (dtype==TINT || dtype==TLONG || dtype==TSHORT) {
                ival = atoi(val);
                fits_write_col(pf->fptr,TINT,col,row,1,1,&ival,status);
            } else if (dtype==TSTRING) {
                fits_write_col(pf->fptr,TSTRING,col,row,1,1,&val,status);
            } else {
                fprintf(stderr, "psrfits_write_ephem warning: "
                        "Unhandled column datatype (key=%s)\n", key);
                continue;
            }
        }

        // sucess/failure
        if (*status) {
            fprintf(stderr, "psrfits_write_ephem failed: key=%s val=%s\n",
                    key, val);
            fits_report_error(stderr, *status);
            *status=0;
        } 
#if 0  // DEBUG
        else {
            fprintf(stderr, "psrfits_write_ephem success: key=%s val=%s\n",
                    key, val);
        }
#endif

    }

    // Go back to orig HDU
    fits_movabs_hdu(pf->fptr, hdu, NULL, status);

    return *status;
}