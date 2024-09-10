void dtweedielogwsmallp(double *y, double *phi, double *power, double *logw) {
  double p,a,a1,r,drop=37,logz,jmax,j,cc,wmax,estlogw,oldestlogw;
  int hij,lowj;
  
  if (*power < 1) error("Error - power<1!");
  if (*power > 2) error("Error - power>2!");
  if (*phi <= 0) error("Error - phi<=0!");
  if (*y <= 0) error("Error - y<=0!");
  p = *power;
  a = (2 - p)/(1 - p);
  a1 = 1 - a;
  r = -a * log(*y) + a * log(p - 1) - a1 * log(*phi) - log(2 - p);
  logz = r;
  
  jmax = (pow(*y,(2 - p)))/(*phi * (2 - p));
  j = fmax2(1, jmax);
  cc = logz + a1 + a * log(-a);
  wmax = a1 * jmax;
  estlogw = wmax;
  while (estlogw > (wmax - drop)) {
    j = j + 2;
    estlogw = j * (cc - a1 * log(j));
  }
  
  hij = (int)ceil(j);
  logz = r;
  jmax = pow(*y,(2 - *power))/(*phi * (2 - *power));
  j = fmax2(1, jmax);
  wmax = a1 * jmax;
  estlogw = wmax;
  while ((estlogw > (wmax - drop)) && (j >= 2)) {
    j = fmax2(1, j - 2);
    oldestlogw = estlogw;
    estlogw = j * (cc - a1 * log(j));
  }
  lowj = (int)fmax2(1, floor(j));
  
  double newj[hij-lowj+1];
  int k;
  for(k=0;k<(hij-lowj+1);k++) newj[k] = lowj+k;
  
  double g[hij-lowj+1]; 
  for(k=0;k<hij-lowj+1;k++) g[k] = lgamma(newj[k]+1)+lgamma(-a*newj[k]);
  
  double A[hij-lowj+1];
  for(k=0;k<hij-lowj+1;k++) A[k] = r*(double)newj[k]-g[k];
  
  double m=fmax2(A[0],hij-lowj+1);
  for(k=0;k<(hij-lowj+1);k++) m = fmax2(A[k],hij-lowj+1);

  double we[hij-lowj+1];
  for(k=0;k<hij-lowj+1;k++) we[k] = exp(A[k]-m);
  double sumwe=0;
  for(k=0;k<hij-lowj+1;k++) sumwe+=we[k];
  *logw=log(sumwe)+m;
}