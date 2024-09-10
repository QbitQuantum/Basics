static double trans_unif(double x , const arg_pack_type * arg) {
  double y;
  double min   = arg_pack_iget_double(arg , 0);
  double max   = arg_pack_iget_double(arg , 1);
  y = 0.5*(1 + erf(x/sqrt(2.0))); /* 0 - 1 */
  return y * (max - min) + min;
}