int FindMissingNum ( char *str, int len ) {
  
  int i = 0;
  int n = 0;
  int j = 0;
  int o = 0;
  int missingNo = -1;
  for ( i = 1; i <= 6; i++ ) {
    n = GetVal(str,0,i);
    printf("-%d",n); getchar();
    for ( j = i; j < len; j += 1 + i ) {
      o = GetVal(str,j,1+log10l(n+1));
      printf("+%d",o); getchar();
    }
  }
  return missingNo;

}