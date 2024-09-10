void SixJSymbol (double l2, double l3, double l4, 
                 double l5, double l6, double &l1min, double &l1max, 
                 double *sixcof, int ndim, int &errflag)
{
  const double zero = 0.0, eps = 0.01, one = 1.0, two = 2.0, three = 3.0;

  int nfin, nlim, i, n, index, lstep, nfinp1, nfinp2, nfinp3, nstep2;
  double c1old = 0.0, sign1, sign2, x, y, denom = 0.0, cnorm, ratio, 
         a1, a2, c1, c2, l1, x1, x2, x3, y1, y2, y3, oldfac, dv, newfac, 
         sumbac = 0.0, thresh, a1s, a2s, sumfor, sumuni, sum1, sum2;

  // Parameter adjustments 
  --sixcof;

  errflag = 0;
  
  // "hugedouble" is the square root of one twentieth of the largest floating 
  // point number, approximately. 
  double hugedouble   = sqrt(DBL_MAX / 20.0),
         srhuge = sqrt(hugedouble),
         tiny   = one / hugedouble,
         srtiny = one / srhuge;

  // lmatch = zero 

  // Check error conditions 1, 2, and 3. 
  if (fmod(l2+l3+l5+l6+eps,one) >= eps + eps 
      || fmod(l4+l2+l6+eps, one) >= eps + eps) {
    errflag = 1;
    Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                  "l2+l3+l5+l6 or l4+l2+l6 not integer.");
    return;
  } else if (l4+l2-l6 < zero || l4-l2+l6 < zero || -l4+l2+l6 < zero) {
    errflag = 2;
    Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                  "L4, L2, L6 triangular condition not satisfied.");
    return;
  } else if (l4-l5+l3 < zero || l4+l5-l3 < zero || -l4+l5+l3 < zero) {
    errflag = 3;
    Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                  "L4, L5, L3 triangular condition not satisfied.");
    return;
  }

  // Limits for l1 
  l1min = MpMax(fabs(l2-l3),fabs(l5-l6));
  l1max = MpMin(l2+l3,l5+l6);

  // Check error condition 4. 
  if (fmod(l1max-l1min+eps,one) >= eps + eps) {
    errflag = 4;
    Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                  "l1max-l1min not integer.");
    return;
  }
  if (l1min < l1max - eps) goto L20;
  if (l1min < l1max + eps) goto L10;

  // Check error condition 5. 
  errflag = 5;
  Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                "l1min greater than l1max.");
  return;

  // This is reached in case that l1 can take only one value 

L10:
  // lscale = 0 
  sixcof[1] = (odd(int(l2+l3+l5+l6+eps)) ? -one : one)
                 / sqrt((l1min+l1min+one)*(l4+l4+one));
  return;

  // This is reached in case that l1 can take more than one value. 

L20:
  // lscale = 0 
  nfin = int(l1max-l1min+one+eps);
  if (ndim - nfin >= 0) goto L23;

  // Check error condition 6. 
  errflag = 6;
  Matpack.Error(Mat::ArgumentDomain, "%s: %s", "SixJSymbol",
                "Dimension of result array for 6j coefficients too small.");
  return;

  // Start of forward recursion 

L23:
  l1 = l1min;
  newfac = 0.0;
  c1 = 0.0;
  sixcof[1] = srtiny;
  sum1 = (l1 + l1 + one) * tiny;

  lstep = 1;
L30:
  ++lstep;
  l1 += one;

  oldfac = newfac;
  a1 = (l1+l2+l3+one) * (l1-l2+l3) * (l1+l2-l3) * (-l1+l2+l3+one);
  a2 = (l1+l5+l6+one) * (l1-l5+l6) * (l1+l5-l6) * (-l1+l5+l6+one);
  newfac = sqrt(a1 * a2);

  if (l1 < one + eps) goto L40;

  dv = two * (l2 * (l2+one) * l5 * (l5+one) + l3 * (l3+one) * l6 * (l6+one) 
              - l1 * (l1-one) * l4 * (l4+one)) 
                        - (l2 * (l2+one) + l3 * (l3+one) - l1 * (l1-one)) 
                        * (l5 * (l5+one) + l6 * (l6+one) - l1 * (l1-one));

  denom = (l1-one) * newfac;

  if (lstep - 2 <= 0) goto L32;
  c1old = fabs(c1);

L32:
  c1 = -(l1+l1-one) * dv / denom;
  goto L50;

  // if l1 = 1, (l1 - 1) has to be factored out of dv, hence 

L40:
  c1 = -two * (l2 * (l2+one) + l5 * (l5+one) - l4 * (l4+one)) / newfac;

L50:
  if (lstep > 2) goto L60;

  // If l1 = l1min + 1, the third term in recursion equation vanishes 

  x = srtiny * c1;
  sixcof[2] = x;
  sum1 += tiny * (l1+l1+one) * c1 * c1;

  if (lstep == nfin) goto L220;
  goto L30;


L60:
  c2 = -l1 * oldfac / denom;

  // Recursion to the next 6j coefficient x 

  x = c1 * sixcof[lstep-1] + c2 * sixcof[lstep-2];
  sixcof[lstep] = x;

  sumfor = sum1;
  sum1 += (l1+l1+one) * x * x;
  if (lstep == nfin) goto L100;

  // See if last unnormalized 6j coefficient exceeds srhuge 

  if (fabs(x) < srhuge) goto L80;

  // This is reached if last 6j coefficient larger than srhuge, 
  // so that the recursion series sixcof(1), ... ,sixcof(lstep) 
  // has to be rescaled to prevent overflow 

  // lscale = lscale + 1 
  for (i = 1; i <= lstep; ++i) {
    if (fabs(sixcof[i]) < srtiny) sixcof[i] = zero;
    sixcof[i] /= srhuge;
  }
  sum1 /= hugedouble;
  sumfor /= hugedouble;
  x /= srhuge;

  // As long as the coefficient abs(c1) is decreasing, the recursion 
  // proceeds towards increasing 6j values and, hence, is numerically 
  // stable.  Once an increase of abs(c1) is detected, the recursion 
  // direction is reversed. 

