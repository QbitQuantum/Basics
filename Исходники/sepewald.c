void _sep_3D_ewald_short_bond(sepatom *ptr, double kappa, double cf, sep3D *sys){
  double Ucol, rv[3], r2, r, ft, f, erfckr=0, erfkr, zizj, krsq;
  int i1, i2, n, k;
  const double A = 2*kappa/sqrt(SEP_PI), cf2 = cf*cf;


  Ucol = 0.0;
  for (i1 = 0; i1 < sys->npart; i1++){
    n = 0;
    while (1){
      i2 = ptr[i1].neighb[n];
      if (i2 == -1) break;

      r2 = 0.0;
      for (k=0; k<3; k++){
	rv[k] = ptr[i1].x[k] - ptr[i2].x[k];
	if (sys->bound[k] == 'p'){
	  sep_Wrap( rv[k], sys->length[k] );
	}	
	r2 += rv[k]*rv[k];
      }

      r = sqrt(r2);
      krsq = kappa*kappa*r2;
      zizj = ptr[i1].z*ptr[i2].z;
       
      // Not same molecule - short ranged real space contribution
      if ( (ptr[i1].molindex == -1 && r2<cf2) || 
	   (ptr[i1].molindex != ptr[i2].molindex && r2<cf2) ){ 
	erfckr = erfc(kappa*r)/r;
	ft = zizj*(erfckr + A*exp(-krsq))/r2;
	for ( k=0; k<3; k++ ){
	  f = ft*rv[k];
	  ptr[i1].a[k] += f/ptr[i1].m;
	  ptr[i2].a[k] -= f/ptr[i2].m;
	}
	
	Ucol += zizj*erfckr;
      }
      // Same molecule no real space contribution, but remove 
      // the self part from the Fourier part
      else if ( ptr[i1].molindex == ptr[i2].molindex ){
	erfkr = erf(kappa*r)/r;
      	ft = -zizj*(erfkr - A*exp(-krsq))/r2;
	for ( k=0; k<3; k++ ){
	  f = ft*rv[k];
	  ptr[i1].a[k] += f/ptr[i1].m;
	  ptr[i2].a[k] -= f/ptr[i2].m;
	}
	
	Ucol -= zizj*erfckr;
      }

      n++;
    }
  }

  sys->retval[0] = Ucol;
}