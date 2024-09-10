     FLOAT *f, FLOAT *dfdx, FLOAT *ldfdx, FLOAT *d2fdx2)
{
  static const FLOAT ad = 1e-8, a4 = 29.790, a6 = 22.417;
  static const FLOAT a8 = 12.119, a10 = 1570.1, a12 = 55.944;
  static const FLOAT a2 = 4.94113918475214219939; /* (ad + 0.1234)/b, b = 0.024974 */
  static const FLOAT b  = 0.024974;

  FLOAT ss, ss2, ss4, ss6, ss8, ss10;
  FLOAT f0, f1, f2, df0, df1, df2, d2f0, d2f1, d2f2;

  ss  = X2S*x;    ss2  = ss*ss;
  ss4 = ss2*ss2;  ss6  = ss4*ss2;
  ss8 = ss6*ss2;  ss10 = ss8*ss2;

  f0 = 1.0 + a2*ss2 + a4*ss4 + a6*ss6 + a8*ss8 + a10*ss10 + a12*ss2*ss10;
  f1 = POW(f0, b);
  f2 = 1.0 + ad*ss2;

  *f = f1/f2;

  if(order < 1) return;

  df0 = ss*(2.0*a2 + 4.0*a4*ss2 + 6.0*a6*ss4 + 8.0*a8*ss6 + 10.0*a10*ss8 + 12.0*a12*ss10);
  df1 = b*df0*POW(f0, b-1.0);
  df2 = 2.0*ss*ad;

  *dfdx  = X2S*(df1*f2 - f1*df2)/(f2*f2);
  *ldfdx = X2S*X2S*(a2 - ad);

  if(order < 2) return;
  