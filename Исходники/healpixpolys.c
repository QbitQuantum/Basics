long double cmrpirpj(vec rpi, vec rpj)
{
  long double cmij;
  
  cmij = (powl((rpi[0]-rpj[0]),2)+powl((rpi[1]-rpj[1]),2)+powl((rpi[2]-rpj[2]),2))/2.;
  return(cmij);
}