L80:
  if (c1old - fabs(c1) <= 0.0) 
    goto L100;
  else
    goto L30;

  // Keep three 6j coefficients around lmatch for comparison later 
  // with backward recursion. 

L100:
  // lmatch = l1 - 1 
  x1 = x;
  x2 = sixcof[lstep-1];
  x3 = sixcof[lstep-2];

  // Starting backward recursion from l1max taking nstep2 steps, so 
  // that forward and backward recursion overlap at the three points 
  // l1 = lmatch+1, lmatch, lmatch-1. 

  nfinp1 = nfin + 1;
  nfinp2 = nfin + 2;
  nfinp3 = nfin + 3;
  nstep2 = nfin - lstep + 3;
  l1 = l1max;

  sixcof[nfin] = srtiny;
  sum2 = (l1 + l1 + one) * tiny;

  l1 += two;
  lstep = 1;
L110:
  ++lstep;
  l1 -= one;

  oldfac = newfac;
  a1s = (l1+l2+l3) * (l1-l2+l3-one) * (l1+l2-l3-one) * (-l1+l2+l3+two);
  a2s = (l1+l5+l6) * (l1-l5+l6-one) * (l1+l5-l6-one) * (-l1+l5+l6+two);
  newfac = sqrt(a1s * a2s);

  dv = two * (l2 * (l2+one) * l5 * (l5+one) + l3 * (l3+one) * l6 * (l6+one) 
              - l1 * (l1-one) * l4 * (l4+one)) 
                        - (l2 * (l2+one) + l3 * (l3+one) - l1 * (l1-one)) 
                        * (l5 * (l5+one) + l6 * (l6+one) - l1 * (l1-one));

  denom = l1 * newfac;
  c1 = -(l1+l1-one) * dv / denom;
  if (lstep > 2) goto L120;

  // If l1 = l1max + 1 the third term in the recursion equation vanishes 

  y = srtiny * c1;
  sixcof[nfin - 1] = y;
  if (lstep == nstep2) goto L200;
  sumbac = sum2;
  sum2 += (l1+l1-three) * c1 * c1 * tiny;
  goto L110;

L120:
  c2 = -(l1-one) * oldfac / denom;

  // Recursion to the next 6j coefficient y 

  y = c1 * sixcof[nfinp2 - lstep] + c2 * sixcof[nfinp3 - lstep];
  if (lstep == nstep2) goto L200;

  sixcof[nfinp1 - lstep] = y;
  sumbac = sum2;
  sum2 += (l1+l1-three) * y * y;

  // See if last unnormalized 6j coefficient exceeds srhuge 

  if (fabs(y) < srhuge) goto L110;

  // This is reached if last 6j coefficient larger than srhuge, 
  // so that the recursion series sixcof(nfin), ... ,sixcof(nfin-lstep+1) 
  // has to be rescaled to prevent overflow 

  // lscale = lscale + 1 
  for (i = 1; i <= lstep; ++i) {
    index = nfin - i + 1;
    if (fabs(sixcof[index]) < srtiny) sixcof[index] = zero;
    sixcof[index] /= srhuge;
  }
  sumbac /= hugedouble;
  sum2 /= hugedouble;

  goto L110;
  
  // The forward recursion 6j coefficients x1, x2, x3 are to be matched 
  // with the corresponding backward recursion values y1, y2, y3. 

L200:
  y3 = y;
  y2 = sixcof[nfinp2 - lstep];
  y1 = sixcof[nfinp3 - lstep];

  // Determine now ratio such that yi = ratio * xi  (i=1,2,3) holds 
  // with minimal error. 

  ratio = (x1*y1 + x2*y2 + x3*y3) / (x1*x1 + x2*x2 + x3*x3);
  nlim = nfin - nstep2 + 1;

  if (fabs(ratio) < one) goto L211;

  for (n = 1; n <= nlim; ++n) 
    sixcof[n] = ratio * sixcof[n];
  sumuni = ratio * ratio * sumfor + sumbac;
  goto L230;

L211:
  ++nlim;
  ratio = one / ratio;
  for (n = nlim; n <= nfin; ++n)
    sixcof[n] = ratio * sixcof[n];
  sumuni = sumfor + ratio * ratio * sumbac;
  goto L230;
  
L220:
  sumuni = sum1;

  // Normalize 6j coefficients 

L230:
  cnorm = one / sqrt((l4+l4+one) * sumuni);

  // Sign convention for last 6j coefficient determines overall phase 

  sign1 = CopySign(one,sixcof[nfin]);
  sign2 = odd(int(l2+l3+l5+l6+eps)) ? -one : one;
  if (sign1 * sign2 <= 0.0) goto L235;
  else  goto L236;

L235:
  cnorm = -cnorm;

L236:
  if (fabs(cnorm) < one) goto L250;

  for (n = 1; n <= nfin; ++n) 
    sixcof[n] = cnorm * sixcof[n];
  return;

L250:
  thresh = tiny / fabs(cnorm);
  for (n = 1; n <= nfin; ++n) {
    if (fabs(sixcof[n]) < thresh) sixcof[n] = zero;
    sixcof[n] = cnorm * sixcof[n];
  }
} 