double evaluate_q (const NumberArray<NDIM, ADScalar>& xyz, const int ret)
{
  typedef typename RawType<ADScalar>::value_type Scalar;

  const Scalar PI = std::acos(Scalar(-1));

  const Scalar R = masa_get_param("R");
  const Scalar u_0 = masa_get_param("u_0");
  const Scalar u_x = masa_get_param("u_x");
  const Scalar u_y = masa_get_param("u_y");
  const Scalar v_0 = masa_get_param("v_0");
  const Scalar v_x = masa_get_param("v_x");
  const Scalar v_y = masa_get_param("v_y");
  const Scalar rho_0 = masa_get_param("rho_0");
  const Scalar rho_x = masa_get_param("rho_x");
  const Scalar rho_y = masa_get_param("rho_y");
  const Scalar p_0 = masa_get_param("p_0");
  const Scalar p_x = masa_get_param("p_x");
  const Scalar p_y = masa_get_param("p_y");
  const Scalar a_px = masa_get_param("a_px");
  const Scalar a_py = masa_get_param("a_py");
  const Scalar a_rhox = masa_get_param("a_rhox");
  const Scalar a_rhoy = masa_get_param("a_rhoy");
  const Scalar a_ux = masa_get_param("a_ux");
  const Scalar a_uy = masa_get_param("a_uy");
  const Scalar a_vx = masa_get_param("a_vx");
  const Scalar a_vy = masa_get_param("a_vy");
  const Scalar Gamma = masa_get_param("Gamma");
  const Scalar L = masa_get_param("L");
  const Scalar mu = masa_get_param("mu");
  const Scalar k = masa_get_param("k");

  const ADScalar& x = xyz[0];
  const ADScalar& y = xyz[1];

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * std::cos(a_ux * PI * x / L) * u_y * std::cos(a_uy * PI * y / L);
  U[1] = v_0 + v_x * std::cos(a_vx * PI * x / L) * v_y * std::cos(a_vy * PI * y / L);
  ADScalar RHO = rho_0 + rho_x * std::cos(a_rhox * PI * x / L) * rho_y * std::cos(a_rhoy * PI * y / L);
  ADScalar P = p_0 + p_x * std::cos(a_px * PI * x / L) * p_y * std::cos(a_py * PI * y / L);

  // Temperature
  ADScalar T = P / RHO / R;

  // Perfect gas energies
  ADScalar E = 1./(Gamma-1.)*P/RHO;
  ADScalar ET = E + .5 * U.dot(U);

  // The shear strain tensor
  NumberArray<NDIM, typename ADScalar::derivatives_type> GradU = gradient(U);

  // The identity tensor I
  NumberArray<NDIM, NumberArray<NDIM, Scalar> > Identity = 
    NumberArray<NDIM, Scalar>::identity();

  // The shear stress tensor
  NumberArray<NDIM, NumberArray<NDIM, ADScalar> > Tau = mu * (GradU + transpose(GradU) - 2./3.*divergence(U)*Identity);

  // Temperature flux
  NumberArray<NDIM, ADScalar> q = -k * T.derivatives();

  // Euler equation residuals
  Scalar Q_rho = raw_value(divergence(RHO*U));
  NumberArray<NDIM, Scalar> Q_rho_u = 
    raw_value(divergence(RHO*U.outerproduct(U) - Tau) + P.derivatives());

  // energy equation
  Scalar Q_rho_e = raw_value(divergence((RHO*ET+P)*U + q - Tau.dot(U)));

  switch(ret)
    {

      // u
    case 1: 
      return Q_rho_u[0];
      break;

      // v
    case 2:
      return Q_rho_u[1];
      break;

      // rho
    case 3:
      return Q_rho;
      break;

      // energy
    case 4:
      return Q_rho_e;
      break;

    default:
      std::cout << "something is wrong!\n";
      exit(1);
    }
}