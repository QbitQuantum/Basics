/**
 * Calculates the modified bessel function \f$I_{n+\alpha}(x)\f$, possibly
 * scaled by \f$\mathrm{e}^{-x}\f$, for real non-negative \f$x,alpha\f$ with
 * \f$0 \le \alpha < 1\f$, and \f$n=0,1,\ldots,nb-1\f$.
 *
 * \arg[in] \c x non-negative real number in \f$I_{n+\alpha}(x)\f$
 * \arg[in] \c alpha non-negative real number with \f$0 \le \alpha < 1\f$ in
 *   \f$I_{n+\alpha}(x)\f$
 * \arg[in] \c nb number of functions to be calculated
 * \arg[in] \c ize switch between no scaling (\c ize = 1) and exponential
 *   scaling (\c ize = 2)
 * \arg[out] \c b real output vector to contain \f$I_{n+\alpha}(x)\f$,
 *   \f$n=0,1,\ldots,nb-1\f$
 * \return error indicator. Only if this value is identical to \c nb, then all
 *   values in \c b have been calculated to full accuracy. If not, errors are
 *   indicated using the following scheme:
 *   - ncalc < 0: At least one of the arguments was out of range (e.g. nb <= 0,
 *     ize neither equals 1 nor 2, \f$|x| \ge exparg\f$). In this case, the
 *     output vector b is not calculated and \c ncalc is set to
 *     \f$\min(nb,0)-1\f$.
 *   - 0 < ncalc < nb: Not all requested functions could be calculated to full
 *     accuracy. This can occur when nb is much larger than |x|. in this case,
 *     the values \f$I_{n+\alpha}(x)\f$ are calculated to full accuracy for
 *     \f$n=0,1,\ldots,ncalc\f$. The rest of the values up to
 *     \f$n=0,1,\ldots,nb-1\f$ is calculated to a lower accuracy.
 *
 * \acknowledgement
 *
 * This program is based on a program written by David J. Sookne [2] that
 * computes values of the Bessel functions \f$J_{\nu}(x)\f$ or \f$I_{\nu}(x)\f$
 * for real argument \f$x\f$ and integer order \f$\nu\f$. modifications include
 * the restriction of the computation to the Bessel function \f$I_{\nu}(x)\f$
 * for non-negative real argument, the extension of the computation to arbitrary
 * non-negative orders \f$\nu\f$, and the elimination of most underflow.
 *
 * References:
 * [1] F. W. J. Olver and D. J. Sookne, A note on backward recurrence
 *   algorithms", Math. Comput. (26), 1972, pp 125 -- 132.
 * [2] D. J. Sookne, "Bessel functions of real argument and int order", NBS
 *   Jour. of Res. B. (77B), 1973, pp. 125 -- 132.
 *
 * Modified by W. J. Cody, Applied Mathematics Division, Argonne National
 *   Laboratory, Argonne, IL, 60439, USA
 *
 * Modified by Jens Keiner, Institute of Mathematics, University of Lübeck,
 *   23560 Lübeck, Germany
 */
