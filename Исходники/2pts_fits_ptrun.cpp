//function to fit
double fun_fit(double Z2,double M,int t)
{
  if(parity==1) return Z2*exp(-M*TH)*cosh(M*(TH-t))/sinh(M);
  else return Z2*exp(-M*TH)*sin(M*(TH-t))/sinh(M);
}