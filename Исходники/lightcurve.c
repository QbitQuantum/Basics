double lommel(int n, double mu, double nu)
{
  
  double val, x;
  int k, kmax;
  double eps = 1e-15;

  kmax = 100;

   val = 0.0;

  for(k=0; k<=kmax; k++){

    x = pow(-1.0, k)*pow(mu/nu, n + 2*k) * jn(n+2*k, PI*mu*nu);

    if(fabs(x) < eps){
      val += x;
      break;
    }else{
      val += x;
    }
  }

  return val;

}