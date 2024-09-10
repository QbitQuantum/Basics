int test_values(const Scalar & Cf, const Scalar & eta, const Scalar & Ea, const Scalar & D, const Scalar & Tref, const Scalar & R, const Antioch::KineticsType<Scalar> & rate_base)
{
  using std::abs;
  using std::exp;
  using std::pow;

  int return_flag = 0;

  const Scalar tol = std::numeric_limits<Scalar>::epsilon() * 100;

  for(Scalar T = 300.1L; T <= 2500.1L; T += 10.L)
  {

    const Scalar rate_exact = Cf*pow(T/Tref,eta)*exp(-Ea/(R*T) + D * T);
    const Scalar derive_exact = exp(-Ea/(R*T) + D * T) * pow(T/Tref,eta) * Cf * (Ea/(R*T*T) + eta/T + D );

    Antioch::KineticsConditions<Scalar> cond(T);

    Scalar rate1 = rate_base(cond);
    Scalar deriveRate1 = rate_base.derivative(cond);
    Scalar rate;
    Scalar deriveRate;

    rate_base.compute_rate_and_derivative(cond,rate,deriveRate);

    if( abs( (rate1 - rate_exact)/rate_exact ) > tol )
      {
          std::cerr << std::scientific << std::setprecision(16)
                    << "Error: Mismatch in rate values." << std::endl
                    << "T = " << T << " K" << std::endl
                    << "rate(T) = " << rate1 << std::endl
                    << "rate_exact = " << rate_exact << std::endl
                    << "relative difference = " << abs( (rate1 - rate_exact)/rate_exact ) << std::endl
                    << "tolerance = " << tol << std::endl
                    << "on rate " << rate_base << std::endl << std::endl;

          return_flag = 1;
      }
    if( abs( (rate - rate_exact)/rate_exact ) > tol )
      {
          std::cerr << std::scientific << std::setprecision(16)
                    << "Error: Mismatch in rate values." << std::endl
                    << "T = " << T << " K" << std::endl
                    << "rate(T) = " << rate << std::endl
                    << "rate_exact = " << rate_exact << std::endl
                    << "relative difference = " << abs( (rate - rate_exact)/rate_exact ) << std::endl
                    << "tolerance = " << tol << std::endl
                    << "on rate " << rate_base << std::endl << std::endl;

          return_flag = 1;
      }
    if( abs( (deriveRate1 - derive_exact)/derive_exact ) > tol )
      {
          std::cerr << std::scientific << std::setprecision(16)
                    << "Error: Mismatch in rate derivative values." << std::endl
                    << "T = " << T << " K" << std::endl
                    << "drate_dT(T) = " << deriveRate1 << std::endl
                    << "derive_exact = " << derive_exact << std::endl
                    << "relative difference = " << abs( (deriveRate1 - derive_exact)/derive_exact ) << std::endl
                    << "tolerance = " << tol << std::endl
                    << "on rate " << rate_base << std::endl << std::endl;

          return_flag = 1;
     }
    if( abs( (deriveRate - derive_exact)/derive_exact ) > tol )
      {
          std::cerr << std::scientific << std::setprecision(16)
                    << "Error: Mismatch in rate derivative values." << std::endl
                    << "T = " << T << " K" << std::endl
                    << "drate_dT(T) = " << deriveRate << std::endl
                    << "derive_exact = " << derive_exact << std::endl
                    << "relative difference = " << abs( (deriveRate - derive_exact)/derive_exact ) << std::endl
                    << "tolerance = " << tol << std::endl
                    << "on rate " << rate_base << std::endl << std::endl;

          return_flag = 1;
     }

     if(return_flag)break;
  }
  return return_flag;
}