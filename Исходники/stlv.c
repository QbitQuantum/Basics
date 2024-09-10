void incr_facet(
  REAL n1, REAL n2, REAL n3,
  REAL i1, REAL i2, REAL i3,
  REAL j1, REAL j2, REAL j3,
  REAL k1, REAL k2, REAL k3){


  REAL x[3] = {i1-j1,i2-j2,i3-j3};
  REAL y[3] = {i1-k1,i2-k2,i3-k3};
  REAL zz[3]; CROSS(x,y,zz);
  REAL A = sqrt(NORM2(zz))/2;
  REAL incr = 1./3. * (i1*n1+i2*n2+i3*n3)*A;

//  REAL incr = (-1*k1*j2*i3 + j1*k2*i3 + k1*i2*j3 - i1*k2*j3 - j1*i2*k3 + i1*j2*k3)/6.;

  vol+=incr;
}