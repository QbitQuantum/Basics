/*!
 * Write Analyze 7.5 image.
 *   Analyze database name must be given with path. Path must exist.
 *   Image and header files with .img and .hdr extensions are created.
 *   Existing files are overwritten.
 *   anaFlipping() determines whether image is flipped in z-direction;
 *   image is always flipped in x,y-directions.
 *   Byte order is determined based on _fileFormat field.
 * 
 * @param dbname analyze database name with path, without extension
 * @param img pointer to IMG data
 * @return 0 if ok, 1 invalid input, 2 invalid image status (image not occupied), 
 * 3 failed to resolve extreme values (min and max),
 * 12 failed to allocate temp memory, 14 failed to open file for writing,
 * 15 failed to write data, 21 failed to write header, and
 * sets IMG->statmsg in case of error
*/
int imgWriteAnalyze(const char *dbname, IMG *img) {
  FILE *fp;
  int ret, fi, pi, xi, yi, little;
  float g;
  ANALYZE_DSR dsr;
  char datfile[FILENAME_MAX], hdrfile[FILENAME_MAX], siffile[FILENAME_MAX];
  const char *cptr;
  int pxlNr=0;
  struct tm *st;
  short int *sdata, *sptr, smin, smax;
  SIF sif;


  if(IMG_TEST) printf("imgWriteAnalyze(%s, *img)\n", dbname);

  /* Check the arguments */
  imgSetStatus(img, STATUS_OK);
  if(img==NULL || img->status!=IMG_STATUS_OCCUPIED) {
    imgSetStatus(img, STATUS_FAULT); return(2);}
  if(dbname==NULL || !dbname[0]) {imgSetStatus(img, STATUS_FAULT); return(1);}
  
  /* Make the image and header filenames */  
  strcpy(datfile, dbname); strcat(datfile, ".img");
  strcpy(hdrfile, dbname); strcat(hdrfile, ".hdr");
  strcpy(siffile, dbname); strcat(siffile, ".sif");


  /*
   *  Fill Analyze header
   */
  if(img->_fileFormat==IMG_ANA_L) dsr.little=1; else dsr.little=0;
  /* Header key */
  memset(&dsr.hk, 0, sizeof(ANALYZE_HEADER_KEY));
  memset(&dsr.dime, 0, sizeof(ANALYZE_HEADER_IMGDIM));
  memset(&dsr.hist, 0, sizeof(ANALYZE_HEADER_HISTORY));
  dsr.hk.sizeof_hdr=348;
  strcpy(dsr.hk.data_type, "");
  cptr=strrchr(dbname, '/'); if(cptr==NULL) cptr=strrchr(dbname, '\\');
  if(cptr!=NULL) cptr++; if(cptr==NULL) cptr=dbname;
  strncpy(dsr.hk.db_name, cptr, 17);
  dsr.hk.extents=16384;
  dsr.hk.regular='r';
  /* Image dimension */
  dsr.dime.dim[0]=4;
  dsr.dime.dim[1]=img->dimx;
  dsr.dime.dim[2]=img->dimy;
  dsr.dime.dim[3]=img->dimz;
  dsr.dime.dim[4]=img->dimt;
  dsr.dime.datatype=ANALYZE_DT_SIGNED_SHORT;
  dsr.dime.bitpix=16;
  dsr.dime.pixdim[0]=0.0;
  dsr.dime.pixdim[1]=img->sizex;
  dsr.dime.pixdim[2]=img->sizey;
  dsr.dime.pixdim[3]=img->sizez;
  dsr.dime.pixdim[4]=0.0;
  dsr.dime.funused1=0.0; /* Scale factor is set later */
  /* dsr.dime.funused2=img->zoom; */ /* Reconstruction zoom */
  dsr.dime.funused3=img->isotopeHalflife;
  /* Data history */
  if(img->decayCorrection==IMG_DC_CORRECTED)
    strcpy(dsr.hist.descrip, "Decay corrected.");
  else if(img->decayCorrection==IMG_DC_NONCORRECTED) 
    strcpy(dsr.hist.descrip, "No decay correction.");
  else
    strcpy(dsr.hist.descrip, "");
  strncpy(dsr.hist.scannum, img->studyNr, 10);
  st=localtime(&img->scanStart);
  if(st!=NULL) {
    strftime(dsr.hist.exp_date, 10, "%Y-%m-%d", st);
    strftime(dsr.hist.exp_time, 10, "%H:%M:%S", st);
  } else {
    strncpy(dsr.hist.exp_date, "1900-01-01", 10);
    strncpy(dsr.hist.exp_time, "00:00:00", 10);
  }

  /*
   *  Scale data to short int range
   *  Determine and set scale factor and cal_min & cal_max
   */
  if(IMG_TEST) printf("scaling data to short ints\n");
  ret=imgMinMax(img, &dsr.dime.cal_min, &dsr.dime.cal_max);
  if(ret) {imgSetStatus(img, STATUS_FAULT); return(3);}
  if(fabs(dsr.dime.cal_min)>fabs(dsr.dime.cal_max)) g=fabs(dsr.dime.cal_min);
  else g=fabs(dsr.dime.cal_max);
  if(g<1E-20) g=1.0; else g=32767./g; dsr.dime.funused1=1.0/g;
  if(IMG_TEST) printf("min=%g max=%g scale_factor=%g\n",
    dsr.dime.cal_min, dsr.dime.cal_max, dsr.dime.funused1);

  /* Allocate memory for short int array */
  pxlNr=(img->dimx)*(img->dimy)*(img->dimz);
  sdata=malloc(pxlNr*sizeof(short int));
  if(sdata==NULL) {
    imgSetStatus(img, STATUS_NOMEMORY);
    return 12;
  }

  /* Open image data file for write */
  if((fp=fopen(datfile, "wb")) == NULL) {
    imgSetStatus(img, STATUS_CANTWRITEIMGFILE);
    free(sdata);
    return 14;
  }

  /* Copy and write image matrix data to short int array */
  /* Data is written one frame at a time */
  smin=smax=temp_roundf(g*img->m[0][0][0][0]);
  for(fi=0; fi<img->dimt; fi++) {
    sptr=sdata;
    if(anaFlipping()==0) {
      for(pi=0; pi<img->dimz; pi++)
        for(yi=img->dimy-1; yi>=0; yi--)
          for(xi=img->dimx-1; xi>=0; xi--) {
            *sptr=temp_roundf(g*img->m[pi][yi][xi][fi]);
            if(*sptr>smax) smax=*sptr; else if(*sptr<smin) smin=*sptr;
            sptr++;
          }
    } else {
      for(pi=img->dimz-1; pi>=0; pi--)
        for(yi=img->dimy-1; yi>=0; yi--)
          for(xi=img->dimx-1; xi>=0; xi--) {
            *sptr=temp_roundf(g*img->m[pi][yi][xi][fi]);
            if(*sptr>smax) smax=*sptr; else if(*sptr<smin) smin=*sptr;
            sptr++;
          }
    }
    /* Change byte order if necessary */
    little=little_endian();
    if(little!=dsr.little)
      swabip(sdata, pxlNr*sizeof(short int));
    /* Write image data */
    if(fwrite(sdata, 2, pxlNr, fp) != pxlNr) {
      imgSetStatus(img, STATUS_CANTWRITEIMGFILE);
      free(sdata); fclose(fp);
      return 15;
    }
  }
  /* Done writing */
  fclose(fp);
  free(sdata);

  if(IMG_TEST) printf("smin=%d smax=%d\n", smin, smax);

  /* Set header glmin & glmax */
  dsr.dime.glmin=smin; dsr.dime.glmax=smax;
  
  /* Write Analyze header */
  ret=anaWriteHeader(hdrfile, &dsr);
  if(ret) {
    imgSetStatus(img, STATUS_CANTWRITEHEADERFILE);
    return 21;
  }
  imgSetStatus(img, STATUS_OK);

  /* Otherwise ready, but check if SIF should/can be written */
  sifInit(&sif);
  /* Try to read existing SIF */
  ret=sifRead(siffile, &sif);
  if(ret==0) { // SIF could be read
    if(sif.frameNr==img->dimt) {
      /* If size matches, then update the contents, but keep counts, in case
         previous SIF comes with actual count info from scanner */
      ret=img2sif(img, &sif, 1, 1, 0);
    } else {
      /* otherwise create SIF contents */
      ret=img2sif(img, &sif, 1, 1, 1);
    }
  } else {
    /* otherwise create SIF contents */
    ret=img2sif(img, &sif, 1, 1, 1);
  }
  if(ret!=0) {
    /* SIF data could not be made: do not give error, just do not write it */
    if(IMG_TEST>0) printf("SIF contents could not be filled.\n");
    return 0;
  }
  /* Write SIF */
  ret=sifWrite(&sif, siffile);  
  if(ret!=0) {
    /* SIF could not be written: do not give error, just do not write it */
    if(IMG_TEST>0)
      fprintf(stderr, "Error: SIF could not be written (%d).\n", ret);
  }

  imgSetStatus(img, STATUS_OK);
  return 0;
}