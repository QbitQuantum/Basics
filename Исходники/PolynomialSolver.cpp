int PolynomialSolver::solveQuartic(float c[5], float s[4])
{
  float	coeffs[4],
        z, u, v, sub,
        A, B, C, D,
        sq_A, p, q, r;
  int i, num;

  // normalize the equation:x ^ 4 + Ax ^ 3 + Bx ^ 2 + Cx + D = 0
  A = c[3] / c[4];
  B = c[2] / c[4];
  C = c[1] / c[4];
  D = c[0] / c[4];

  // subsitute x = y - A / 4 to eliminate the cubic term: x^4 + px^2 + qx + r = 0
  sq_A = A * A;
  p = -3.0f / 8.0f * sq_A + B;
  q = 1.0f / 8.0f * sq_A * A - 1.0f / 2.0f * A * B + C;
  r = -3.0f / 256.0f * sq_A * sq_A + 1.0f / 16.0f * sq_A * B - 1.0f / 4.0f * A * C + D;

  if(isZero(r))
  {
    // no absolute term:y(y ^ 3 + py + q) = 0
    coeffs[0] = q;
    coeffs[1] = p;
    coeffs[2] = 0.0;
    coeffs[3] = 1.0;

    num = solveCubic(coeffs, s);
    s[num++] = 0;
  }
  else
  {
    // solve the resolvent cubic...
    coeffs[0] = 1.0f / 2.0f * r * p - 1.0f / 8.0f * q * q;
    coeffs[1] = -r;
    coeffs[2] = -1.0f / 2.0f * p;
    coeffs[3] = 1.0f;
    (void) solveCubic(coeffs, s);

    // ...and take the one real solution...
    z = s[0];

    // ...to build two quadratic equations
    u = z * z - r;
    v = 2.0f * z - p;

    if(isZero(u))
      u = 0.0;
    else if(u > 0.0f)
      u = std::sqrt(u);
    else
      return 0;

    if(isZero(v))
      v = 0;
    else if(v > 0.0f)
      v = std::sqrt(v);
    else
      return 0;

    coeffs[0] = z - u;
    coeffs[1] = q < 0 ? -v : v;
    coeffs[2] = 1.0f;

    num = solveQuadric(coeffs, s);

    coeffs[0] = z + u;
    coeffs[1] = q < 0 ? v : -v;
    coeffs[2] = 1.0f;

    num += solveQuadric(coeffs, s + num);
  }

  // resubstitute
  sub = 1.0f / 4 * A;
  for(i = 0; i < num; i++)
    s[i] -= sub;

return num;
}