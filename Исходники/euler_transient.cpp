Scalar MASA::euler_transient_1d<Scalar>::eval_exact_rho(Scalar x,Scalar t)
{
  using std::sin;

  Scalar exact_rho;
  exact_rho = rho_0 + rho_x * sin(a_rhox * pi * x / L) + rho_t * sin(a_rhot * pi * t / L);
  return exact_rho;
}