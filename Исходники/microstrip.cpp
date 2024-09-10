/*
 * delta_Z0_cover() - compute the cover effect on impedance for a
 * stripline in a homogeneous medium
 */
double microstrip::delta_Z0_cover(double u, double h2h)
{
  double P, Q;
  double h2hp1;
  h2hp1 = 1.0 + h2h;
  P = 270.0 * (1.0 - tanh(1.192 + 0.706 * sqrt(h2hp1) - 1.389 / h2hp1));
  Q = 1.0109 - atanh((0.012 * u + 0.177 * u * u - 0.027 * u * u * u) / (h2hp1 * h2hp1));
  return (P * Q);
}