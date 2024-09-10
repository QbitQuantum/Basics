int tester()
{
  using std::abs;

  int return_flag = 0;
  const Scalar tol = (std::numeric_limits<Scalar>::epsilon() * 10 < 5e-17)?5e-17:
                      std::numeric_limits<Scalar>::epsilon() * 10;

  const Scalar eps_kb = 97.53L; // N2 value
  const Scalar z_298 = 4.0L; // N2 value

  Antioch::RotationalRelaxation<Scalar> rot(z_298,eps_kb);

  for(Scalar T = 300.1; T <= 2500.1; T += 10.)
  {
     Scalar z = rot(T);
     Scalar z_exact = Z(T,eps_kb,z_298);

    if( abs( (z - z_exact)/z_exact) > tol )
      {
          std::cout << std::scientific << std::setprecision(16)
                    << "Error: Mismatch in rotational relaxation values." << std::endl
                    << " T = " << T << std::endl
                    << " z = " << z << std::endl
                    << " z_exact = " << z_exact << std::endl
                    << " relative error = " << std::abs(z - z_exact)/z_exact << std::endl
                    << " tolerance = " << tol << std::endl;

          return_flag = 1;
     }
  }

  return return_flag;
}