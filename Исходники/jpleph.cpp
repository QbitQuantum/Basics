/*****************************************************************************
**                        jpl_state(ephem,et2,list,pv,nut,bary)             **
******************************************************************************
** This subroutine reads and interpolates the jpl planetary ephemeris file  **
**                                                                          **
**    Calling sequence parameters:                                          **
**                                                                          **
**    Input:                                                                **
**                                                                          **
**        et2[] double, 2-element JED epoch at which interpolation          **
**              is wanted.  Any combination of et2[0]+et2[1] which falls    **
**              within the time span on the file is a permissible epoch.    **
**                                                                          **
**               a. for ease in programming, the user may put the           **
**                  entire epoch in et2[0] and set et2[1]=0.0               **
**                                                                          **
**               b. for maximum interpolation accuracy, set et2[0] =        **
**                  the most recent midnight at or before interpolation     **
**                  epoch and set et2[1] = fractional part of a day         **
**                  elapsed between et2[0] and epoch.                       **
**                                                                          **
**               c. as an alternative, it may prove convenient to set       **
**                  et2[0] = some fixed epoch, such as start of integration,**
**                  and et2[1] = elapsed interval between then and epoch.   **
**                                                                          **
**       list   13-element integer array specifying what interpolation      **
**              is wanted for each of the "bodies" on the file.             **
**                                                                          **
**                        list[i]=0, no interpolation for body i            **
**                               =1, position only                          **
**                               =2, position and velocity                  **
**                                                                          **
**              the designation of the astronomical bodies by i is:         **
**                                                                          **
**                        i = 0: mercury                                    **
**                          = 1: venus                                      **
**                          = 2: earth-moon barycenter                      **
**                          = 3: mars                                       **
**                          = 4: jupiter                                    **
**                          = 5: saturn                                     **
**                          = 6: uranus                                     **
**                          = 7: neptune                                    **
**                          = 8: pluto                                      **
**                          = 9: geocentric moon                            **
**                          =10: nutations in lon & obliq (if on file)      **
**                          =11: lunar librations (if on file)              **
**                          =12: lunar mantle omegas                        **
**                          =13: TT-TDB (if on file)                        **
**                                                                          **
** Note that I've not actually seen case 12 yet.  It probably doesn't work. **
**                                                                          **
**    output:                                                               **
**                                                                          **
**    pv[][6]   double array that will contain requested interpolated       **
**              quantities.  The body specified by list[i] will have its    **
**              state in the array starting at pv[i][0]  (on any given      **
**              call, only those words in 'pv' which are affected by the    **
**              first 10 'list' entries (and by list(11) if librations are  **
**              on the file) are set.  The rest of the 'pv' array           **
**              is untouched.)  The order of components in pv[][] is:       **
**              pv[][0]=x,....pv[][5]=dz.                                   **
**                                                                          **
**              All output vectors are referenced to the earth mean         **
**              equator and equinox of epoch. The moon state is always      **
**              geocentric; the other nine states are either heliocentric   **
**              or solar-system barycentric, depending on the setting of    **
**              global variables (see below).                               **
**                                                                          **
**              Lunar librations, if on file, are put into pv[10][k] if     **
**              list[11] is 1 or 2.                                         **
**                                                                          **
**        nut   dp 4-word array that will contain nutations and rates,      **
**              depending on the setting of list[10].  the order of         **
**              quantities in nut is:                                       **
**                                                                          **
**                       d psi  (nutation in longitude)                     **
**                       d epsilon (nutation in obliquity)                  **
**                       d psi dot                                          **
**                       d epsilon dot                                      **
**                                                                          **
*****************************************************************************/
int DLL_FUNC jpl_state(void *ephem, const double et, const int list[14],
                          double pv[][6], double nut[4], const int bary)
{
  struct jpl_eph_data *eph = (struct jpl_eph_data *)ephem;
  unsigned i, j, n_intervals;
  uint32_t nr;
  double *buf = eph->cache;
  double t[2];
  const double block_loc = (et - eph->ephem_start) / eph->ephem_step;
  bool recompute_pvsun;
  const double aufac = 1.0 / eph->au;

/*   error return for epoch out of range  */
  if(et < eph->ephem_start || et > eph->ephem_end)
    return(JPL_EPH_OUTSIDE_RANGE);

/*   calculate record # and relative time in interval   */

  nr = (uint32_t)block_loc;
  t[0] = block_loc - (double)nr;
  if(!t[0] && nr)
  {
    t[0] = 1.;
    nr--;
  }  

/*   read correct record if not in core (static vector buf[])   */
    if(nr != eph->curr_cache_loc)
    {
      eph->curr_cache_loc = nr;
                  /* Read two blocks ahead to account for header: */
      if(FSeek(eph->ifile, (nr + 2) * eph->recsize, SEEK_SET))
      {
	      // GZ: Make sure we will try again on next call...
	      eph->curr_cache_loc=0;
	      return(JPL_EPH_FSEEK_ERROR);
      }
      if(fread(buf, sizeof(double), (size_t)eph->ncoeff, eph->ifile)
                               != (size_t)eph->ncoeff)
        return(JPL_EPH_READ_ERROR);

      if(eph->swap_bytes)
         swap_64_bit_val(buf, eph->ncoeff);
      }
    t[1] = eph->ephem_step;

    if(eph->pvsun_t != et)   /* If several calls are made for the same et, */
    {                      /* don't recompute pvsun each time... only on */
      recompute_pvsun = true;   /* the first run through.                     */
      eph->pvsun_t = et;
    }
    else
      recompute_pvsun = false;

          /* Here, i loops through the "traditional" 14 listed items -- 10
          solar system objects,  nutations,  librations,  lunar mantle angles,
          and TT-TDT -- plus a fifteenth:  the solar system barycenter.  That
          last is quite different:  it's computed 'as needed',  rather than
          from list[];  the output goes to pvsun rather than the pv array;
          and three quantities (position,  velocity,  acceleration) are
          computed (nobody else gets accelerations at present.)  */
  for(n_intervals = 1; n_intervals <= 8; n_intervals *= 2)
    for(i = 0; i < 15; i++)
    {
        unsigned quantities;
        uint32_t *iptr = &eph->ipt[i + 1][0];

        if(i == 14)
        {
            quantities = (recompute_pvsun ? 3 : 0);
            iptr = &eph->ipt[10][0];
          }
          else
          {
            quantities = list[i];
            iptr = &eph->ipt[i < 10 ? i : i + 1][0];
          }
          if(n_intervals == iptr[2] && quantities)
          {
            double *dest = ((i == 10) ? eph->pvsun : pv[i]);

            if(i < 10)
               dest = pv[i];
            else if(i == 14)
               dest = eph->pvsun;
            else
               dest = nut;
            interp(&eph->iinfo, &buf[iptr[0]-1], t, (int)iptr[1],
                                    dimension(i + 1),
                                    n_intervals, quantities, dest);

            if(i < 10 || i == 14)        /*  convert km to AU */
               for(j = 0; j < quantities * 3; j++)
                  dest[j] *= aufac;
            }
         }
    if(!bary)                             /* gotta correct everybody for */
      for(i = 0; i < 9; i++)            /* the solar system barycenter */
         for(j = 0; j < (unsigned)list[i] * 3; j++)
            pv[i][j] -= eph->pvsun[j];
    return(0);
}