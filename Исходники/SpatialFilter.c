void
VSpatialFilter(VAttrList list,VDouble fwhm)
{
  VAttrListPosn posn;
  VImage src[NSLICES],xsrc=NULL,tmp=NULL,dest=NULL,kernel=NULL,tmp2d=NULL;
  VString str=NULL;
  float v0,v1,v2,v3;
  int b,r,c,i,size;
  int n,nslices,nrows,ncols,dim;
  double u, sigma=0;
  extern VImage VGaussianConv (VImage,VImage,VBand,double,int);


  /* get image dimensions */
  dim = 3;
  v0 = v1 = v2 = v3 = 1;
  n = i = nrows = ncols = 0;
  str = VMalloc(100);
  for (VFirstAttr (list, & posn); VAttrExists (& posn); VNextAttr (& posn)) {
    if (i >= NSLICES) VError(" too many slices");
    if (VGetAttrRepn (& posn) != VImageRepn) continue;
    VGetAttrValue (& posn, NULL,VImageRepn, & xsrc);
    if (VPixelRepn(xsrc) != VShortRepn) continue;
    if (VImageNBands(xsrc) > n) n = VImageNBands(xsrc);
    if (VImageNRows(xsrc) > nrows) nrows = VImageNRows(xsrc);
    if (VImageNColumns(xsrc) > ncols) ncols = VImageNColumns(xsrc);
    if (VGetAttr (VImageAttrList (xsrc), "voxel", NULL,VStringRepn, (VPointer) & str) == VAttrFound) {
      sscanf(str,"%f %f %f",&v1,&v2,&v3);
    }
    src[i] = xsrc;
    i++;    
  }
  nslices = i;


  /* in general, apply 3D spatial filtering */
  dim = 3;

  /* only if clearly non-isotropic apply 2D filtering */
  v0 = 0.5*(v1+v2);
  if (ABS(v0-v3) > 0.5) dim = 2;


  /*
  ** Sigma
  */
  sigma  = fwhm/sqrt(8.0*log(2.0));
  sigma /= (double)v1;


  /*
  ** 2D gauss filtering
  */
  if (dim==2) {
    fprintf(stderr," 2D spatial filter: fwhm=  %.3f mm sigma= %.3f vox\n",fwhm,sigma); 

    size = (int)(6.0 * sigma + 1.5);
    if ((size & 1) == 0) size++;
    fprintf(stderr," size= %d\n",size);

    for (b=0; b<nslices; b++) {
      if (VImageNRows(src[b]) < 2) continue;
      tmp2d  = VGaussianConv(src[b],tmp2d, VAllBands, sigma, size);
      src[b] = VCopyImagePixels(tmp2d,src[b],VAllBands);
    }
    VDestroyImage(tmp2d);
  }


  /*
  ** 3D gauss filtering
  */
  if (dim==3) {
    fprintf(stderr," 3D spatial filter: fwhm=  %.3f mm sigma= %.3f vox\n",fwhm,sigma); 

    kernel = VSGaussKernel(sigma);

    tmp = VCreateImage(nslices,nrows,ncols,VFloatRepn);
    VFillImage(tmp,VAllBands,0);
    
    for (i=0; i<n; i++) {
      if (i%20 == 0) fprintf(stderr," i= %5d\r",i);
      
      VFillImage(tmp,VAllBands,0);
      for (b=0; b<nslices; b++) {
	if (VImageNRows(src[b]) < 2) continue;
	for (r=0; r<nrows; r++) {
	  for (c=0; c<ncols; c++) {
	    u = VPixel(src[b],i,r,c,VShort);
	    VPixel(tmp,b,r,c,VFloat) = u;
	  }
	}
      }
      
      dest = VGauss3d (tmp,dest,kernel);
      
      for (b=0; b<nslices; b++) {
	if (VImageNRows(src[b]) < 2) continue;
	for (r=0; r<nrows; r++) {
	  for (c=0; c<ncols; c++) {
	    u = VPixel(dest,b,r,c,VFloat);
	    VPixel(src[b],i,r,c,VShort) = u;
	  }
	}
      }
    }
  }


}