/*  This routine provides simple FITS writer. It uses the routines
 *  provided by the fitsTcl/cfitsio libraries
 *
 *  NOTE : It will fail if the image already exists
 */
int ApogeeAltaManager::saveimage(unsigned short *src_buffer, char *filename, int nx, int ny)
{
	fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
	long  fpixel, nelements;
	unsigned short *array;
	unsigned short *simg;
	int status;
	/* initialize FITS image parameters */
	int bitpix   =  USHORT_IMG; /* 16-bit unsigned short pixel values       */
	long naxis    =   2;  /* 2-dimensional image                            */
	long naxes[2];

	naxes[0] = nx-bcols;
	naxes[1] = ny;
	array = src_buffer;
	status = 0;         /* initialize status before calling fitsio routines */
	simg = (unsigned short *)CCD_locate_buffer(const_cast<char *>("stemp"),2,nx-bcols,ny,1,1);

	if (fits_create_file(&fptr, filename, &status)) /* create new FITS file */
		printerror( status );           /* call printerror if error occurs */

	/* write the required keywords for the primary array image.     */
	/* Since bitpix = USHORT_IMG, this will cause cfitsio to create */
	/* a FITS image with BITPIX = 16 (signed short integers) with   */
	/* BSCALE = 1.0 and BZERO = 32768.  This is the convention that */
	/* FITS uses to store unsigned integers.  Note that the BSCALE  */
	/* and BZERO keywords will be automatically written by cfitsio  */
	/* in this case.                                                */

	if ( fits_create_img(fptr,  bitpix, naxis, naxes, &status) )
		printerror( status );

	fpixel = 1;                               /* first pixel to write      */
	nelements = naxes[0] * naxes[1];          /* number of pixels to write */

	if (bcols > 0)
	{
		dobiassubtract(src_buffer,simg,naxes[0],naxes[1]);

		/* write the array of unsigned integers to the FITS file */
		if ( fits_write_img(fptr, TUSHORT, fpixel, nelements, simg, &status) )
			printerror( status );
	} else
	{
		/* write the array of unsigned integers to the FITS file */
		if ( fits_write_img(fptr, TUSHORT, fpixel, nelements, src_buffer, &status) )
			printerror( status );
	}

	if ( fits_close_file(fptr, &status) )                /* close the file */
		printerror( status );

	return(status);
}