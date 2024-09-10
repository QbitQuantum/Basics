int main(int argc, char *argv[])
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */

    int status, nkeys, keypos, hdutype, ii, jj;
    char filename[FLEN_FILENAME];    /* input FITS file */
    char card[FLEN_CARD];   /* standard string lengths defined in fitsioc.h */

    status = 0;

    if (argc == 1)
        strcpy(filename, "-");  /* no command line name, so assume stdin */
    else
        strcpy(filename, argv[1] );   /* name of file to list */


    if ( fits_open_file(&fptr, filename, READONLY, &status) ) 
         printerror( status );

    /* get the current HDU number */
    fits_get_hdu_num(fptr, &ii);

    /* attempt to move to next HDU, until we get an EOF error */
    for (; !(fits_movabs_hdu(fptr, ii, &hdutype, &status) ); ii++) 
    {
        /* get no. of keywords */
        if (fits_get_hdrpos(fptr, &nkeys, &keypos, &status) )
            printerror( status );

        printf("Header listing for HDU #%d:\n", ii);
        for (jj = 1; jj <= nkeys; jj++)  {
            if ( fits_read_record(fptr, jj, card, &status) )
                 printerror( status );

            printf("%s\n", card); /* print the keyword card */
        }
        printf("END\n\n");  /* terminate listing with END */
    }

    if (status == END_OF_FILE)   /* status values are defined in fitsio.h */
        status = 0;              /* got the expected EOF error; reset = 0  */
    else
       printerror( status );     /* got an unexpected error                */

    if ( fits_close_file(fptr, &status) )
         printerror( status );

    return(0);
}