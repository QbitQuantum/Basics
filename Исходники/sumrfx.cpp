void
do_sumrfx(const string &fname,const string &mname,double thresh,vector<VBRegion> &rlist)
{
  int i,j,k;
  Tes rfx;
  Cube mask;

  rfx.ReadFile(fname);
  if (!rfx.data_valid) {
    printf("sumrfx: invalid 4D file %s.\n",fname.c_str());
    return;
  }
  // specified mask, intersect with tes mask
  if (mname.size()) {
    mask.ReadFile(mname);
    for (i=0; i<mask.dimx; i++)
      for (j=0; j<mask.dimy; j++)
	for (k=0; k<mask.dimz; k++)
	  if (rfx.GetMaskValue(i,j,k)<0.5)
	    mask.SetValue(i,j,k,0);
  }
  // default mask
  else {
    mask.SetVolume(rfx.dimx,rfx.dimy,rfx.dimz,vb_byte);
    for (i=0; i<mask.dimx; i++)
      for (j=0; j<mask.dimy; j++)
	for (k=0; k<mask.dimz; k++)
	  mask.SetValue(i,j,k,rfx.GetMaskValue(i,j,k));
  }
  if (!mask.data_valid) {
    printf("sumrfx: invalid mask file %s.\n",mname.c_str());
    return;
  }

  if (mask.dimx != rfx.dimx || mask.dimy != rfx.dimy || mask.dimz != rfx.dimz) {
    printf("sumrfx: mask and rfx volume dimensions don't match\n");
    return;
  }

  printf("sumrfx: thresh %.2f mask file: %s\n",thresh,mname.c_str());

  for (i=0; i<rfx.dimt; i++) {
    Cube mycube;
    rfx.getCube(i,mycube);
    if (!mycube.data_valid) continue;
    do_sumcube(rfx.GetFileName(),i,mycube,mask,thresh,rlist);
  }
}