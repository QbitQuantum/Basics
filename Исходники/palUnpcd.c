void palUnpcd( double disco, double * x, double *y ) {

  const double THIRD = 1.0/3.0;

  double rp,q,r,d,w,s,t,f,c,t3,f1,f2,f3,w1,w2,w3;
  double c2;

  /*  Distance of the point from the origin. */
  rp = sqrt( (*x)*(*x)+(*y)*(*y));

  /*  If zero, or if no distortion, no action is necessary. */
  if (rp != 0.0 && disco != 0.0) {

    /*     Begin algebraic solution. */
    q = 1.0/(3.0*disco);
    r = rp/(2.0*disco);
    w = q*q*q+r*r;

    /* Continue if one real root, or three of which only one is positive. */
    if (w > 0.0) {

      d = sqrt(w);
      w = r+d;
      s = COPYSIGN(pow(fabs(w),THIRD),w);
      w = r-d;
      t = COPYSIGN(pow(fabs(w),THIRD),w);
      f = s+t;

    } else {
      /* Three different real roots:  use geometrical method instead. */
      w = 2.0/sqrt(-3.0*disco);
      c = 4.0*rp/(disco*w*w*w);
      c2 = c*c;
      s = sqrt(1.0-DMIN(c2,1.0));
      t3 = atan2(s,c);

      /* The three solutions. */
      f1 = w*cos((PAL__D2PI-t3)/3.0);
      f2 = w*cos((t3)/3.0);
      f3 = w*cos((PAL__D2PI+t3)/3.0);

      /* Pick the one that moves [X,Y] least. */
      w1 = fabs(f1-rp);
      w2 = fabs(f2-rp);
      w3 = fabs(f3-rp);
      if (w1 < w2) {
        f = ( w1 < w3 ? f1 : f3 );
      } else {
        f = ( w2 < w3 ? f2 : f3 );
      }
    }

    /* Remove the distortion. */
    f = f/rp;
    *x *= f;
    *y *= f;
  }
}