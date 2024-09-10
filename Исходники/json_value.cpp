static bool IsIntegral(double d) {
  double integral_part;
  return modf(d, &integral_part) == 0.0;
}