int vectester(const PairScalars& example)
{
  using std::abs;
  using std::exp;

  typedef typename Antioch::value_type<PairScalars>::type Scalar;

  const Scalar Cf = 1.4;
  const Scalar D = -2.5;

  Antioch::BerthelotRate<Scalar> berthelot_rate(Cf,D);

  // Construct from example to avoid resizing issues
  PairScalars T = example;
  T[0] = 1500.1;
  T[1] = 1600.1;
  
  const Scalar rate_exact0 = Cf*exp(D*1500.1);
  const Scalar rate_exact1 = Cf*exp(D*1600.1);
  const Scalar derive_exact0 = D * Cf * exp(D*Scalar(1500.1));
  const Scalar derive_exact1 = D * Cf * exp(D*Scalar(1600.1));

  int return_flag = 0;

  const PairScalars rate = berthelot_rate(T);
  const PairScalars deriveRate = berthelot_rate.derivative(T);

  const Scalar tol = std::numeric_limits<Scalar>::epsilon()*10;

  if( abs( (rate[0] - rate_exact0)/rate_exact0 ) > tol )
    {
      std::cout << "Error: Mismatch in rate values." << std::endl
		<< "rate(T0)   = " << rate[0] << std::endl
		<< "rate_exact = " << rate_exact0 << std::endl
		<< "difference = " << rate[0] - rate_exact0 << std::endl;

      return_flag = 1;
    }

  if( abs( (rate[1] - rate_exact1)/rate_exact1 ) > tol )
    {
      std::cout << "Error: Mismatch in rate values." << std::endl
		<< "rate(T1)   = " << rate[1] << std::endl
		<< "rate_exact = " << rate_exact1 << std::endl
		<< "difference = " << rate[1] - rate_exact1 << std::endl;

      return_flag = 1;
    }
  if( abs( (deriveRate[0] - derive_exact0)/derive_exact0 ) > tol )
    {
      std::cout << std::scientific << std::setprecision(16)
                << "Error: Mismatch in rate derivative values." << std::endl
		<< "drate_dT(T0) = " << deriveRate[0] << std::endl
		<< "derive_exact = " << derive_exact0 << std::endl;

      return_flag = 1;
    }
  if( abs( (deriveRate[1] - derive_exact1)/derive_exact1 ) > tol )
    {
      std::cout << std::scientific << std::setprecision(16)
                << "Error: Mismatch in rate derivative values." << std::endl
		<< "drate_dT(T1) = " << deriveRate[1] << std::endl
		<< "derive_exact = " << derive_exact1 << std::endl;

      return_flag = 1;
    }

  std::cout << "Berthelot rate: " << berthelot_rate << std::endl;

  return return_flag;
}