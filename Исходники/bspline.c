/* Evaluate the cardinal B-Spline B_{n-1} supported on [0,n]. */
R Y(bsplines)(const INT k, const R _x)
{
  const R kk = (R)k;
  R result_value;
  INT r;
  INT g1, g2; /* boundaries */
  INT j, idx, ug, og; /* indices */
  R a; /* Alpha of de Boor scheme*/
  R x = _x;
  R scratch[k];

  result_value = K(0.0);

  if (K(0.0) < x && x < kk)
  {
    /* Exploit symmetry around k/2, maybe. */
    if ( (kk - x) < x)
    {
      x = kk - x;
    }

    r = (INT)LRINT(CEIL(x) - K(1.0));

    /* Do not use the explicit formula x^k / k! for first interval! De Boor's
     * algorithm is more accurate. See https://github.com/NFFT/nfft/issues/16.
     */

    for (idx = 0; idx < k; idx++)
      scratch[idx] = K(0.0);

    scratch[k-r-1] = K(1.0);

    /* Bounds of the algorithm. */
    g1 = r;
    g2 = k - 1 - r;
    ug = g2;

    /* g1 <= g2 */

    for (j = 1, og = g2 + 1; j <= g1; j++, og++)
    {
      a = (x + (R)(k - r - og - 1)) / ((R)(k - j));
      scratch[og] = (K(1.0) - a) * scratch[og-1];
      bspline_help(k, x, scratch, j, ug + 1, og - 1, r);
      a = (x + (R)(k - r - ug - 1)) / ((R)(k - j));
      scratch[ug] = a * scratch[ug];
    }

    for (og-- ; j <= g2; j++)
    {
      bspline_help(k, x, scratch, j, ug + 1, og, r);
      a = (x + (R)(k - r - ug - 1)) / ((R)(k - j));
      scratch[ug] = a * scratch[ug];
    }

    for(; j < k; j++)
    {
      ug++;
      bspline_help(k, x, scratch, j, ug, og, r);
    }

    result_value = scratch[k-1];
  }

  return(result_value);
}