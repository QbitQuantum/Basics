void MpFitLineMinAbsDev (const Vector& X, const Vector& Y, 
                         double& a, double& b, double& mean_abs_dev)
{
  // verify index range
  if ( ! (MatchingIndexRange(X,Y) )) {
    Matpack.Error(Mat::UnspecifiedError,"MpFitLineMinAbsDev: vector x,y index range mismatch");  
    return;
  }

  // shift index range to 1..n
  int lo = X.Lo(), hi = X.Hi(), n = hi-lo+1;
  const double *x = &X[lo-1],
               *y = &Y[lo-1];
    
  Vector h(1,n); // auxillary vector

  double b1,b2,f,f1,f2,absdev_sum;

  double sx = 0.0, sy = 0.0, sxy = 0.0, sxx = 0.0;
  int i;
  for (i = 1; i <= n; i++) {
    double xi = x[i],
           yi = y[i];
    sx  += xi;
    sxx += xi * xi;
    sy  += yi;
    sxy += xi * yi;
  }

  double nrm = n * sxx - sx * sx,
         aa  = (sxx * sy - sx * sxy) / nrm,
         bb  = (n * sxy - sx * sy) / nrm,
         chi2 = 0.0;

  for (i = 1; i <= n; i++) {
    double t = y[i] - (aa + bb * x[i]);
    chi2 += t * t;
  }
  double b_sdev = sqrt(chi2 / nrm);

  b1 = bb;
  f1 = MedianAux(h,x,y,b1,aa,absdev_sum);

  if (b_sdev > 0.0) {

    b2 = bb + CopySign(3*b_sdev,f1);
    f2 = MedianAux(h,x,y,b2,aa,absdev_sum);

    if (b2 != b1) {

      while (f1 * f2 > 0.0) {
        bb = b2 + 1.6 * (b2 - b1);
        b1 = b2;
        f1 = f2;
        b2 = bb;
        f2 = MedianAux(h,x,y,b2,aa,absdev_sum);
      } // while
      
      b_sdev *= 0.01;
      while (fabs(b2 - b1) > b_sdev) {
        // bisection to reduce error
        bb = b1 + 0.5 * (b2 - b1);
        if (bb == b1 || bb == b2) break;
        f = MedianAux(h,x,y,bb,aa,absdev_sum);
        if (f * f1 >= 0.0) {
          f1 = f;
          b1 = bb;
        } else {
          f2 = f;
          b2 = bb;
        }
      } // while

    } // b2 != b1

  } // b_sdev > 0.0

  // return values
  a = aa;
  b = bb;
  mean_abs_dev = absdev_sum / n;
}