static void Test_alpha_epsilon(void) {
  printf("\n** Test_alpha_epsilon: **\n");
  const REAL8 f = 0.01;
  const REAL8 q = 4;
  const REAL8 chil = 0.5625;
  const REAL8 chip = 0.18;

  NNLOanglecoeffs angcoeffs;
  ComputeNNLOanglecoeffs(&angcoeffs,q,chil,chip);

  const REAL8 omega = LAL_PI * f;
  const REAL8 logomega = log(omega);
  const REAL8 omega_cbrt = cbrt(omega);
  const REAL8 omega_cbrt2 = omega_cbrt*omega_cbrt;
  const REAL8 alpha = (angcoeffs.alphacoeff1/omega
                    + angcoeffs.alphacoeff2/omega_cbrt2
                    + angcoeffs.alphacoeff3/omega_cbrt
                    + angcoeffs.alphacoeff4*logomega
                    + angcoeffs.alphacoeff5*omega_cbrt);

  const REAL8 epsilon = (angcoeffs.epsiloncoeff1/omega
                      + angcoeffs.epsiloncoeff2/omega_cbrt2
                      + angcoeffs.epsiloncoeff3/omega_cbrt
                      + angcoeffs.epsiloncoeff4*logomega
                      + angcoeffs.epsiloncoeff5*omega_cbrt);

  const REAL8 alpha_expected = -11.8196;
  const REAL8 epsilon_expected = -11.936;

  print_difference("alpha", alpha, alpha_expected);
  print_difference("epsilon", epsilon, epsilon_expected);

  const REAL8 eps = 1e-5;

  assert(
       approximatelyEqual(alpha,    alpha_expected,   eps)
    && approximatelyEqual(epsilon,  epsilon_expected, eps)
    && "Test_alpha_epsilon()"
  );
}