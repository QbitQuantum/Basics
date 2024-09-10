void incomkin(double m1, double m2, double p1, double p2, 
           double *sqrt_S_,  double *Pcm_, double * rapidity_)
{
  double sqrt_S, Pcm,rapidity;
  double e1=sqrt(m1*m1+p1*p1);
  double e2=sqrt(m2*m2+p2*p2);
   
  sqrt_S=(e1+e2)*(e1+e2)-(p1-p2)*(p1-p2);
  
  rapidity= atanh((p1-p2)/(e1+e2));

  Pcm=p1*cosh(rapidity)-e1*sinh(rapidity);

  if(sqrt_S_) *sqrt_S_=sqrt(sqrt_S);
  if(Pcm_) *Pcm_=Pcm; 
  if(rapidity_) *rapidity_=rapidity;
}