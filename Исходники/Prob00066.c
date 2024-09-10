long double
FindXYgivenD (long double D) {

  long double maxx = 0;
  long double miny = 0;

  long double y;
  for ( y = 1 ; y < D; y++) {
    long double x = Diophanite(D, y);
    //if ((x < (x+.001)) && (x> (x-.001))) {
    if (floorl(x) == x) {
      if (maxx < x) {
        maxx = x;
        miny = y;
      }

    } //if
  } // for

  if (maxx == 0) 
    printf("None found for D= %0.0Lf\n", D);
  else
    printf("%0.0Lf^2 - %0.0Lf * %0.0Lf^2 = 1\n", maxx, D, miny);
  return maxx;
} // FindXYgivenD