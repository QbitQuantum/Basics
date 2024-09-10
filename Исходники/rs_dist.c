static double mod2pi(double a)
{
  return((double)((a=fmod(a, M_2PI))>0.0)?a:(FEQ(a,0.0,EPSILON)?0.0:(a + M_2PI)));
}