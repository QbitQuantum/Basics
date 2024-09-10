double PleC::uniRandNum(){

  double r1; 
  do{r1=1.0*rand()/RAND_MAX;}while(r1<=0 || r1>=1);

  return r1;
}