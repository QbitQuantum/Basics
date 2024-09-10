int test_cv_vib()
{
  using std::exp;

  const Scalar Mm_N  = 14.008e-3;   //in SI kg/mol
  const Scalar Mm_O  = 16e-3;       //in SI kg/mol
  const Scalar Mm_N2 = 2.L * Mm_N;  //in SI kg/mol
  const Scalar Mm_O2 = 2.L * Mm_O;  //in SI kg/mol
  const Scalar Mm_NO = Mm_O + Mm_N; //in SI kg/mol

  std::vector<std::string> species_str_list;
  const unsigned int n_species = 5;
  species_str_list.reserve(n_species);
  species_str_list.push_back( "N2" );
  species_str_list.push_back( "O2" );
  species_str_list.push_back( "N" );
  species_str_list.push_back( "O" );
  species_str_list.push_back( "NO" );

  Antioch::ChemicalMixture<Scalar> chem_mixture( species_str_list );

  // Can we instantiate it?
  Antioch::StatMechThermodynamics<Scalar> sm_thermo( chem_mixture );

  // Mass fractions
  std::vector<Scalar> mass_fractions( 5, 0.2 );
  mass_fractions[0] = 0.5;
  mass_fractions[1] = 0.2;
  mass_fractions[2] = 0.1;
  mass_fractions[3] = 0.1;
  mass_fractions[4] = 0.1;

  const Scalar R_N2 = Antioch::Constants::R_universal<Scalar>() / Mm_N2;
  const Scalar R_O2 = Antioch::Constants::R_universal<Scalar>() / Mm_O2;
  const Scalar R_NO = Antioch::Constants::R_universal<Scalar>() / Mm_NO;

  const Scalar th0_N2 = 3.39500e+03; // degeneracy = 1
  const Scalar th0_O2 = 2.23900e+03; // degeneracy = 1
  const Scalar th0_NO = 2.81700e+03; // degeneracy = 1

  // Tv
  const Scalar Tv = 1000.0;

  const Scalar tol = std::numeric_limits<Scalar>::epsilon() * 2;
  const Scalar ztol = std::numeric_limits<Scalar>::epsilon();

  int return_flag = 0;

  Scalar cv_vib_mix = 0.0;

  // N2
  {
    Scalar cv_vib_N2 = sm_thermo.cv_vib (0, Tv);

    const Scalar expv   = exp(th0_N2/Tv);
    const Scalar expvmi = expv - Scalar(1.0);
    Scalar cv_vib_N2_true = R_N2*th0_N2*th0_N2*expv/expvmi/expvmi/Tv/Tv;

    if( !test_relative(cv_vib_N2, cv_vib_N2_true, tol) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in cv_vib for N2."
                << "\n Expected = " << cv_vib_N2_true
                << "\n Computed = " << cv_vib_N2
                << "\n Diff     = " << cv_vib_N2_true - cv_vib_N2
                << std::endl;
      return_flag += 1;
    }

    cv_vib_mix += mass_fractions[0]*cv_vib_N2_true;
  }

  // O2
  {
    Scalar cv_vib_O2 = sm_thermo.cv_vib (1, Tv);

    const Scalar expv   = exp(th0_O2/Tv);
    const Scalar expvmi = expv - Scalar(1.0);
    Scalar cv_vib_O2_true = R_O2*th0_O2*th0_O2*expv/expvmi/expvmi/Tv/Tv;

    if( !test_relative(cv_vib_O2, cv_vib_O2_true, tol) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in cv_vib for O2."
                << "\n Expected = " << cv_vib_O2_true
                << "\n Computed = " << cv_vib_O2
                << "\n Diff     = " << cv_vib_O2_true - cv_vib_O2
                << std::endl;
      return_flag += 1;
    }

    cv_vib_mix += mass_fractions[1]*cv_vib_O2_true;
  }

  // O
  {
    Scalar cv_vib_O = sm_thermo.cv_vib (2, Tv);

    if( !test_zero(cv_vib_O, ztol) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in cv_vib for O."
                << "\n Expected = " << Scalar(0.0)
                << "\n Computed = " << cv_vib_O
                << "\n Diff     = " << cv_vib_O
                << std::endl;
      return_flag += 1;
    }

    // cv_vib_mix += 0.0;
  }

  // N
  {
    Scalar cv_vib_N = sm_thermo.cv_vib (3, Tv);

    if( !test_zero(cv_vib_N, ztol) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in cv_vib for N."
                << "\n Expected = " << Scalar(0.0)
                << "\n Computed = " << cv_vib_N
                << "\n Diff     = " << cv_vib_N
                << std::endl;
      return_flag += 1;
    }

    // cv_vib_mix += 0.0;
  }

  // NO
  {
    Scalar cv_vib_NO = sm_thermo.cv_vib (4, Tv);

    const Scalar expv   = exp(th0_NO/Tv);
    const Scalar expvmi = expv - Scalar(1.0);
    Scalar cv_vib_NO_true = R_NO*th0_NO*th0_NO*expv/expvmi/expvmi/Tv/Tv;

    if( !test_relative(cv_vib_NO, cv_vib_NO_true, tol*4) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in cv_vib for NO."
                << "\n Expected = " << cv_vib_NO_true
                << "\n Computed = " << cv_vib_NO
                << "\n Diff     = " << cv_vib_NO_true - cv_vib_NO
                << std::endl;
      return_flag += 1;
    }

    cv_vib_mix += mass_fractions[4]*cv_vib_NO_true;
  }

  // mixture
  {
    Scalar cv = sm_thermo.cv_vib(Tv, mass_fractions);
    
    if( !test_relative(cv, cv_vib_mix, tol) )
    {
      std::cerr << std::scientific << std::setprecision(20);
      std::cerr << "Error: Mismatch in mixture cv_vib."
                << "\n Expected = " << cv_vib_mix
                << "\n Computed = " << cv
                << "\n Diff     = " << cv - cv_vib_mix
                << std::endl;
      return_flag += 1;
    }
  }

  return return_flag;
}