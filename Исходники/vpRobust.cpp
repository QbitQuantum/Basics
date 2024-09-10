double
vpRobust::simultscale(vpColVector &x)
{
  unsigned int p = 6; //Number of parameters to be estimated.
  unsigned int n = x.getRows();
  double sigma2=0;
  /* long */ double Expectation=0;
  /* long */ double Sum_chi=0;
  /* long */ double chiTmp =0;

  for(unsigned int i=0; i<n; i++)
  {

    chiTmp = simult_chi_huber(x[i]);
    Expectation += chiTmp*(1-erf(chiTmp));
    Sum_chi += chiTmp;

#ifdef VP_DEBUG
#if VP_DEBUG_MODE == 3
    {
      std::cout << "erf = " << 1-erf(chiTmp) << std::endl;
      std::cout << "x[i] = " << x[i] <<std::endl;
      std::cout << "chi = " << chiTmp << std::endl;
      std::cout << "Sum chi = " << chiTmp*vpMath::sqr(sig_prev) << std::endl;
      std::cout << "Expectation = " << chiTmp*(1-erf(chiTmp)) << std::endl;
      //getchar();
    }
#endif
#endif
  }


  sigma2 = Sum_chi*vpMath::sqr(sig_prev)/((n-p)*Expectation);

#ifdef VP_DEBUG
#if VP_DEBUG_MODE == 3
  {
    std::cout << "Expectation = " << Expectation << std::endl;
    std::cout << "Sum chi = " << Sum_chi << std::endl;
    std::cout << "sig_prev" << sig_prev << std::endl;
    std::cout << "sig_out" << sqrt(fabs(sigma2)) << std::endl;
  }
#endif
#endif

  return sqrt(fabs(sigma2));

}