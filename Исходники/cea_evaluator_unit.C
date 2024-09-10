int test_h( const std::string& species_name, unsigned int species, Scalar h_exact, Scalar T,
            const Antioch::CEAEvaluator<Scalar>& thermo )
{
  using std::abs;

  int return_flag = 0;

  const Scalar tol = std::numeric_limits<Scalar>::epsilon() * 5;

  typedef typename Antioch::template TempCache<Scalar> Cache;

  const Scalar h = thermo.h(Cache(T), species);

  if( abs( (h_exact - h)/h_exact ) > tol )
    {
      std::cerr << std::scientific << std::setprecision(16)
                << "Error: Mismatch in species total enthalpy."
		<< "\nspecies    = " << species_name
		<< "\nh          = " << h
		<< "\nh_exact    = " << h_exact
		<< "\ndifference = " << (h_exact - h)
		<< "\ntolerance  = " << tol
		<< "\nT = " << T << std::endl;
      return_flag = 1;
    }

  return return_flag;
}