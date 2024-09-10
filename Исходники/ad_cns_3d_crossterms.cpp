Scalar MASA::ad_cns_3d_crossterms<Scalar>::eval_q_e(Scalar x1, Scalar y1, Scalar z1) const
{
  using std::cos;

  typedef DualNumber<Scalar, NumberArray<NDIM, Scalar> > FirstDerivType;
  typedef DualNumber<FirstDerivType, NumberArray<NDIM, FirstDerivType> > SecondDerivType;
  typedef SecondDerivType ADScalar;

  // Treat velocity as a vector
  NumberArray<NDIM, ADScalar> U;

  const ADScalar x = ADScalar(x1,NumberArrayUnitVector<NDIM, 0, Scalar>::value());
  const ADScalar y = ADScalar(y1,NumberArrayUnitVector<NDIM, 1, Scalar>::value());
  const ADScalar z = ADScalar(z1,NumberArrayUnitVector<NDIM, 2, Scalar>::value());

  // Arbitrary manufactured solution
  U[0] = u_0 + u_x * cos(a_ux * PI * x / L) * u_y * cos(a_uy * PI * y / L) * cos(a_uy * PI * z / L);
  U[1] = v_0 + v_x * cos(a_vx * PI * x / L) * v_y * cos(a_vy * PI * y / L) * cos(a_vy * PI * z / L);
  U[2] = w_0 + w_x * cos(a_wx * PI * x / L) * w_y * cos(a_wy * PI * y / L) * cos(a_wy * PI * z / L);
  ADScalar RHO = rho_0 + rho_x * cos(a_rhox * PI * x / L) * rho_y * cos(a_rhoy * PI * y / L) * cos(a_rhoz * PI * z / L);
  ADScalar P = p_0 + p_x * cos(a_px * PI * x / L) * p_y * cos(a_py * PI * y / L) * cos(a_pz * PI * z / L);

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
  // Scalar Q_rho = raw_value(divergence(RHO*U));
  // NumberArray<NDIM, Scalar> Q_rho_u = 
  //   raw_value(divergence(RHO*U.outerproduct(U) - Tau) + P.derivatives());

  // energy equation
  Scalar Q_rho_e = raw_value(divergence((RHO*ET+P)*U + q - Tau.dot(U)));

  return Q_rho_e;
}