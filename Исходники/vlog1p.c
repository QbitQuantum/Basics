void OpenVML_FUNCNAME_REF(vsLog1p)(const VML_INT n, const float * a, float * y){
  VML_INT i;
  if (n<=0) return;
  if (a==NULL || y==NULL) return;

  for(i=0; i<n; i++){
    y[i]=log1pf(a[i]);
  }
}