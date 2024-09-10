/*
Final processing of object data, just before saving it to the catalog.
*/
void	endobject(picstruct *field, picstruct *dfield, picstruct *wfield,
		picstruct *dwfield, int n, objliststruct *objlist)
  {
   checkstruct	*check;
   int		i,j, ix,iy,selecflag, newnumber,nsub;
   objstruct	*obj;

  obj = &objlist->obj[n];

/* Current FITS extension */
  obj2->ext_number = thecat.currext;

/* Source position */
  obj2->sposx = (float)(obj2->posx = obj->mx+1.0); /* That's standard FITS */
  obj2->sposy = (float)(obj2->posy = obj->my+1.0);

/* Integer coordinates */
  ix=(int)(obj->mx+0.49999);
  iy=(int)(obj->my+0.49999);

/* Association */
  if (prefs.assoc_flag)
    obj2->assoc_number = do_assoc(field, obj2->sposx, obj2->sposy);

  if (prefs.assoc_flag && prefs.assocselec_type!=ASSOCSELEC_ALL)
    selecflag = (prefs.assocselec_type==ASSOCSELEC_MATCHED)?
		obj2->assoc_number:!obj2->assoc_number;
  else
    selecflag = 1;

  if (selecflag)
    {
/*-- Paste back to the image the object's pixels if BLANKing is on */
    if (prefs.blank_flag)
      {
      pasteimage(field, obj->blank, obj->subw, obj->subh,
		obj->subx, obj->suby);
      if (obj->dblank)
        pasteimage(dfield, obj->dblank, obj->subw, obj->subh,
		obj->subx, obj->suby);
      }

/*------------------------- Error ellipse parameters ------------------------*/
    if (FLAG(obj2.poserr_a))
      {
       double	pmx2,pmy2,temp,theta;

      if (fabs(temp=obj->poserr_mx2-obj->poserr_my2) > 0.0)
        theta = atan2(2.0 * obj->poserr_mxy,temp) / 2.0;
      else
        theta = PI/4.0;

      temp = sqrt(0.25*temp*temp+obj->poserr_mxy*obj->poserr_mxy);
      pmy2 = pmx2 = 0.5*(obj->poserr_mx2+obj->poserr_my2);
      pmx2+=temp;
      pmy2-=temp;

      obj2->poserr_a = (float)sqrt(pmx2);
      obj2->poserr_b = (float)sqrt(pmy2);
      obj2->poserr_theta = theta*180.0/PI;
      }

    if (FLAG(obj2.poserr_cxx))
      {
       double	xm2,ym2, xym, temp;

      xm2 = obj->poserr_mx2;
      ym2 = obj->poserr_my2;
      xym = obj->poserr_mxy;
      obj2->poserr_cxx = (float)(ym2/(temp=xm2*ym2-xym*xym));
      obj2->poserr_cyy = (float)(xm2/temp);
      obj2->poserr_cxy = (float)(-2*xym/temp);
      }

/* ---- Aspect ratio */

    if (FLAG(obj2.elong))
      obj2->elong = obj->a/obj->b;

    if (FLAG(obj2.ellip))
      obj2->ellip = 1-obj->b/obj->a;

    if (FLAG(obj2.polar))
      obj2->polar = (obj->a*obj->a - obj->b*obj->b)
		/ (obj->a*obj->a + obj->b*obj->b);

/*------------------------------- Photometry -------------------------------*/

/*-- Convert the father of photom. error estimates from variance to RMS */
    obj2->flux_iso = obj->flux;
    obj2->fluxerr_iso = sqrt(obj->fluxerr);
    if (FLAG(obj.flux_prof))
      {
      obj2->flux_prof = obj->flux_prof;
      obj2->fluxerr_prof = sqrt(obj->fluxerr_prof);
      }

    if (FLAG(obj2.flux_isocor))
      computeisocorflux(field, obj);

    if (FLAG(obj2.flux_aper))
      for (i=0; i<prefs.naper; i++)
        computeaperflux(field, wfield, obj, i);

    if (FLAG(obj2.flux_auto))
      computeautoflux(field, dfield, wfield, dwfield, obj);

    if (FLAG(obj2.flux_petro))
      computepetroflux(field, dfield, wfield, dwfield, obj);

/*-- Growth curve */
    if (prefs.growth_flag)
      makeavergrowth(field, wfield, obj);

/*--------------------------- Windowed barycenter --------------------------*/
    if (FLAG(obj2.winpos_x))
      compute_winpos(field, wfield, obj);

/*-- What about the peak of the profile? */
    if (obj->peak+obj->bkg >= prefs.satur_level)
      obj->flag |= OBJ_SATUR;

/*-- Check-image CHECK_APERTURES option */

    if ((check = prefs.check[CHECK_APERTURES]))
      {
      if (FLAG(obj2.flux_aper))
        for (i=0; i<prefs.naper; i++)
          sexcircle(check->pix, check->width, check->height,
		obj->mx, obj->my, prefs.apert[i]/2.0, check->overlay);

      if (FLAG(obj2.flux_auto))
        sexellips(check->pix, check->width, check->height,
	obj->mx, obj->my, obj->a*obj2->kronfactor,
	obj->b*obj2->kronfactor, obj->theta,
	check->overlay, obj->flag&OBJ_CROWDED);

      if (FLAG(obj2.flux_petro))
        sexellips(check->pix, check->width, check->height,
	obj->mx, obj->my, obj->a*obj2->petrofactor,
	obj->b*obj2->petrofactor, obj->theta,
	check->overlay, obj->flag&OBJ_CROWDED);
      }

/* ---- Star/Galaxy classification */

    if (FLAG(obj2.sprob))
      {
       int	j;
       double	fac2, input[10], output, fwhm;

      fwhm = prefs.seeing_fwhm;

      fac2 = fwhm/field->pixscale;
      fac2 *= fac2;
      input[j=0] = log10(obj->iso[0]? obj->iso[0]/fac2: 0.01);
      input[++j] = field->thresh>0.0?
		  log10(obj->peak>0.0? obj->peak/field->thresh: 0.1)
		 :-1.0;
      for (i=1; i<NISO; i++)
        input[++j] = log10(obj->iso[i]? obj->iso[i]/fac2: 0.01);
      input[++j] = log10(fwhm);
      neurresp(input, &output);
      obj2->sprob = (float)output;
      }

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*-- Put here your calls to "BLIND" custom functions. Ex:

    compute_myotherparams(obj); 

--*/

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

    newnumber = ++thecat.ntotal;
/*-- update segmentation map */
    if ((check=prefs.check[CHECK_SEGMENTATION]))
      {
       ULONG	*pix;
       ULONG	newsnumber = newnumber,
		oldsnumber = obj->number;
       int	dx,dx0,dy,dpix;

      pix = (ULONG *)check->pix + check->width*obj->ymin + obj->xmin;
      dx0 = obj->xmax-obj->xmin+1;
      dpix = check->width-dx0;
      for (dy=obj->ymax-obj->ymin+1; dy--; pix += dpix)
        for (dx=dx0; dx--; pix++)
          if (*pix==oldsnumber)
            *pix = newsnumber;
      }
    obj->number = newnumber;

    if (FLAG(obj2.vignet))
      copyimage(field,outobj2.vignet,prefs.vignetsize[0],prefs.vignetsize[1],
	ix,iy);

    if (FLAG(obj2.vigshift))
      copyimage_center(field, outobj2.vigshift, prefs.vigshiftsize[0],
		prefs.vigshiftsize[1], obj->mx, obj->my);

/*--- Express everything in magnitude units */
    computemags(field, obj);

/*------------------------------- PSF fitting ------------------------------*/
    nsub = 1;
    if (prefs.psf_flag)
      {
      psf_fit(thepsf, field, wfield, obj);
      obj2->npsf = thepsfit->npsf;
      if (prefs.psfdisplay_type == PSFDISPLAY_SPLIT)
        {
        nsub = thepsfit->npsf;
        if (nsub<1)
          nsub = 1;
        }
      else
        for (j=0; j<thepsfit->npsf; j++)
          {
          if (FLAG(obj2.x_psf) && j<prefs.psf_xsize)
            obj2->x_psf[j] = thepsfit->x[j];
          if (FLAG(obj2.y_psf) && j<prefs.psf_ysize)
            obj2->y_psf[j] = thepsfit->y[j];
          if (FLAG(obj2.flux_psf) && j<prefs.psf_fluxsize)
            obj2->flux_psf[j] = thepsfit->flux[j];
          if (FLAG(obj2.mag_psf) && j<prefs.psf_magsize)
            obj2->mag_psf[j] = thepsfit->flux[j]>0.0?
		prefs.mag_zeropoint -2.5*log10(thepsfit->flux[j]) : 99.0;
          }
      }

/*-------------------------------- Astrometry ------------------------------*/
    if (prefs.world_flag)
      computeastrom(field, obj);
/*-- Edit min and max coordinates to follow the FITS conventions */
    obj->xmin += 1;
    obj->ymin += 1;
    obj->xmax += 1;
    obj->ymax += 1;

/*-- Go through each newly identified component */
    for (j=0; j<nsub; j++)
      {
      if (prefs.psf_flag && prefs.psfdisplay_type == PSFDISPLAY_SPLIT)
        {
        if (FLAG(obj2.x_psf))
          obj2->x_psf[0] = thepsfit->x[j];
        if (FLAG(obj2.y_psf))
          obj2->y_psf[0] = thepsfit->y[j];
        if (FLAG(obj2.flux_psf))
          obj2->flux_psf[0] = thepsfit->flux[j];
        if (FLAG(obj2.mag_psf))
          obj2->mag_psf[0] = thepsfit->flux[j]>0.0?
		prefs.mag_zeropoint -2.5*log10(thepsfit->flux[j]) : 99.0;
        if (j)
          obj->number = ++thecat.ntotal;
        }

      FPRINTF(OUTPUT, "%8d %6.1f %6.1f %5.1f %5.1f %12g "
			"%c%c%c%c%c%c%c%c\n",
	obj->number, obj->mx+1.0, obj->my+1.0,
	obj->a, obj->b,
	obj->flux,
	obj->flag&OBJ_CROWDED?'C':'_',
	obj->flag&OBJ_MERGED?'M':'_',
	obj->flag&OBJ_SATUR?'S':'_',
	obj->flag&OBJ_TRUNC?'T':'_',
	obj->flag&OBJ_APERT_PB?'A':'_',
	obj->flag&OBJ_ISO_PB?'I':'_',
	obj->flag&OBJ_DOVERFLOW?'D':'_',
	obj->flag&OBJ_OVERFLOW?'O':'_');
      writecat(n, objlist);
      }
    }


 if (prefs.user_ana) prefs.user_ana(obj, obj2); /* pour TOADS */


/* Remove again from the image the object's pixels if BLANKing is on ... */
/*-- ... and free memory */

  if (prefs.blank_flag && obj->blank)
    {
    if (selecflag)
      {
      if (prefs.somfit_flag && (check=prefs.check[CHECK_MAPSOM]))
        blankcheck(check, obj->blank, obj->subw, obj->subh,
		obj->subx, obj->suby, (PIXTYPE)*(obj2->vector_somfit));

      }
    blankimage(field, obj->blank, obj->subw, obj->subh,
		obj->subx, obj->suby, -BIG);
    free(obj->blank);
    if (obj->dblank)
      {
      blankimage(dfield, obj->dblank, obj->subw, obj->subh,
		obj->subx, obj->suby, -BIG);
      free(obj->dblank);
      }
    }

  return;
  }