static MRI *
MRIcomputeSurfaceDistanceIntensities(MRI_SURFACE *mris,  MRI *mri_ribbon, MRI *mri_aparc, MRI *mri, MRI *mri_aseg, int whalf) 
{
  MRI          *mri_features, *mri_binary, *mri_white_dist, *mri_pial_dist ;
  int          vno, ngm, outside_of_ribbon, label0, label, ohemi_label, xi, yi, zi, xk, yk, zk, x0, y0, z0, hemi_label, assignable ;
  double       xv, yv, zv, step_size, dist, thickness, wdist, pdist, snx, sny, snz, nx, ny, nz, xl, yl, zl, x, y, z, dot, angle ;
  VERTEX       *v ;

  mri_features = MRIallocSequence(mris->nvertices, 1, 1, MRI_FLOAT, 1) ;  // one samples inwards, one in ribbon, and one outside
  MRIcopyHeader(mri, mri_features) ;

  mri_binary = MRIcopy(mri_ribbon, NULL) ;
  mri_binary = MRIbinarize(mri_ribbon, NULL, 1, 0, 1) ;
  mri_pial_dist = MRIdistanceTransform(mri_binary, NULL, 1, max_pial_dist+1, DTRANS_MODE_SIGNED,NULL);
  if (Gdiag & DIAG_WRITE && DIAG_VERBOSE_ON)
    MRIwrite(mri_pial_dist, "pd.mgz") ;

  MRIclear(mri_binary) ;
  MRIcopyLabel(mri_ribbon, mri_binary, Left_Cerebral_White_Matter) ;
  MRIcopyLabel(mri_ribbon, mri_binary, Right_Cerebral_White_Matter) ;
  MRIbinarize(mri_binary, mri_binary, 1, 0, 1) ;
  mri_white_dist = MRIdistanceTransform(mri_binary, NULL, 1, max_white_dist+1, DTRANS_MODE_SIGNED,NULL);
  if (Gdiag & DIAG_WRITE && DIAG_VERBOSE_ON)
    MRIwrite(mri_white_dist, "wd.mgz") ;

  if (mris->hemisphere == LEFT_HEMISPHERE)
  {
    ohemi_label = Right_Cerebral_Cortex ;
    hemi_label = Left_Cerebral_Cortex ;
  }
  else
  {
    hemi_label = Right_Cerebral_Cortex ;
    ohemi_label = Left_Cerebral_Cortex ;
  }

  step_size = mri->xsize/2 ;
  for (vno = 0 ; vno < mris->nvertices ; vno++)
  {
    v = &mris->vertices[vno] ;
    if (vno == Gdiag_no)
      DiagBreak() ;
    if (v->ripflag)
      continue ;  // not cortex
    nx = v->pialx - v->whitex ; ny = v->pialy - v->whitey ; nz = v->pialz - v->whitez ;
    thickness = sqrt(nx*nx + ny*ny + nz*nz) ;
    if (FZERO(thickness))
      continue ;   // no  cortex here


    x = (v->pialx + v->whitex)/2 ; y = (v->pialy + v->whitey)/2 ; z = (v->pialz + v->whitez)/2 ;  // halfway between white and pial is x0
    MRISsurfaceRASToVoxelCached(mris, mri_aseg, x, y, z, &xl, &yl, &zl) ;
    x0 = nint(xl); y0 = nint(yl) ; z0 = nint(zl) ;
    label0 = MRIgetVoxVal(mri_aparc, x0, y0, z0,0) ;

    // compute surface normal in voxel coords
    MRISsurfaceRASToVoxelCached(mris, mri_aseg, x+v->nx, y+v->ny, z+v->nz, &snx, &sny, &snz) ;
    snx -= xl ; sny -= yl ; snz -= zl ;

    for (ngm = 0, xk = -whalf ; xk <= whalf ; xk++)
    {
      xi = mri_aseg->xi[x0+xk] ;
      for (yk = -whalf ; yk <= whalf ; yk++)
      {
	yi = mri_aseg->yi[y0+yk] ;
	for (zk = -whalf ; zk <= whalf ; zk++)
	{
	  zi = mri_aseg->zi[z0+zk] ;
	  label = MRIgetVoxVal(mri_aseg, xi, yi, zi,0) ;
	  if (xi == Gx && yi == Gy && zi == Gz)
	    DiagBreak() ;
	  if (label != hemi_label)
	    continue ;
	  label = MRIgetVoxVal(mri_aparc, xi, yi, zi,0) ;
	  if (label && label != label0)  // if  outside the ribbon it won't be assigned to a parcel
	    continue ;  // constrain it to be in the same cortical parcel

	  // search along vector connecting x0 to this point to make sure it is we don't perforate wm or leave and re-enter cortex
	  nx = xi-x0 ; ny = yi-y0 ; nz = zi-z0 ;
	  thickness = sqrt(nx*nx + ny*ny + nz*nz) ;
	  assignable = 1 ;  // assume this point should be counted
	  if (thickness > 0)
	  {
	    nx /= thickness ; ny /= thickness ; nz /= thickness ;
	    dot = nx*snx + ny*sny + nz*snz ; angle = acos(dot) ;
	    if (FABS(angle) > angle_threshold)
	      assignable = 0 ;
	    outside_of_ribbon = 0 ;
	    for (dist = 0 ; assignable && dist <= thickness ; dist += step_size) 
	    {
	      xv = x0+nx*dist ;  yv = y0+ny*dist ;  zv = z0+nz*dist ; 
	      if (nint(xv) == Gx && nint(yv) == Gy && nint(zv) == Gz)
		DiagBreak() ;
	      MRIsampleVolume(mri_pial_dist, xv, yv, zv, &pdist) ;
	      MRIsampleVolume(mri_white_dist, xv, yv, zv, &wdist) ;
	      label = MRIgetVoxVal(mri_aseg, xi, yi, zi,0) ;
	      if (SKIP_LABEL(label) || label == ohemi_label)
		assignable = 0 ;
	      if (wdist < 0)  // entered wm - not assignable
		assignable = 0 ;
	      else
	      {
		if (pdist > 0)  // outside pial surface
		  outside_of_ribbon = 1 ;
		else
		{
		  if (outside_of_ribbon) // left ribbon and reentered
		    assignable = 0 ;
		}
	      }
	    }
	  }  // close of thickness > 0
	  if (assignable)
	    ngm++ ;
	  else
	    DiagBreak() ;
	}
      }
    }
    
    MRIsetVoxVal(mri_features, vno, 0, 0, 0, ngm) ;
  }

  MRIfree(&mri_white_dist) ; MRIfree(&mri_pial_dist) ; MRIfree(&mri_binary) ;
  return(mri_features) ;
}