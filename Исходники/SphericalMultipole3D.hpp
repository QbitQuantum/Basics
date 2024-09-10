  /** Computes the function
   * W[n*(n+1)/2+m]
   *         = W_n^m
   *         = i^|m| / A_n^m rho^{-n-1} Y_n^m(theta, phi)
   *         = i^|m| (-1)^n sqrt((n+m)!(n-m)!) rho^{-n-1} Y_n^m(theta, phi)
   *         = (-1)^n rho^{-n-1} (n-|m|)! P_n^|m|(cos theta) exp(i m phi) i^|m|
   * for all 0 <= n < P and all 0 <= m <= n.
   *
   * @param[in] rho    The radial distance, rho > 0.
   * @param[in] theta  The inclination or polar angle, 0 <= theta <= pi.
   * @param[in] phi    The azimuthal angle, 0 <= phi <= 2pi.
   * @param[in] P      The maximum degree spherical harmonic to compute, P > 0.
   * @param[out] Y,dY  The output arrays to store Wnm and its theta-derivative.
   *                     Each has storage for P*(P+1)/2 elements.
   *
   * Note this uses the spherical harmonics definition
   * Y_n^m(\theta, \phi) =
   *        \sqrt{\frac{(n-|m|)!}{(n+|m|)!}} P_n^{|m|}(\cos \theta) e^{i m \phi)
   * which has symmetries
   *   Y_n^m(\pi - \theta, \pi + \phi) = (-1)^n Y_n^m(\theta, \phi)
   *   Y_n^{-m} = (-1)^m conj(Y_n^m)
   *
   * Note the symmetry in the result of this function
   *    W_n^{-m} = (-1)^m conj(W_n^m)
   * where conj denotes complex conjugation.
   *
   * These are not the spherical harmonics, but are the spherical
   * harmonics with the prefactor (often denoted A_n^m) included. These are useful
   * for computing multipole and local expansions in an FMM.
   */
  inline static
  void evalW(real_type rho, real_type theta, real_type phi, int P,
             complex_type* Y) {
    typedef real_type     real;
    typedef complex_type  complex;
    using std::cos;
    using std::sin;

    const real    ct = cos(theta);
    const real    st = sin(theta);
    const complex ei = complex(-sin(phi),cos(phi));// exp(i*phi) i

    rho = 1 / rho;
    int m = 0;
    int nm;
    real    Pmm = 1;                               // Init Legendre Pmm(ct)
    real   rhom = rho;                             // Init -1^n rho^{-n-1} (n-m)!
    complex eim = 1;                               // Init exp(i*m*phi) i^-m
    while (true) {                                 // For all 0 <= m < P
      // n == m
      nm = m*(m+1)/2 + m;                          //  Index of Wnm for m > 0
      Y[nm] = rhom * Pmm * eim;                    //  Wnm for m > 0

      // n == m+1
      int n = m+1;
      if (n == P) return;                          //  Done! m == P-1

      real Pnm  = ct * (2*m+1) * Pmm;              //  P_{m+1}^m(x) = x(2m+1)Pmm
      real rhon = rhom * -rho;                     //  -1^n rho^{-n-1} (n-m)!
      nm += n;                                     //  n*(n+1)/2 + m
      Y[nm] = rhon * Pnm * eim;                    //  Wnm for m > 0

      // m+1 < n < P
      real Pn1m = Pmm;                              //  P_{n-1}^m
      while (++n != P) {
        real Pn2m = Pn1m;                           //   P_{n-2}^m
        Pn1m = Pnm;                                 //   P_{n-1}^m
        Pnm = (ct*(2*n-1)*Pn1m-(n+m-1)*Pn2m)/(n-m); //   P_n^m recurrence
        rhon *= -rho * (n - m);                     //   -1^n rho^{-n-1} (n-m)!

        nm += n;                                    //   n*(n+1)/2 + m
        Y[nm] = rhon * Pnm * eim;                   //   Wnm for m > 0
      }

      ++m;                                          //  Increment m

      rhom *= -rho;                                 //  -1^m rho^{-m-1} (n-m)!
      Pmm  *= -st * (2*m-1);                        //  P_{m+1}^{m+1} recurrence
      eim  *= ei;                                   //  exp(i*m*phi) i^m
    }                                               // End loop over m in Wnm
  }