static int smbi(const R x, const R alpha, const int nb, const int ize, R *b)
{
  /* machine dependent parameters */
  /* NSIG   - DECIMAL SIGNIFICANCE DESIRED.  SHOULD BE SET TO */
  /*          IFIX(ALOG10(2)*NBIT+1), WHERE NBIT IS THE NUMBER OF */
  /*          BITS IN THE MANTISSA OF A WORKING PRECISION VARIABLE. */
  /*          SETTING NSIG LOWER WILL RESULT IN DECREASED ACCURACY */
  /*          WHILE SETTING NSIG HIGHER WILL INCREASE CPU TIME */
  /*          WITHOUT INCREASING ACCURACY.  THE TRUNCATION ERROR */
  /*          IS LIMITED TO A RELATIVE ERROR OF T=.5*10**(-NSIG). */
  /* ENTEN  - 10.0 ** K, WHERE K IS THE LARGEST int SUCH THAT */
  /*          ENTEN IS MACHINE-REPRESENTABLE IN WORKING PRECISION. */
  /* ENSIG  - 10.0 ** NSIG. */
  /* RTNSIG - 10.0 ** (-K) FOR THE SMALLEST int K SUCH THAT */
  /*          K .GE. NSIG/4. */
  /* ENMTEN - THE SMALLEST ABS(X) SUCH THAT X/4 DOES NOT UNDERFLOW. */
  /* XLARGE - UPPER LIMIT ON THE MAGNITUDE OF X WHEN IZE=2.  BEAR */
  /*          IN MIND THAT IF ABS(X)=N, THEN AT LEAST N ITERATIONS */
  /*          OF THE BACKWARD RECURSION WILL BE EXECUTED. */
  /* EXPARG - LARGEST WORKING PRECISION ARGUMENT THAT THE LIBRARY */
  /*          EXP ROUTINE CAN HANDLE AND UPPER LIMIT ON THE */
  /*          MAGNITUDE OF X WHEN IZE=1. */
  const int nsig = MANT_DIG + 2;
  const R enten = nfft_float_property(NFFT_R_MAX);
  const R ensig = POW(K(10.0),(R)nsig);
  const R rtnsig = POW(K(10.0),-CEIL((R)nsig/K(4.0)));
  const R xlarge = K(1E4);
  const R exparg = FLOOR(LOG(POW(K(R_RADIX),K(DBL_MAX_EXP-1))));

  /* System generated locals */
  int l, n, nend, magx, nbmx, ncalc, nstart;
  R p, em, en, sum, pold, test, empal, tempa, tempb, tempc, psave, plast, tover,
    emp2al, psavel;

  magx = LRINT(FLOOR(x));

  /* return if x, nb, or ize out of range */
  if (   nb <= 0 || x < K(0.0) || alpha < K(0.0) || K(1.0) <= alpha
      || ((ize != 1 || exparg < x) && (ize != 2 || xlarge < x)))
    return (MIN(nb,0) - 1);

  /* 2-term ascending series for small x */
  if (x < rtnsig)
    return scaled_modified_bessel_i_series(x,alpha,nb,ize,b);

  ncalc = nb;
  /* forward sweep, Olver's p-sequence */

  nbmx = nb - magx;
  n = magx + 1;

  en = (R) (n+n) + (alpha+alpha);
  plast = K(1.0);
  p = en/x;

  /* significance test */
  test = ensig + ensig;

  if ((5*nsig) < (magx << 1))
    test = SQRT(test*p);
  else
    test /= POW(K(1.585),(R)magx);

  if (3 <= nbmx)
  {
    /* calculate p-sequence until n = nb-1 */
    tover = enten/ensig;
    nstart = magx+2;
    nend = nb - 1;

    for (n = nstart; n <= nend; n++)
    {
      en += K(2.0);
      pold = plast;
      plast = p;
      p = en*plast/x + pold;
      if (p > tover)
      {
        /* divide p-sequence by tover to avoid overflow. Calculate p-sequence
         * until 1 <= |p| */
        tover = enten;
        p /= tover;
        plast /= tover;
        psave = p;
        psavel = plast;
        nstart = n + 1;

        do
        {
          n++;
          en += K(2.0);
          pold = plast;
          plast = p;
          p = en*plast/x + pold;
        } while (p <= K(1.0));

        tempb = en/x;

        /* Backward test. Find ncalc as the largest n such that test is passed. */
        test = pold*plast*(K(0.5) - K(0.5)/(tempb * tempb))/ensig;
        p = plast*tover;
        n--;
        en -= K(2.0);
        nend = MIN(nb,n);

        for (ncalc = nstart; ncalc <= nend; ncalc++)
        {
          pold = psavel;
          psavel = psave;
          psave = en*psavel/x + pold;
          if (test < psave * psavel)
            break;
        }

        ncalc--;
        goto L80;
      }
    }

    n = nend;
    en = (R) (n+n) + (alpha+alpha);

    /* special significance test for 2 <= nbmx */
    test = FMAX(test,SQRT(plast*ensig)*SQRT(p+p));
  }

  /* calculate p-sequence until significance test is passed */
  do
  {
    n++;
    en += K(2.0);
    pold = plast;
    plast = p;
    p = en*plast/x + pold;
  } while (p < test);

  /* Initialize backward recursion and normalization sum. */
L80:
  n++;
  en += K(2.0);
  tempb = K(0.0);
  tempa = K(1.0)/p;
  em = (R)(n-1);
  empal = em + alpha;
  emp2al = em - K(1.0) + (alpha+alpha);
  sum = tempa*empal*emp2al/em;
  nend = n-nb;

  if (nend < 0)
  {
    /* We have n <= nb. So store b[n] and set higher orders to zero */
    b[n-1] = tempa;
    nend = -nend;
    for (l = 1; l <= nend; ++l)
      b[n-1 + l] = K(0.0);
  }
  else
  {
    if (nend != 0)
    {
      /* recur backward via difference equation, calculating b[n] until n = nb */
      for (l = 1; l <= nend; ++l)
      {
        n--;
        en -= K(2.0);
        tempc = tempb;
        tempb = tempa;
        tempa = en*tempb/x + tempc;
        em -= K(1.0);
        emp2al -= K(1.0);

        if (n == 1)
          break;

        if (n == 2)
          emp2al = K(1.0);

        empal -= K(1.0);
        sum = (sum + tempa*empal)*emp2al/em;
      }
    }

    /* store b[nb] */
    b[n-1] = tempa;

    if (nb <= 1)
    {
      sum = sum + sum + tempa;
      scaled_modified_bessel_i_normalize(x,alpha,nb,ize,b,sum);
      return ncalc;
    }

    /* calculate and store b[nb-1] */
    n--;
    en -= 2.0;
    b[n-1] = en*tempa/x + tempb;

    if (n == 1)
    {
      sum = sum + sum + b[0];
      scaled_modified_bessel_i_normalize(x,alpha,nb,ize,b,sum);
      return ncalc;
    }

    em -= K(1.0);
    emp2al -= K(1.0);

    if (n == 2)
      emp2al = K(1.0);

    empal -= K(1.0);
    sum = (sum + b[n-1]*empal)*emp2al/em;
  }

  nend = n - 2;

  if (nend != 0)
  {
    /* Calculate and store b[n] until n = 2. */
    for (l = 1; l <= nend; ++l)
    {
      n--;
      en -= K(2.0);
      b[n-1] = en*b[n]/x + b[n+1];
      em -= K(1.0);
      emp2al -= K(1.0);

      if (n == 2)
        emp2al = K(1.0);

      empal -= K(1.0);
      sum = (sum + b[n-1]*empal)*emp2al/em;
    }
  }

  /* calculate b[1] */
  b[0] = K(2.0)*empal*b[1]/x + b[2];
  sum = sum + sum + b[0];

  scaled_modified_bessel_i_normalize(x,alpha,nb,ize,b,sum);
  return ncalc;
}