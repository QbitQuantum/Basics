int pointblankrange_calculate(lpPointBlankRange pointblankrange)
{
  Vector dr, r, tv, v, w;
  double mv, vm, elev, mh, vz, bw;
  double dt, eq, t, mach, drg;
  int    i, itcnt, mhr;

/* Set values that don't change for the pointblankrange... */
  if (pointblankrange->alc) 
    atmos_standardalt(pointblankrange->atmos);
  else 
    atmos_atmos(pointblankrange->atmos);
  mach = pointblankrange->atmos->mach;
  eq = pointblankrange->atmos->density/ATMOS_DENSSTD;
  vz = INTOFT(pointblankrange->vital_zone);
  bw = pointblankrange->bullet_weight;


  itcnt = 0;
  pointblankrange->found = 0;
  elev = vz/(250.0*PBR_DX);
  while ((!pointblankrange->found) && (itcnt < PBR_MAXIMUM_ITCNT))
  {
    vm = pointblankrange->muzzle_velocity;
    pointblankrange->muzzle_energy = PBR_ENERGY(bw, vm);
    t = 0.0;
    mh = INTOFT(-pointblankrange->sight_height);
    r = vector(0.0, mh, 0.0);
    dr = vector(0.0, 0.0, 0.0);
    v.x = vm*cos(elev);
    v.y = vm*sin(elev);
    v.z = 0.0;

    for (i = 0; (r.y > -vz); i++)
    {

      if (vm < PBR_ABSMINVX) break;

      vm  = LENGTH(v);
      dt  = 0.5*PBR_DX/v.x;
      drg = eq*vm*bc_getdrag(pointblankrange->bc, vm/mach);
      tv  = SUBTRACT(v, MULTIPLY(dt, SUBTRACT(MULTIPLY(drg, v), PBR_GRAVITY)));
      vm  = LENGTH(tv);
      dt  = PBR_DX/tv.x;
      drg = eq*vm*bc_getdrag(pointblankrange->bc, vm/mach);
      v   = SUBTRACT(v, MULTIPLY(dt, SUBTRACT(MULTIPLY(drg, tv), PBR_GRAVITY)));
      dr  = vector(PBR_DX, v.y*dt, v.z*dt);
      r   = ADD(r, dr);
      t   = t + LENGTH(dr)/vm;
      vm  = LENGTH(v);

      if (r.y > 0.0) pointblankrange->pbzero = i;
      pointblankrange->pbrange = i;

      if (r.y > mh)
      {
	mh = r.y;
	mhr = i;
      }
    }
    pointblankrange->found = (fabs(mh - vz) < PBR_MAXIMUM_ERROR);
    if (!pointblankrange->found)
    {
      elev = elev - (mh - vz)/(mhr*PBR_DX);
    }
    itcnt++;
    pointblankrange->terminal_energy = PBR_ENERGY(bw, vm);
  }

  return 0;
}