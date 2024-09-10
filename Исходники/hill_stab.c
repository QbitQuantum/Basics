void cartes(double *x, double *v, ELEMS elem_ptr,double mu) {
  double a,e,m,cosi,sini,cos_lasc,sin_lasc,cos_aper,sin_aper;
  double es,ec,w,wp,wpp,wppp,ecc,dx,lo,up,next;int iter;
  double sin_ecc,cos_ecc,l1,m1,n1,l2,m2,n2;
  double xi,eta,vel_scl;

  a = elem_ptr.a;
  e = elem_ptr.e;
  m = elem_ptr.mean_an;
  cosi = cos(elem_ptr.i);
  sini = sin(elem_ptr.i);
  cos_lasc = cos(elem_ptr.lasc);
  sin_lasc = sin(elem_ptr.lasc);
  cos_aper = cos(elem_ptr.aper);
  sin_aper = sin(elem_ptr.aper);

  /*
   * Reduce mean anomoly to [0, 2*PI)
   */
  m -= ((int)(m/(2*M_PI)))*2*M_PI;
  /*
   * Solve kepler's equation.
   */
  if (sin(m)>0)
    ecc = m+0.85*e;
  else 
    ecc = m-0.85*e;
  lo = -2*M_PI;
  up = 2*M_PI;
  for(iter=1;iter<=32;iter++) {
    es = e*sin(ecc);
    ec = e*cos(ecc);
    w = ecc-es-m;
    wp = 1-ec;
    wpp = es;
    wppp = ec;
    if (w>0)
      up = ecc;
    else 
      lo = ecc;
    dx = -w/wp;
    dx = -w/(wp+dx*wpp/2);
    dx = -w/(wp+dx*wpp/2+dx*dx*wppp/6);
    next = ecc+dx;
    if (ecc==next) 
      break;
    if ((next>lo) && (next<up))
      ecc= next;
    else ecc= (lo+up)/2;
    if((ecc==lo) || (ecc==up))
      break;
    if (iter>30)
      printf("%4d %23.20f %e\n",iter,ecc,up-lo);
  }
  if(iter>32) {
    fprintf(stderr,"ERROR: Kepler solultion failed.\n");
    exit(1);
  }

  cos_ecc = cos(ecc);
  sin_ecc = sin(ecc);

  l1 = cos_lasc*cos_aper-sin_lasc*sin_aper*cosi;
  m1 = sin_lasc*cos_aper+cos_lasc*sin_aper*cosi;
  n1 = sin_aper*sini;
  l2 = -cos_lasc*sin_aper-sin_lasc*cos_aper*cosi;
  m2 = -sin_lasc*sin_aper+cos_lasc*cos_aper*cosi;
  n2 = cos_aper*sini;

  xi = a*(cos_ecc-e);
  eta = a*sqrt(1-e*e)*sin_ecc;
  x[0] = l1*xi+l2*eta;
  x[1] = m1*xi+m2*eta;
  x[2] = n1*xi+n2*eta;
  vel_scl = sqrt((mu*a)/dot(x,x));
  xi = -vel_scl*sin_ecc;
  eta = vel_scl*sqrt(1-e*e)*cos_ecc;
  v[0] = l1*xi+l2*eta;
  v[1] = m1*xi+m2*eta;
  v[2] = n1*xi+n2*eta;
}