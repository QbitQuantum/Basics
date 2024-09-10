/**
 * @function beta
 */
double beta( double z,double w) {
  double gz, gw, gzw;
  
  gz = tgamma(z);
  gw = tgamma(w);
  gzw = tgamma(z+w);
  return  gz*gw/gzw;
}