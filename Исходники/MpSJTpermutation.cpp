void MpSJTpermutation (int n, int *a, bool &next, bool &even)
{
  if (next) goto CONTINUE;

  // initialize array
  int j;
  for (j = 0; j < n; ++j) a[j] = j+1;
  next = even = true;
  
  if (n == 1) {
    next = false;
    return;
  }
  
 EVEN:

  if (a[n-1] != 1 || a[0] != n % 2 + 2) return;

  if (n > 3) {
    int nm3 = n-3;
    for (int j = 1; j <= nm3; ++j)
      if (a[j] != a[j-1]+1) return;
  }

  next = false;
  return;
  
 CONTINUE:

  if (n == 1) {
    a[0] = 0;
    next = false;
    return;
  }
  
  if (even) {

    int a0 = a[0];
    a[0] = a[1];
    a[1] = a0;
    even = false;
    goto EVEN;

  } else {
  
    int s = 0;
    for (int i = 1; i < n; ++i) {
      int ai = a[i], d = 0, l = 0; // initialization of l is not necessary
      for (int j = 0; j < i; ++j)
        if (a[j] > ai) ++d;
      s += d;
      if (d != i * (s % 2)) {
        int m = (s + 1) % 2 * (n + 1);
        for (int j = 0; j < i; ++j) 
          if (CopySign(1,a[j]-ai) != CopySign(1,a[j]-m)) {
            m = a[j];
            l = j+1;
          }
        a[l-1] = ai;
        a[i] = m;
        even = true;
        return;
      }
    }
    
    a[0] = 0;
    next = false;
    return;
  }

}