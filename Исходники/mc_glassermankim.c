//------------------------Sampling the transition probability (v(0)=X_t, v(1)=int_0^t X_s ds) 
//-------------------------dX_t = kappa(theta-X_t)dt + sigma sqrt(X_t)dW_t
//-------------------------------------In the case of the troncation serie
static void Sample_C(  PnlVect* v,double t, double kappa, double sigma, double theta ,int generator)
{
  //----------Declaration of variable
  double gamma, lambda;
  double tmp;
  double tmp2;
  int j,pss;
  int order_tr; // Default value is equal to 20
  //----------Initialization of parammter
  tmp=0.;
  j=0;
  gamma = 4.*kappa/(sigma*sigma*(1.-exp(-kappa*t)));
  lambda = pnl_vect_get(v,0)*gamma*exp(-kappa*t);
  order_tr = 20;
  //----------Begin operations
  //----generate vt --> tmp
  pss = pnl_rand_poisson(lambda*0.5,generator);
  
  for(j=1;j<= pss;j++)
    tmp = tmp + pnl_rand_gamma(1.,2., generator);
  
  tmp = tmp +pnl_rand_gamma(2.*kappa*theta/(sigma*sigma),2.,generator);
  tmp = tmp/gamma;
  //----generate the variable Z

  tmp2 =0.;
  j=0;
  pss = pnl_rand_bessel(2.*theta*kappa/(sigma*sigma)-1.,2.*kappa*sqrt(pnl_vect_get(v,0)*tmp)/(sigma*sigma*sinh(kappa*t*0.5)),generator);

  for(j=1;j<=pss;j++)
    {
      tmp2=tmp2+X_3_sample(  order_tr,  t,  kappa,  sigma,  generator);
    }
  //----generate int_0^t vs = X1 +X2 +X3 --> lambda

  lambda=tmp2+X_2_sample(  order_tr,  t,  kappa,  sigma,  theta ,  generator)+X_1_sample(  order_tr,  t,  kappa,  sigma,  pnl_vect_get(v,0),  tmp,  generator);
  
  //----set the new value 
  pnl_vect_set(v,0,tmp);
  pnl_vect_set(v,1,lambda);
}