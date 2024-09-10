/*----------------------------------------------------------------------
            Parameters:

           Description:
----------------------------------------------------------------------*/
MRI *
MRIprobabilityThresholdNeighborhoodOn(MRI *mri_src, MRI *mri_prob,MRI *mri_dst,
                                      float threshold, int nsize, int out_label)
{
    BUFTYPE   *pprob, out_val ;
    int       width, height, depth, x, y, z, x1, y1, z1, xi, yi, zi,
              xmin, xmax, ymin, ymax, zmin, zmax, nchanged ;
    float     nvox ;

    if (mri_prob->type != MRI_UCHAR)
        ErrorReturn(NULL, (ERROR_UNSUPPORTED,
                           "MRI3Dthreshold: prob must be MRI_UCHAR")) ;

    if (!mri_dst)
        mri_dst = MRIclone(mri_src, NULL) ;

    width = mri_src->width ;
    height = mri_src->height ;
    depth = mri_src->depth ;


    /* now apply the inverse morph to build an average wm representation
       of the input volume
       */

    xmin = width ;
    ymin = height ;
    zmin = depth ;
    xmax = ymax = zmax = 0 ;
    for (z = 0 ; z < depth ; z++)
    {
        for (y = 0 ; y < height ; y++)
        {
            pprob = &MRIvox(mri_prob, 0, y, z) ;
            for (x = 0 ; x < width ; x++)
            {
                if (*pprob++ > threshold)
                {
                    if (x < xmin)
                        xmin = x ;
                    if (x > xmax)
                        xmax = x ;
                    if (y < ymin)
                        ymin = y ;
                    if (y > ymax)
                        ymax = y ;
                    if (z < zmin)
                        zmin = z ;
                    if (z > zmax)
                        zmax = z ;
                }
            }
        }
    }
    xmin = MAX(xmin-nsize, 0) ;
    ymin = MAX(ymin-nsize, 0) ;
    zmin = MAX(zmin-nsize, 0) ;
    xmax = MIN(xmax+nsize, width-1) ;
    ymax = MIN(ymax+nsize, height-1) ;
    zmax = MIN(zmax+nsize, depth-1) ;

    if (Gdiag & DIAG_SHOW && DIAG_VERBOSE_ON)
        fprintf(stderr, "bounding box = (%d:%d, %d:%d, %d:%d).\n",
                xmin, xmax, ymin, ymax, zmin, zmax) ;

#if 0
    xmin = ymin = zmin = 0 ;
    xmax = width-1 ;
    ymax = height-1 ;
    zmax = depth-1 ;
#endif

    nchanged = 0 ;
    for (z = zmin ; z <= zmax ; z++)
    {
        for (y = ymin ; y <= ymax ; y++)
        {
            for (x = xmin ; x <= xmax ; x++)
            {
                if (DEBUG_POINT(x,y,z))
                    DiagBreak() ;
                out_val = out_label ;
                for (z1 = -nsize ; z1 <= nsize ; z1++)
                {
                    zi = mri_src->zi[z+z1] ;
                    for (y1 = -nsize ; y1 <= nsize ; y1++)
                    {
                        yi = mri_src->yi[y+y1] ;
                        for (x1 = -nsize ; x1 <= nsize ; x1++)
                        {
                            xi = mri_src->xi[x+x1] ;
                            if (MRIvox(mri_prob, xi, yi, zi) < threshold)
                            {
                                out_val = MRIvox(mri_src, x, y, z) ;
                                break ;
                            }
                        }
                    }
                }
                if (out_val == out_label && MRIvox(mri_src,x,y,z) != out_label)
                    nchanged++ ;
                MRIvox(mri_dst, x, y, z) = out_val ;
            }
        }
    }

    nvox = (float)(width*height*depth) ;
    fprintf(stderr, "%8d of %8d voxels changed - %2.1f%%.\n",
            nchanged, (int)nvox, 100.0f*(float)nchanged/nvox) ;

    return(mri_dst) ;
}