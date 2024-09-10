std::set<Argument> SolveQuadraticEquation(
    Argument const& origin,
    Value const& a0,
    Derivative<Value, Argument> const& a1,
    Derivative<Derivative<Value, Argument>, Argument> const& a2) {
  using Derivative1 = Derivative<Value, Argument>;
  using Discriminant = Square<Derivative1>;

  std::set<Argument> solutions;

  // This algorithm is after section 1.8 of Accuracy and Stability of Numerical
  // Algorithms, Second Edition, Higham, ISBN 0-89871-521-0.

  static Discriminant const discriminant_zero{};

  // Use compensated summation for the discriminant because there can be
  // cancellations.
  DoublePrecision<Discriminant> discriminant(a1 * a1);
  discriminant.Increment(-4.0 * a0 * a2);

  if (discriminant.value == discriminant_zero &&
      discriminant.error == discriminant_zero) {
    // One solution.
    solutions.insert(origin - 0.5 * a1 / a2);
  } else if (discriminant.value < discriminant_zero ||
             (discriminant.value == discriminant_zero &&
              discriminant.error < discriminant_zero)) {
    // No solution.
  } else {
    // Two solutions.  Compute the numerator of the larger one.
    Derivative1 numerator;
    static Derivative1 derivative_zero{};
    if (a1 > derivative_zero) {
      numerator = -a1 - Sqrt(discriminant.value + discriminant.error);
    } else {
      numerator = -a1 + Sqrt(discriminant.value + discriminant.error);
    }
    solutions.insert(origin + numerator / (2.0 * a2));
    solutions.insert(origin + (2.0 * a0) / numerator);
  }
  return solutions;
}