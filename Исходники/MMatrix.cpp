int invertMatrix(Matrix m, int printErrors)
{
  int ok = 1;
  int i,icol=0,irow=0,j,k,l,ll;
  float big,dum,pivinv;
  
  int n=4;

  if (indxc==0) {
    indxr = new int[4];
    indxc = new int[4];
    ipiv  = new int[4];
    a     = new float*[4];
    if (!a || !ipiv) printf("new fails - memory problem\n");
  }
  for (j=0;j<n;j++) a[j] = &(m[j][0]);

  for (j=0;j<n;j++) ipiv[j]=0;
  for (i=0;i<n;i++) {
    big=0.0;
    for (j=0;j<n;j++)
      if (ipiv[j] != 1)
        for (k=0;k<n;k++) {
          if (ipiv[k] == 0) {
            if (fabs(a[j][k]) >= big) {
              big=ABS(a[j][k]);
              irow=j;
              icol=k;
            }
          } else if (ipiv[k] > 1) {
          		if (printErrors) printf("GAUSSJ: Singular Matrix-1\n");
          		ok =0;
          	}
        }
    ++(ipiv[icol]);
    if (irow != icol) {
      for (l=0;l<n;l++) SWAP(a[irow][l],a[icol][l])
    }
    indxr[i]=irow;
    indxc[i]=icol;
    if (a[icol][icol] == 0.0) {
    	ok =0;
    	if (printErrors) printf("GAUSSJ: Singular Matrix-2");
    }
    pivinv=1.0f/a[icol][icol];
    a[icol][icol]=1.0;
    for (l=0;l<n;l++) a[icol][l] *= pivinv;
    for (ll=0;ll<n;ll++)
      if (ll != icol) {
        dum=a[ll][icol];
        a[ll][icol]=0.0;
        for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
      }
  }
  for (l=n-1;l>=0;l--) {
    if (indxr[l] != indxc[l])
      for (k=0;k<n;k++)
        SWAP(a[k][indxr[l]],a[k][indxc[l]]);
  }
  return ok;
}