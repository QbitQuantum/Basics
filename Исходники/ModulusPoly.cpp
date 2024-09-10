public String toString() {
  StringBuilder result = new StringBuilder(8 * getDegree());
  for (int degree = getDegree(); degree >= 0; degree--) {
    int coefficient = getCoefficient(degree);
    if (coefficient != 0) {
      if (coefficient < 0) {
        result.append(" - ");
        coefficient = -coefficient;
      } else {
        if (result.length() > 0) {
          result.append(" + ");
        }
      }
      if (degree == 0 || coefficient != 1) {
        result.append(coefficient);
      }
      if (degree != 0) {
        if (degree == 1) {
          result.append('x');
        } else {
          result.append("x^");
          result.append(degree);
        }
      }
    }
  }
  return result.toString();
}