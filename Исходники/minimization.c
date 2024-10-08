void BracketMin (TSIL_REAL *ax, TSIL_REAL *bx, TSIL_REAL *cx, 
		 TSIL_REAL *fa, TSIL_REAL *fb, TSIL_REAL *fc, 
		 TSIL_REAL (*func)(TSIL_REAL))
{
  TSIL_REAL ulim, u, r, q, fu, dum;

  *fa = (*func)(*ax);
  *fb = (*func)(*bx);
  if (*fb > *fa) {
    SHFT(dum,*ax,*bx,dum) ;
    SHFT(dum,*fb,*fa,dum) ;
  }
  *cx = (*bx) + GOLD*(*bx - *ax);
  *fc = (*func)(*cx);
  while (*fb > *fc) {
    r = (*bx - *ax)*(*fb - *fc);
    q = (*bx - *cx)*(*fb - *fa);
    u = (*bx) - ((*bx - *cx)*q - (*bx - *ax)*r)/
      (2.0L*SIGN(FMAX(TSIL_FABS(q-r),TINY), q-r));
    ulim = (*bx) + GLIMIT*(*cx - *bx);

    if ((*bx - u)*(u - *cx) > 0.0) {
      fu = (*func)(u);
      if (fu < *fc) {
	*ax = *bx;
	*bx = u;
	*fa = *fb;
	*fb = fu;
	return;
      }
      else if (fu > *fb) {
	*cx = u;
	*fc = fu;
	return;
      }
      u = (*cx) + GOLD*(*cx - *bx);
      fu = (*func)(u);
    }
    else if ((*cx - u)*(u - ulim) > 0.0) {
      fu = (*func)(u);
      if (fu < *fc) {
	SHFT(*bx,*cx,u,*cx + GOLD*(*cx - *bx)) ;
	SHFT(*fb,*fc,fu,(*func)(u)) ;
      }
    }
    else if ((u-ulim)*(ulim-*cx) >= 0.0) {
      u = ulim;
      fu = (*func)(u);
    }
    else {
      u = *cx + GOLD*(*cx - *bx);
      fu = (*func)(u);
    }
    SHFT(*ax,*bx,*cx,u) ;
    SHFT(*fa,*fb,*fc,fu) ;
  }
}