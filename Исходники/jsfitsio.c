// getImageToArray: extract a sub-section from an image HDU, return array
void *getImageToArray(fitsfile *fptr, int *dims, double *cens, char *slice,
		      int *odim1, int *odim2, int *bitpix, int *status){
  int i, naxis;
  int xcen, ycen, dim1, dim2, type;
  int tstatus = 0;
  int doscale = 0;
  void *obuf;
  long totpix, totbytes;
  long naxes[IDIM], fpixel[IDIM], lpixel[IDIM], inc[IDIM];
  double bscale = 1.0;
  double bzero = 0.0;
  char comment[81];
  char *s, *tslice;
  int nslice, idx, iaxis0, iaxis1;
  int iaxes[2] = {0, 1};
  int saxes[IDIM] = {0, 0, 0, 0};
  // seed buffers
  for(i=0; i<IDIM; i++){
    naxes[i] = 0;
    fpixel[i] = 1;
    lpixel[i] = 1;
    inc[i] = 1;
  }
  // get image dimensions and type
  fits_get_img_dim(fptr, &naxis, status);
  fits_get_img_size(fptr, min(IDIM,naxis), naxes, status);
  fits_get_img_type(fptr, bitpix, status);
  if( naxis < 2 ){
    *status = BAD_DIMEN;
    return NULL;
  }
  // parse slice string into primary axes and slice axes
  if( slice && *slice ){
    tslice = (char *)strdup(slice);
    for(s=(char *)strtok(tslice, " :,"), nslice=0, idx=0;
	(s != NULL) && (nslice < IDIM); 
	s=(char *)strtok(NULL," :,"), nslice++){
      if( !strcmp(s, "*") ){
	if( idx < 2 ){
	  iaxes[idx++] = nslice;
	}
      } else {
	saxes[nslice] = atoi(s);
	if( (saxes[nslice] < 1) || (saxes[nslice] > naxes[nslice]) ){
	  *status = SEEK_ERROR;
	  return NULL;
	}
      }
    }
    free(tslice);      
  }
  // convenience variables for the primary axis indexes
  iaxis0 = iaxes[0];
  iaxis1 = iaxes[1];
  // get limits of extracted section
  if( dims && dims[0] && dims[1] ){
    dim1 = min(dims[0], naxes[iaxis0]);
    dim2 = min(dims[1], naxes[iaxis1]);
    // read image section
    if( cens ){
      xcen = cens[0];
      ycen = cens[1];
    } else {
      xcen = dim1/2;
      ycen = dim2/2;
    }
    fpixel[iaxis0] = (int)(xcen - (dim1+1)/2);
    fpixel[iaxis1] = (int)(ycen - (dim2+1)/2);
    lpixel[iaxis0] = (int)(xcen + (dim1/2));
    lpixel[iaxis1] = (int)(ycen + (dim2/2));
  } else {
    // read entire image
    fpixel[iaxis0] = 1;
    fpixel[iaxis1] = 1;
    lpixel[iaxis0] = naxes[iaxis0];
    lpixel[iaxis1] = naxes[iaxis1];
  }
  // stay within image limits
  fpixel[iaxis0] = max(fpixel[iaxis0], 1);
  fpixel[iaxis0] = min(fpixel[iaxis0], naxes[iaxis0]);
  lpixel[iaxis0] = max(lpixel[iaxis0], 1);
  lpixel[iaxis0] = min(lpixel[iaxis0], naxes[iaxis0]);
  fpixel[iaxis1] = max(fpixel[iaxis1], 1);
  fpixel[iaxis1] = min(fpixel[iaxis1], naxes[iaxis0]);
  lpixel[iaxis1] = max(lpixel[iaxis1], 1);
  lpixel[iaxis1] = min(lpixel[iaxis1], naxes[iaxis0]);
  // for sliced dimensions, set first and last pixel to the specified slice
  for(i=0; i<min(IDIM,naxis); i++){
    if( saxes[i] ){
      // 1 pixel slice in this dimension
      fpixel[i] = saxes[i];
      lpixel[i] = saxes[i];
      // stay within image limits
      fpixel[i] = max(fpixel[i], 1);
      fpixel[i] = min(fpixel[i], naxes[i]);
      lpixel[i] = max(lpixel[i], 1);
      lpixel[i] = min(lpixel[i], naxes[i]);
    }
  }
  // section dimensions
  *odim1 = lpixel[iaxis0] - fpixel[iaxis0] + 1;
  *odim2 = lpixel[iaxis1] - fpixel[iaxis1] + 1;
  totpix = *odim1 * *odim2;
  // make sure we have an image with valid dimensions size
  if( totpix <= 1 ){
    *status = NEG_AXIS;
    return NULL;
  }
  // are we scaling?
  fits_read_key(fptr, TDOUBLE, "BSCALE", &bscale, comment, &tstatus);
  if( tstatus != VALUE_UNDEFINED ){
    fits_read_key(fptr, TDOUBLE, "BZERO", &bzero, comment, &tstatus);
  }
  if( (bscale != 1.0) || (bzero != 0.0) ){
    doscale = 1;
  }
  // allocate space for the pixel array
  switch(*bitpix){
    case 8:
      if( doscale ){
	// scaled data has to be float
	*bitpix = -32;
	type = TFLOAT;
	totbytes = totpix * sizeof(float);
      } else {
	type = TBYTE;
	totbytes = totpix * sizeof(char);
      }
      break;
    case 16:
      if( doscale ){
	// scaled data has to be float
	*bitpix = -32;
	type = TFLOAT;
	totbytes = totpix * sizeof(float);
      } else {
	type = TSHORT;
	totbytes = totpix * sizeof(short);
      }
      break;
    case -16:
      if( doscale ){
	// scaled data has to be float
	*bitpix = -32;
	type = TFLOAT;
	totbytes = totpix * sizeof(float);
      } else {
	type = TUSHORT;
	totbytes = totpix * sizeof(unsigned short);
      }
      break;
    case 32:
      if( doscale ){
	// scaled data has to be float
	*bitpix = -32;
	type = TFLOAT;
	totbytes = totpix * sizeof(float);
      } else {
	type = TINT;
	totbytes = totpix * sizeof(int);
      }
      break;
    case 64:
      if( doscale ){
	// scaled data has to be float
	*bitpix = -32;
	type = TFLOAT;
	totbytes = totpix * sizeof(float);
      } else {
	type = TLONGLONG;
	totbytes = totpix * sizeof(long long);
      }
      break;
    case -32:
      type = TFLOAT;
      totbytes = totpix * sizeof(float);
      break;
    case -64:
      type = TDOUBLE;
      totbytes = totpix * sizeof(double);
      break;
  default:
    return NULL;
  }
#if EM
  // sanity check on memory limits
  if( totbytes > max_memory ){
    *status = MEMORY_ALLOCATION;
    return NULL;
  }
#endif
  // try to allocate that much memory
  if(!(obuf = (void *)malloc(totbytes))){
    *status = MEMORY_ALLOCATION;
    return NULL;
  }
  /* read the image section */
  fits_read_subset(fptr, type, fpixel, lpixel, inc, 0, obuf, 0, status);
  // return pixel buffer (and section dimensions)
  return obuf;
}